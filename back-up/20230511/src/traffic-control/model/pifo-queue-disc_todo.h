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

#ifndef PIFO_H
#define PIFO_H

#include "ns3/queue-disc.h"

namespace ns3 {

/**
 * \ingroup traffic-control
 *
 * A single PIFO queue disc. Has one associated filter which assigns a
 * rank to each packet. The rank determines the packet's priority (lower
 * rank = higher priority).
 *
 * Uses one internal priority queue.
 *
 */
class PifoQueueDisc : public QueueDisc {
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * \brief PifoQueueDisc constructor
   *
   * Creates a PIFO queue with a depth of 1000 packets by default
   */
  PifoQueueDisc ();

  virtual ~PifoQueueDisc() override;

  // Reasons for dropping packets
  static constexpr const char* LIMIT_EXCEEDED_DROP = "Queue disc limit exceeded";  //!< Packet dropped due to queue disc limit exceeded

private:
  virtual bool DoEnqueue (Ptr<QueueDiscItem> item) override;
  virtual Ptr<QueueDiscItem> DoDequeue (void) override;
  virtual Ptr<const QueueDiscItem> DoPeek (void) override;
  virtual bool CheckConfig (void) override;
  virtual void InitializeParams (void) override;

  uint16_t find_top_qid(map<uint16_t, uint32_t>& M);
  uint16_t find_tail_qid(map<uint16_t, uint32_t>& M);

  std::map<uint16_t, uint32_t> m_q_rank; // <internalqueue_id, rank>
  uint32_t m_max_rank = 0; // max rank in the pifo queue
  uint16_t m_q_num = 300;
  uint16_t m_q_num_full = 0; // occupied fifo number
};

} // namespace ns3

#endif /* PIFO_H */