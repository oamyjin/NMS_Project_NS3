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

#ifndef SPPIFO_QUEUE_DISC_H
#define SPPIFO_QUEUE_DISC_H

#include "ns3/queue-disc.h"

namespace ns3
{

/**
 * \ingroup traffic-control
 *
 * Simple queue disc implementing the FIFO (First-In First-Out) policy.
 *
 */
class SppifoQueueDisc : public QueueDisc
{
  public:
    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    /**
     * \brief SppifoQueueDisc constructor
     *
     * Creates a queue with a depth of 1000 packets by default
     */
    SppifoQueueDisc();

    ~SppifoQueueDisc() override;

    uint32_t GetFifoNum() const;
    void SetFifoNum(uint32_t fifoNum);

    // Reasons for dropping packets
    static constexpr const char* LIMIT_EXCEEDED_DROP =
        "Queue disc limit exceeded"; //!< Packet dropped due to queue disc limit exceeded

  private:
    bool DoEnqueue(Ptr<QueueDiscItem> item) override;
    Ptr<QueueDiscItem> DoDequeue() override;
    Ptr<const QueueDiscItem> DoPeek() override;
    bool CheckConfig() override;
    void InitializeParams() override;

    uint32_t GetTotalNPackets();

    uint32_t m_fifo_num = 8; // number of fifos
    uint32_t m_bounds[50] = {0}; // max 50 FIFOs
    bool m_useEcn = false;            //!< True if ECN is used (packets are marked instead of being dropped)
    uint32_t m_minTh = 20;         //!< Minimum threshold for (number of packets)

};

} // namespace ns3

#endif /* SPPIFO_QUEUE_DISC_H */
