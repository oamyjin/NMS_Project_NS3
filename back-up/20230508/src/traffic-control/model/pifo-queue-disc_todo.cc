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
    // .AddAttribute("MaxSize",
    //                       "The max queue size",
    //                       QueueSizeValue(QueueSize("100p")),
    //                       MakeQueueSizeAccessor(&QueueDisc::SetMaxSize, &QueueDisc::GetMaxSize),
    //                       MakeQueueSizeChecker())
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
  : QueueDisc (SchedulingAlgorithm::STFQ, QueueDiscSizePolicy::MULTIPLE_QUEUES, QueueSizeUnit::PACKETS)
{
  NS_LOG_FUNCTION(this);
  ObjectFactory factory;
  factory.SetTypeId("ns3::DropTailQueue<QueueDiscItem>");
  factory.Set("MaxSize", QueueSizeValue(QueueSize("1p")));
  for (uint16_t i = 0; i < m_q_num; i++)
  {
      AddInternalQueue(factory.Create<InternalQueue>());
      m_q_rank[i] = 999999999; // a very large rank initialization
  }
  std::cout << "PifoQueueDisc Created " << GetNInternalQueues() << std::endl;
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
  std::cout << "PifoQueueDisc::DoEnqueue " << GetCurrentSize()  << " " << GetInternalPrioQueue (0)->GetNPackets () << std::endl;

  uint32_t rank = RankComputation(item); // implement in QueueDisc

  // drop the packet with the max rank
  if (rank >= m_max_rank)
  {
    NS_LOG_LOGIC ("Queue disc limit exceeded -- dropping packet");
    DropBeforeEnqueue (item, LIMIT_EXCEEDED_DROP);
    return false;
  }
  else
  {
    if (m_q_num_full < m_q_num)
    {
      for (uint16_t i = 0; i < m_q_num; i++){
        if (GetInternalQueue(i)->GetNPackets() == 0){
          bool retval = GetInternalQueue(i)->Enqueue(item);
          if (!retval)
          {
            return false;
          }
          m_q_rank[i] = rank;
          if(rank > m_max_rank)
          {
            m_max_rank = rank;
          }
          UpdateFlowTable(item);
          return true;
        }
      }
    }
    else
    {
      uint16_t tail_qid = find_tail_qid(m_q_rank);
      GetInternalQueue(tail_qid)->Dequeue();
      // TODO update max rank
      bool retval = GetInternalQueue(i)->Enqueue(item);
        if (!retval)
        {
          return false;
        }
        m_q_rank[i] = rank;
        if(rank > m_max_rank)
        {
          m_max_rank = rank;
        }
        UpdateFlowTable(item);
        return true;
    }
  }

 

  // If PrioQueue::Enqueue fails, QueueDisc::DropBeforeEnqueue is called by the
  // internal prio queue because QueueDisc::AddInternalPrioQueue sets the trace callback

  if (!retval)
  {
    NS_LOG_WARN ("Packet enqueue failed. Check the size of the internal priority queue");
    return false;
  }

  NS_LOG_LOGIC ("Number packets in priority queue::" << GetInternalPrioQueue (0)->GetNPackets ());

  UpdateFlowTable(item);
  std::cout << "Enqueued" << std::endl;
  return retval;
}

Ptr<QueueDiscItem>
PifoQueueDisc::DoDequeue (void)
{
  NS_LOG_DEBUG("PifoQueueDisc::DoDequeue");
  NS_LOG_FUNCTION (this);
  std::cout << "PifoQueueDisc::DoDequeue " << GetCurrentSize()  << " " << GetInternalPrioQueue (0)->GetNPackets () << std::endl;

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
    std::cout << "Dequeued" << std::endl;
    return item;
  }
  else
  {
    NS_LOG_LOGIC ("PrioQueue empty");
    return nullptr;
  }
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



uint16_t PifoQueueDisc::find_tail_qid(map<uint16_t, uint32_t>& M)
{
    // Declare vector of pairs
    vector<pair<uint16_t, uint32_t> > A;
 
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
 
    uint16_t tail_qid = -1;
    uint32_t tail_rank = rank;
    for (uint16_t i = 0; i < A.size(); i++){
        if (A[i].second > tail_rank){
            tail_rank = A[i].second;
            tail_qid = A[i].first;
        }
    }
    return tail_qid;
}

uint16_t PifoQueueDisc::find_top_qid(map<uint16_t, uint32_t>& M)
{
    // Declare vector of pairs
    vector<pair<uint16_t, uint32_t> > A;
 
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
 
    uint16_t top_qid = 0;
    uint32_t top_rank = A[0].second;
    std::cout << "-------------------find_top_qid A.size():" << A.size() << " top_rank:" << top_rank << std::endl;
    for (uint16_t i = 0; i < A.size(); i++){
        std::cout << " i:" << i << " A[i].first:" << A[i].first << " A[i].second:" << A[i].second << std::endl;
        if (A[i].second < top_rank){
            top_rank = A[i].second;
            top_qid = A[i].first;
        }
    }
    std::cout << "top_qid:" << top_qid << std::endl;
    return top_qid;
}


} // namespace ns3