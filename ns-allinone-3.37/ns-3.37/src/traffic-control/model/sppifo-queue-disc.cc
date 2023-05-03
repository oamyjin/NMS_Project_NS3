/*
 * Copyright (c) 2017 Universita' degli Studi di Napoli Federico II
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:  Stefano Avallone <stavallo@unina.it>
 */

#include "sppifo-queue-disc.h"

#include "ns3/drop-tail-queue.h"
#include "ns3/log.h"
#include "ns3/object-factory.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("SppifoQueueDisc");

NS_OBJECT_ENSURE_REGISTERED(SppifoQueueDisc);

TypeId
SppifoQueueDisc::GetTypeId()
{
    static TypeId tid =
        TypeId("ns3::SppifoQueueDisc")
            .SetParent<QueueDisc>()
            .SetGroupName("TrafficControl")
            .AddConstructor<SppifoQueueDisc>()
            .AddAttribute("MaxSize",
                          "The max queue size",
                          QueueSizeValue(QueueSize("60p")),
                          MakeQueueSizeAccessor(&QueueDisc::SetMaxSize, &QueueDisc::GetMaxSize),
                          MakeQueueSizeChecker())
            // .AddAttribute("FifoNum",
            //               "The number of FIFOs",
            //               UintegerValue(8),
            //               MakeUintegerAccessor(&SppifoQueueDisc::GetFifoNum, &SppifoQueueDisc::GetFifoNum),
            //               MakeUintegerChecker<uint32_t>())
            ;
    return tid;
}

SppifoQueueDisc::SppifoQueueDisc()
    : QueueDisc (SchedulingAlgorithm::STFQ, QueueDiscSizePolicy::MULTIPLE_QUEUES, QueueSizeUnit::PACKETS)
{
    NS_LOG_FUNCTION(this);

    ObjectFactory factory;
    factory.SetTypeId("ns3::DropTailQueue<QueueDiscItem>");
    factory.Set("MaxSize", QueueSizeValue(GetMaxSize()));
    for (uint32_t i = 0; i < m_fifo_num; i++)
    {
        AddInternalQueue(factory.Create<InternalQueue>());
    }

    std::cout << "SpPifoQueueDisc Created " << GetNInternalQueues() << " " << GetMaxSize() << std::endl;
}

SppifoQueueDisc::~SppifoQueueDisc()
{
    NS_LOG_FUNCTION(this);
}

bool
SppifoQueueDisc::DoEnqueue(Ptr<QueueDiscItem> item)
{
    NS_LOG_FUNCTION(this << item);
    NS_LOG_DEBUG("DoEnqueue");
    std::cout << "DoEnqueue" << std::endl;

    uint32_t rank = RankComputation(item);
    
    bool retval = false;
    for (int i = GetNInternalQueues() - 1; i >= 0; i--)
    {
        // push up
        std::ofstream thr("MyResult/queuebound.txt", std::ios::out | std::ios::app);
        thr << "i:" << i << " bound[i]:" << m_bounds[i] << " rank:" << rank << " Qsize:" << GetMaxSize().GetValue() << std::endl;
        if (rank >= m_bounds[i])
        {
            if (GetInternalQueue(i)->GetNPackets() < GetMaxSize().GetValue())
            {
                NS_LOG_DEBUG("queue " << i << " push up");
                retval = GetInternalQueue(i)->Enqueue(item);
                if (retval)
                {
                    m_bounds[i] = rank;
                    UpdateFlowTable(item);
                }
                else
                {
                    NS_LOG_WARN ("Packet enqueue failed. Check the size of the internal fifo queue");
                    return false;
                }
                break;
            }
            else
            {
                DropBeforeEnqueue(item, "Fifo overflow");
                NS_LOG_LOGIC("FIFO Queue full -- dropping pkt");
                std::ofstream thr("MyResult/overflow.txt", std::ios::out | std::ios::app);
                thr << "i:" << i << " bound[i]:" << m_bounds[i] << " rank:" << rank << std::endl;
                return false;
            }
        }
        else
        {
            std::ofstream thr("MyResult/queuebound.txt", std::ios::out | std::ios::app);
            thr << "i:" << i << " bound[i]:" << m_bounds[i] << " rank:" << rank << "======" << std::endl;
            if (i == 0)
            { 
                if (GetInternalQueue(i)->GetNPackets() < GetMaxSize().GetValue()) // TODO check fifo size
                {
                    retval = GetInternalQueue(i)->Enqueue(item);
                    // push down
                    NS_LOG_DEBUG("PUSH DOWN " << m_bounds[0] << " " << rank << "!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    uint32_t cost = m_bounds[0] - rank;
                    m_bounds[0] = rank;
                    for (int j = 1; j < static_cast<int>(GetNInternalQueues()); j++)
                    {
                        m_bounds[j] -= cost;
                    }
                    if (retval)
                    {
                        UpdateFlowTable(item);
                    }
                    else
                    {
                        NS_LOG_LOGIC("FIFO Enqueue failed");
                        return false;
                    }
                    break;
                }
                else
                {
                    DropBeforeEnqueue(item, "Fifo overflow");
                    NS_LOG_LOGIC("FIFO Queue full -- dropping pkt");
                    std::ofstream thr("MyResult/overflow.txt", std::ios::out | std::ios::app);
                    thr << "i:" << i << " bound[i]:" << m_bounds[i] << " rank:" << rank << std::endl;
                    return false;
                }
            }
        }

    }

    // If Queue::Enqueue fails, QueueDisc::DropBeforeEnqueue is called by the
    // internal queue because QueueDisc::AddInternalQueue sets the trace callback

    NS_LOG_LOGIC("Number packets " << GetInternalQueue(0)->GetNPackets());
    NS_LOG_LOGIC("Number bytes " << GetInternalQueue(0)->GetNBytes());

    return retval;
}

Ptr<QueueDiscItem>
SppifoQueueDisc::DoDequeue()
{
    NS_LOG_FUNCTION(this);
    NS_LOG_DEBUG("DoDequeue");
    std::cout << "DoDequeue" << std::endl;
    
    Ptr<QueueDiscItem> item;
    for (int i = 0; i < static_cast<int>(GetNInternalQueues()); i++)
    {
        if (GetInternalQueue(i)->GetNPackets() > 0)
        {
            std::cout << "i:" << i << std::endl;
            item = GetInternalQueue(i)->Dequeue();
            UpdateCurrentRound(item);
            break;
        }
    }
    if (!item)
    {
        NS_LOG_LOGIC("Queue empty");
        return nullptr;
    }
    return item;
}

Ptr<const QueueDiscItem>
SppifoQueueDisc::DoPeek()
{
    NS_LOG_FUNCTION(this);

    Ptr<const QueueDiscItem> item = GetInternalQueue(0)->Peek();

    if (!item)
    {
        NS_LOG_LOGIC("Queue empty");
        return nullptr;
    }

    return item;
}

uint32_t 
SppifoQueueDisc::GetFifoNum() const
{
    NS_LOG_FUNCTION(this);
    return m_fifo_num;
}
    
void 
SppifoQueueDisc::SetFifoNum(uint32_t fifoNum)
{
    NS_LOG_FUNCTION(this << fifoNum);
    m_fifo_num = fifoNum;
}

bool
SppifoQueueDisc::CheckConfig()
{
    NS_LOG_FUNCTION(this);
    return true;
}

void
SppifoQueueDisc::InitializeParams()
{
    NS_LOG_FUNCTION(this);
}

} // namespace ns3
