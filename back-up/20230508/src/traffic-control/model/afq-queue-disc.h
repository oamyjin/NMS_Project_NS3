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

#ifndef AFQ_H
#define AFQ_H

#include "ns3/queue-disc.h"

namespace ns3
{

/**
 * \ingroup traffic-control
 *
 * Linux pfifo_fast is the default priority queue enabled on Linux
 * systems. Packets are enqueued in three FIFO droptail queues according
 * to three priority bands based on the packet priority.
 *
 * The system behaves similar to three ns3::DropTail queues operating
 * together, in which packets from higher priority bands are always
 * dequeued before a packet from a lower priority band is dequeued.
 *
 * The queue disc capacity, i.e., the maximum number of packets that can
 * be enqueued in the queue disc, is set through the limit attribute, which
 * plays the same role as txqueuelen in Linux. If no internal queue is
 * provided, three DropTail queues having each a capacity equal to limit are
 * created by default. User is allowed to provide queues, but they must be
 * three, operate in packet mode and each have a capacity not less
 * than limit. No packet filter can be provided.
 */
class AFQQueueDisc : public QueueDisc
{
  public:
    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    /**
     * \brief AFQQueueDisc constructor
     *
     */
    AFQQueueDisc();

    ~AFQQueueDisc() override;

    // Reasons for dropping packets
    static constexpr const char* LIMIT_EXCEEDED_DROP =
        "Queue disc limit exceeded"; //!< Packet dropped due to queue disc limit exceeded

  private:
    /**
     * queue bounds
     */
    uint16_t m_fifo_num = 32; // number of fifos
    uint16_t m_granularity = 4; //granularity per fifo
    uint32_t m_dropA = 0;
    uint32_t m_dropB = 0;
    uint32_t m_eq = 0;
    uint32_t m_dq = 0;

    bool DoEnqueue(Ptr<QueueDiscItem> item) override;
    Ptr<QueueDiscItem> DoDequeue() override;
    Ptr<const QueueDiscItem> DoPeek() override;
    bool CheckConfig() override;
    void InitializeParams() override;
};

} // namespace ns3

#endif /* AFQ_H */