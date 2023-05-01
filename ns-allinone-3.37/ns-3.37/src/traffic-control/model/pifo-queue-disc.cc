/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2018 Stanford University
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
 * Author: Stephen Ibanez <sibanez@stanford.edu>
 */

#include "ns3/log.h"
#include "ns3/object-factory.h"
#include "ns3/queue.h"
#include "ns3/enum.h"
#include "ns3/prio-queue.h"
#include "ns3/net-device-queue-interface.h"
#include "ns3/socket.h"
#include "pifo-queue-disc.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PifoQueueDisc");

NS_OBJECT_ENSURE_REGISTERED (PifoQueueDisc);

TypeId PifoQueueDisc::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PifoQueueDisc")
    .SetParent<QueueDisc> ()
    .SetGroupName ("TrafficControl")
    .AddConstructor<PifoQueueDisc> ()
    .AddAttribute("MaxSize",
                          "The max queue size",
                          QueueSizeValue(QueueSize("100p")),
                          MakeQueueSizeAccessor(&QueueDisc::SetMaxSize, &QueueDisc::GetMaxSize),
                          MakeQueueSizeChecker())
    // .AddAttribute("SchedulingAlgorithm",
    //                       "The scheduling algorithm",
    //                       SchedulingAlgorithm::STFQ,
    //                       MakeEnumAccessor(&QueueDisc::SetSchedulingAlgorithm, &QueueDisc::GetSchedulingAlgorithm),
    //                       MakeEnumChecker(SchedulingAlgorithm::STFQ,
    //                                       "STFQ",
    //                                       SchedulingAlgorithm::LSTF,
    //                                       "LSTF"))
    ;
;
  return tid;
}

PifoQueueDisc::PifoQueueDisc ()
  : QueueDisc (SchedulingAlgorithm::STFQ, QueueDiscSizePolicy::SINGLE_INTERNAL_PRIO_QUEUE, QueueSizeUnit::PACKETS)
{
  NS_LOG_FUNCTION (this);
  ObjectFactory factory;
  factory.SetTypeId ("ns3::PrioQueue<QueueDiscItem>");
  factory.Set ("MaxSize", QueueSizeValue (GetMaxSize ()));
  AddInternalPrioQueue (factory.Create<InternalPrioQueue> ());
  std::cout << "PifoQueueDisc Created " << GetMaxSize() << std::endl;
}

PifoQueueDisc::~PifoQueueDisc ()
{
  NS_LOG_FUNCTION (this);
}

bool
PifoQueueDisc::DoEnqueue (Ptr<QueueDiscItem> item)
{
  NS_LOG_DEBUG("PifoQueueDisc::DoEnqueue");
  NS_LOG_FUNCTION (this << item);
  NS_LOG_DEBUG(GetCurrentSize () << " " << GetMaxSize ());
  if (GetCurrentSize () >= GetMaxSize ())
    {
      NS_LOG_LOGIC ("Queue disc limit exceeded -- dropping packet");
      DropBeforeEnqueue (item, LIMIT_EXCEEDED_DROP);
      return false;
    }

  int32_t rank = RankComputation(item); // implement in QueueDisc
  bool retval = GetInternalPrioQueue (0)->Enqueue (item);

  // If PrioQueue::Enqueue fails, QueueDisc::DropBeforeEnqueue is called by the
  // internal prio queue because QueueDisc::AddInternalPrioQueue sets the trace callback

  if (!retval)
    {
      NS_LOG_WARN ("Packet enqueue failed. Check the size of the internal priority queue");
    }

  NS_LOG_LOGIC ("Number packets in priority queue::" << GetInternalPrioQueue (0)->GetNPackets ());

  return retval;
}

Ptr<QueueDiscItem>
PifoQueueDisc::DoDequeue (void)
{
  NS_LOG_DEBUG("PifoQueueDisc::DoDequeue");
  NS_LOG_FUNCTION (this);

  Ptr<QueueDiscItem> item;

  if ((item = GetInternalPrioQueue (0)->Dequeue ()) != 0)
    {
      bool retval = UpdateCurrentRound(item); // implement in QueueDisc
      if (!retval)
      {
        NS_LOG_WARN ("Update current round failed when deque " << item);
      }

      NS_LOG_LOGIC ("Popped from priority queue: " << item);
      NS_LOG_LOGIC ("Number packets priority queue: " << GetInternalPrioQueue (0)->GetNPackets ());
      return item;
    }
  
  NS_LOG_LOGIC ("PrioQueue empty");
  return item;
}

Ptr<const QueueDiscItem>
PifoQueueDisc::DoPeek (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<const QueueDiscItem> item;

  if ((item = GetInternalPrioQueue (0)->Peek ()) != 0)
    {
      NS_LOG_LOGIC ("Peeked from priority queue: " << item);
      NS_LOG_LOGIC ("Number packets priority queue: " << GetInternalPrioQueue (0)->GetNPackets ());
      return item;
    }

  NS_LOG_LOGIC ("PrioQueue empty");
  return item;
}

bool
PifoQueueDisc::CheckConfig (void)
{
  NS_LOG_FUNCTION (this);
  if (GetNQueueDiscClasses () > 0)
    {
      NS_LOG_ERROR ("PifoQueueDisc cannot have classes");
      return false;
    }

  if (GetNInternalPrioQueues () != 1)
    {
      NS_LOG_ERROR ("PifoQueueDisc needs 1 internal priority queue");
      return false;
    }

  if (GetInternalPrioQueue (0)-> GetMaxSize ().GetUnit () != QueueSizeUnit::PACKETS)
    {
      NS_LOG_ERROR ("PifoQueueDisc needs 1 internal priority queue operating in packet mode");
      return false;
    }

  if (GetInternalPrioQueue (0)->GetMaxSize () < GetMaxSize ())
    {
      NS_LOG_ERROR ("The capacity of the internal priority queue is less than the queue disc capacity");
      return false;
    }

  return true;
}

void
PifoQueueDisc::InitializeParams (void)
{
  NS_LOG_FUNCTION (this);
}

} // namespace ns3