/*
 * Copyright (c) 2008 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#ifndef FLOW_ID_TAG_H
#define FLOW_ID_TAG_H

#include "ns3/tag.h"

namespace ns3
{

class FlowIdTag : public Tag
{
  public:
    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    TypeId GetInstanceTypeId() const override;
    uint32_t GetSerializedSize() const override;
    void Serialize(TagBuffer buf) const override;
    void Deserialize(TagBuffer buf) override;
    void Print(std::ostream& os) const override;
    FlowIdTag();

    /**
     * Constructs a FlowIdTag with the given flow id
     *
     * \param flowId Id to use for the tag
     */
    FlowIdTag(uint32_t flowId);
    /**
     * Constructs a FlowIdTag with the given flow id
     * 
     * \param flowId Id to assign to the tag
     * \param flowWeight Id to assign to the tag
     * \param isFwd flow forwarding mark
     */
    FlowIdTag(uint32_t flowId, uint32_t flowWeight, bool isFwd);
    /**
     * Sets the flow id for the tag
     * \param flowId Id to assign to the tag
     */
    void SetFlowId(uint32_t flowId);
    /**
     * Sets the flow weight for the flow
     * \param flowWeight Id to assign to the tag
     */
    void SetFlowWeight(uint32_t flowWeight);
    /**
     * Set the flow forwarding mark
     * \param isFwd True if forwaring, False if ack
     */
    void SetIsFwd(bool isFwd);
    /**
     * Get the flow forwarding mark
     * \returns True if the flow is a forwarding flow, otherwise False
     */
    bool GetIsFwd() const;
    /**
     * Gets the flow id for the tag
     * \returns current flow id for this tag
     */
    uint32_t GetFlowId() const;
    /**
     * Gets the flow weight for the tag
     * \returns current flow weight for this tag
     */
    uint32_t GetFlowWeight() const;
    /**
     * Uses a static variable to generate sequential flow id
     * \returns flow id allocated
     */
    static uint32_t AllocateFlowId();

  private:
    uint32_t m_flowId; //!< Flow ID
    uint32_t m_flowWeight; //!< Flow weight
    bool m_isFwd = false; //!< mark True if the flow is a forwarding flow
};

} // namespace ns3

#endif /* FLOW_ID_TAG_H */
