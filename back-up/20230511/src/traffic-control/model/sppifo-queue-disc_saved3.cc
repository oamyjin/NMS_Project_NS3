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
            //               MakeUintegerAccessor(&SppifoQueueDisc::m_fifo_num),
            //               MakeUintegerChecker<uint32_t>())
            // .AddAttribute("UseEcn",
            //               "True to use ECN (packets are marked instead of being dropped)",
            //               BooleanValue(false),
            //               MakeBooleanAccessor(&SppifoQueueDisc::m_useEcn),
            //               MakeBooleanChecker())
            // .AddAttribute("MinTh",
            //               "Minimum number threshold of packets",
            //               DoubleValue(5),
            //               MakeUintegerAccessor(&SppifoQueueDisc::m_minTh),
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
        m_bounds[i] = 0;
    }

    std::cout << "SpPifoQueueDisc Created " << GetNInternalQueues() << " " << GetMaxSize() << " m_minTh:" << m_minTh << std::endl;
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

    uint32_t rank = RankComputation(item);

     if (rank > ((GetCurrentRound() / m_granularity) * m_granularity + m_granularity * m_fifo_num - 1))
    {
        DropBeforeEnqueue(item, "Too large rank");
        return false;
    }

    uint32_t band = 0;
    for (uint32_t i = GetNInternalQueues() - 1; i >= 0; i--)
    {
        // push up
        std::ofstream thr("MyResult/queuebound.txt", std::ios::out | std::ios::app);
        thr << "i:" << i << " bound[i]:" << m_bounds[i] << " rank:" << rank << " Qsize:" << GetTotalNPackets() << " " << GetInternalQueue(7)->GetNPackets() << " " << GetInternalQueue(6)->GetNPackets() << std::endl;
        if (rank >= m_bounds[i] || i == 0)
        {
            band = i;
            break;
        }
    }

    bool retval = GetInternalQueue(band)->Enqueue(item);
    if (!retval)
    {
        NS_LOG_WARN ("Packet enqueue failed. Check the size of the internal fifo queue");
        return false;
    }
    else
    {
        m_bounds[band] = rank;
        int cost = m_bounds[band] - rank;
        if (cost > 0)
        {
            for (uint32_t j = GetNInternalQueues() - 1; j > band; j--)
            {
                m_bounds[j] = m_bounds[j] - cost;
            }
        }
    }

    // If Queue::Enqueue fails, QueueDisc::DropBeforeEnqueue is called by the
    // internal queue because QueueDisc::AddInternalQueue sets the trace callback
    
    /*if (m_useEcn && GetTotalNPackets() > m_minTh)
    {
        Mark(item, "SP-Pifo ECN mark");
    }*/

    UpdateFlowTable(item);
    return retval;
}

Ptr<QueueDiscItem>
SppifoQueueDisc::DoDequeue()
{
    NS_LOG_FUNCTION(this);
    NS_LOG_DEBUG("DoDequeue");
    
    int band = -1;
    Ptr<QueueDiscItem> item;

    for (uint32_t i = 0; i < GetNInternalQueues(); i++)
    {
        if (GetInternalQueue(i)->GetNPackets() != 0)
        {
            NS_LOG_DEBUG("i:" << i);
            band = i;
            item = GetInternalQueue(band)->Dequeue();
            break;
        }
    }
    if (band != -1)
    {
        bool retval = UpdateCurrentRound(item); // implement in QueueDisc
        if (!retval)
        {
            NS_LOG_WARN ("Update current round failed when deque " << item);
        }
        NS_LOG_LOGIC("Popped from band " << band << ": " << item);
        NS_LOG_LOGIC("Number packets band " << band << ": " << GetInternalQueue(band)->GetNPackets());
        return item;
    }
    NS_LOG_DEBUG("band:" << band << " " << item);

    NS_LOG_LOGIC("Queue empty");
    return nullptr;
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


uint32_t
SppifoQueueDisc::GetTotalNPackets()
{
    uint32_t total = 0;
    for(int i = 0; i < m_fifo_num; i++)
    {
        total += GetInternalQueue(i)->GetNPackets();
    }
    return total;
}

} // namespace ns3
