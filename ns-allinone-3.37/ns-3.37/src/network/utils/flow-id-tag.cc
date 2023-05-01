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
#include "flow-id-tag.h"

#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("FlowIdTag");

NS_OBJECT_ENSURE_REGISTERED(FlowIdTag);

TypeId
FlowIdTag::GetTypeId()
{
    static TypeId tid = TypeId("ns3::FlowIdTag")
                            .SetParent<Tag>()
                            .SetGroupName("Network")
                            .AddConstructor<FlowIdTag>();
    return tid;
}

TypeId
FlowIdTag::GetInstanceTypeId() const
{
    return GetTypeId();
}

uint32_t
FlowIdTag::GetSerializedSize() const
{
    NS_LOG_FUNCTION(this);
    return 9;
}

void
FlowIdTag::Serialize(TagBuffer buf) const
{
    NS_LOG_FUNCTION(this << &buf);
    buf.WriteU32(m_flowId);
    buf.WriteU32(m_flowWeight);
    buf.WriteU8(m_isFwd);
}

void
FlowIdTag::Deserialize(TagBuffer buf)
{
    NS_LOG_FUNCTION(this << &buf);
    m_flowId = buf.ReadU32();
    m_flowWeight = buf.ReadU32();
    m_isFwd = buf.ReadU8();
}

void
FlowIdTag::Print(std::ostream& os) const
{
    NS_LOG_FUNCTION(this << &os);
    os << "FlowId=" << m_flowId << " m_flowWeight=" << m_flowWeight << " m_isFwd=" << m_isFwd;
}

FlowIdTag::FlowIdTag()
    : Tag()
{
    NS_LOG_FUNCTION(this);
}

FlowIdTag::FlowIdTag(uint32_t id)
    : Tag(),
      m_flowId(id)
{
    NS_LOG_FUNCTION(this << id);
}

FlowIdTag::FlowIdTag(uint32_t id, uint32_t weight, bool isFwd)
    : Tag(),
      m_flowId(id),
      m_flowWeight(weight),
      m_isFwd(isFwd)
{
    NS_LOG_FUNCTION(this << id << weight << isFwd);
}

void
FlowIdTag::SetFlowId(uint32_t id)
{
    NS_LOG_FUNCTION(this << id);
    m_flowId = id;
}

void
FlowIdTag::SetFlowWeight(uint32_t weight)
{
    NS_LOG_FUNCTION(this << weight);
    m_flowWeight = weight;
}

void
FlowIdTag::SetIsFwd(bool isFwd)
{
    NS_LOG_FUNCTION(this << isFwd);
    m_isFwd = isFwd;
}

bool
FlowIdTag::GetIsFwd() const
{
    NS_LOG_FUNCTION(this);
    return m_isFwd;
}

uint32_t
FlowIdTag::GetFlowWeight() const
{
    NS_LOG_FUNCTION(this);
    return m_flowWeight;
}

uint32_t
FlowIdTag::GetFlowId() const
{
    NS_LOG_FUNCTION(this);
    return m_flowId;
}

uint32_t
FlowIdTag::AllocateFlowId()
{
    NS_LOG_FUNCTION_NOARGS();
    static uint32_t nextFlowId = 1;
    uint32_t flowId = nextFlowId;
    nextFlowId++;
    return flowId;
}

} // namespace ns3
