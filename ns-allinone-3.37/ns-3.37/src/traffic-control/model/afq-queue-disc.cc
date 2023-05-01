/*
 * Copyright (c) 2007, 2014 University of Washington
 *               2015 Universita' degli Studi di Napoli Federico II
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
 *           Tom Henderson <tomhend@u.washington.edu>
 */

#include "afq-queue-disc.h"

#include "ns3/log.h"
#include "ns3/object-factory.h"
#include "ns3/queue.h"
#include "ns3/socket.h"
#include "ns3/gearbox-pkt-tag.h"
#include "ns3/ipv4-queue-disc-item.h"
#include "ns3/tcp-header.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("AFQQueueDisc");

NS_OBJECT_ENSURE_REGISTERED(AFQQueueDisc);

TypeId
AFQQueueDisc::GetTypeId()
{
    static TypeId tid =
        TypeId("ns3::AFQQueueDisc")
            .SetParent<QueueDisc>()
            .SetGroupName("TrafficControl")
            .AddConstructor<AFQQueueDisc>()
            .AddAttribute("MaxSize",
                          "The maximum number of packets accepted by this queue disc.",
                          QueueSizeValue(QueueSize("20p")),
                          MakeQueueSizeAccessor(&QueueDisc::SetMaxSize, &QueueDisc::GetMaxSize),
                          MakeQueueSizeChecker()) 
            ;
    return tid;
}

AFQQueueDisc::AFQQueueDisc()
    : QueueDisc (SchedulingAlgorithm::STFQ, QueueDiscSizePolicy::MULTIPLE_QUEUES, QueueSizeUnit::PACKETS)
{
    NS_LOG_FUNCTION(this);

    ObjectFactory factory;
    factory.SetTypeId("ns3::DropTailQueue<QueueDiscItem>");
    factory.Set("MaxSize", QueueSizeValue(GetMaxSize()));
    for (uint16_t i = 0; i < m_fifo_num; i++)
    {
        AddInternalQueue(factory.Create<InternalQueue>());
    }

    std::cout << "AFQQueueDisc Created " << GetNInternalQueues() << " " << GetMaxSize() << std::endl;
}

AFQQueueDisc::~AFQQueueDisc()
{
    NS_LOG_FUNCTION(this);
}

bool
AFQQueueDisc::DoEnqueue(Ptr<QueueDiscItem> item)
{
    NS_LOG_FUNCTION(this << item);
    NS_LOG_DEBUG("DoEnqueue");

    uint32_t rank = RankComputation(item);
    if (rank > ((GetCurrentRound() / m_granularity) * m_granularity + m_granularity * m_fifo_num - 1))
    {
        NS_LOG_DEBUG("Too large rank " << rank << ", granularity: " << m_granularity << " m_fifo_num:" << m_fifo_num << " currentRound:" << GetCurrentRound());
        DropBeforeEnqueue(item, "Too large rank");
        return false;
    }
    // Calulate Queue Idx
    uint32_t band = rank / m_granularity % m_fifo_num;
    std::cout << "rank:" << rank << " band:" << band << " m_granularity:" << m_granularity << " Qsize:" << GetMaxSize().GetValue() << std::endl;

    bool retval = GetInternalQueue(band)->Enqueue(item);

    // If Queue::Enqueue fails, QueueDisc::DropBeforeEnqueue is called by the
    // internal queue because QueueDisc::AddInternalQueue sets the trace callback

    if (!retval)
    {
        NS_LOG_WARN("Packet enqueue failed. Check the size of the internal queues");
    }

    NS_LOG_LOGIC("Number packets band " << band << ": " << GetInternalQueue(band)->GetNPackets());

    return retval;
}

Ptr<QueueDiscItem>
AFQQueueDisc::DoDequeue()
{
    NS_LOG_FUNCTION(this);
    NS_LOG_DEBUG("DoDequeue");

    uint32_t current_band = GetCurrentRound() / m_granularity % m_fifo_num;
    uint32_t band = -1;
    Ptr<QueueDiscItem> item;
    NS_LOG_DEBUG("current_band:" << current_band << " GetCurrentRound():" << GetCurrentRound());

    for (uint32_t i = 0; i < GetNInternalQueues(); i++)
    {
        NS_LOG_DEBUG("q:" << (i + current_band) % m_fifo_num << " GetNPackets():" << GetInternalQueue((i + current_band) % m_fifo_num)->GetNPackets());
        if (GetInternalQueue((i + current_band) % m_fifo_num)->GetNPackets() != 0)
        {
            band = (i + current_band) % m_fifo_num;
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

    NS_LOG_LOGIC("Queue empty");
    return item;
}

Ptr<const QueueDiscItem>
AFQQueueDisc::DoPeek()
{
    NS_LOG_FUNCTION(this);

    Ptr<const QueueDiscItem> item;

    for (uint32_t i = 0; i < GetNInternalQueues(); i++)
    {
        if ((item = GetInternalQueue(i)->Peek()))
        {
            NS_LOG_LOGIC("Peeked from band " << i << ": " << item);
            NS_LOG_LOGIC("Number packets band " << i << ": " << GetInternalQueue(i)->GetNPackets());
            return item;
        }
    }

    NS_LOG_LOGIC("Queue empty");
    return item;
}

bool
AFQQueueDisc::CheckConfig()
{
    NS_LOG_FUNCTION(this);

    return true;
}

void
AFQQueueDisc::InitializeParams()
{
    NS_LOG_FUNCTION(this);
}

} // namespace ns3
