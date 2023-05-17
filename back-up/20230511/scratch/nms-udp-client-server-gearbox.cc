/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 * ==== Node0 <-> Node1 <-> Node1
 * ==== Gearbox on the link from middleNode to Node1
 *
 *
 *
   A(1) --------
               |
   A(2) -----\ |
              \|
   A(3) ------ router(0) ------- S(6)
              /|
   A(4) -----/ |
               |
   A(5) --------
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/random-variable-stream.h"
#include "ns3/stats-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/udp-header.h"
#include "ns3/flow-monitor.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("MyTopoUDP");

uint32_t previous1 = 0;
uint32_t previous2 = 0;
uint32_t previous3 = 0;
Time prevTime1 = Seconds(0);
Time prevTime2 = Seconds(0);
Time prevTime3 = Seconds(0);
double nSamplingPeriod = 0.1;
double stopTime = 10.0;

int
main(int argc, char* argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    // LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    // LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    // LogComponentEnable ("DropTailQueue", LOG_LEVEL_INFO);

    NodeContainer clientNodes, routers, serverNode;
    routers.Create(1);     // 0
    clientNodes.Create(3); // 1,2,3
    serverNode.Create(1);  // 4
    NodeContainer nodes = NodeContainer(routers, clientNodes, serverNode);
    std::vector<NodeContainer> nodeAdjacencyList(4);
    nodeAdjacencyList[0] = NodeContainer(nodes.Get(0), nodes.Get(1)); // router(0),A(1)
    nodeAdjacencyList[1] = NodeContainer(nodes.Get(0), nodes.Get(2)); // router(0),A(2)
    nodeAdjacencyList[2] = NodeContainer(nodes.Get(0), nodes.Get(3)); // router(0),A(3)
    nodeAdjacencyList[3] = NodeContainer(nodes.Get(0), nodes.Get(4)); // router(0),S(4)

    std::vector<PointToPointHelper> p2p(4);
    p2p[0].SetDeviceAttribute("DataRate", StringValue("10Mbps")); 
    p2p[0].SetChannelAttribute("Delay", StringValue("1ms"));
    p2p[0].SetQueue("ns3::DropTailQueue", "MaxSize", QueueSizeValue(QueueSize("1000p")));
    for (int i = 1; i < 4; i++)
    {
        p2p[i].SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p[i].SetChannelAttribute("Delay", StringValue("1ms"));
        p2p[i].SetQueue("ns3::DropTailQueue", "MaxSize", QueueSizeValue(QueueSize("1p")));
    }
    p2p[3].SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p[3].SetChannelAttribute("Delay", StringValue("2ms"));
    p2p[3].SetQueue("ns3::DropTailQueue", "MaxSize", QueueSizeValue(QueueSize("1000p")));

    std::vector<NetDeviceContainer> devices(4);
    for (int i = 0; i < 4; i++)
    {
        devices[i] = p2p[i].Install(nodeAdjacencyList[i]);
    }

    InternetStackHelper stack;
    stack.Install(nodes);

    // NS_LOG_INFO ("Assign IP address.");
    Ipv4AddressHelper address;
    std::vector<Ipv4InterfaceContainer> interfaces(4);
    for (uint32_t i = 0; i < 4; i++)
    {
        std::ostringstream subset;
        subset << "10.1." << i + 1 << ".0";
        address.SetBase(subset.str().c_str(), "255.255.255.0");
        interfaces[i] = address.Assign(
            devices[i]);
    }

    TrafficControlHelper tch;
    tch.Uninstall(devices[0]);
    tch.Uninstall(devices[1]);
    tch.Uninstall(devices[2]);
    tch.Uninstall(devices[3]);

    std::string qdiscTypeId = "ns3::FifoQueueDisc"; //"ns3::SppifoQueueDisc" "ns3::FifoQueueDisc" "ns3::PifoQueueDisc" "ns3::AFQQueueDisc"

    Config::SetDefault(qdiscTypeId + "::MaxSize", QueueSizeValue(QueueSize("1000p")));
    tch.SetRootQueueDisc(qdiscTypeId);
    tch.Install(devices[3]);

    // Create router nodes, initialize routing database and set up the routing tables in the nodes.
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    uint16_t port = 50000;
    Address sinkLocalAddress(InetSocketAddress(Ipv4Address::GetAny(), port));
    PacketSinkHelper sinkHelper("ns3::UdpSocketFactory", sinkLocalAddress);
    ApplicationContainer sinkApp = sinkHelper.Install(nodes.Get(4));
    sinkApp.Start(Seconds(0));
    sinkApp.Stop(Seconds(stopTime + 1));

    AddressValue remoteAddress(InetSocketAddress(interfaces[3].GetAddress(1), port));
    OnOffHelper sourceHelper("ns3::UdpSocketFactory", Address());
    sourceHelper.SetAttribute("DataRate", StringValue("4Mbps"));
    sourceHelper.SetAttribute("PacketSize", UintegerValue(1024));
    sourceHelper.SetAttribute("Remote", remoteAddress);
    sourceHelper.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    sourceHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));

    ApplicationContainer sourceApp1 = sourceHelper.Install(nodes.Get(1)); // A1
    ApplicationContainer sourceApp2 = sourceHelper.Install(nodes.Get(2)); // A2
    ApplicationContainer sourceApp3 = sourceHelper.Install(nodes.Get(3)); // A3
    sourceApp1.Start(Seconds(0));
    sourceApp1.Stop(Seconds(stopTime));
    sourceApp2.Start(Seconds(0));
    sourceApp2.Stop(Seconds(stopTime));
    sourceApp3.Start(Seconds(0));
    sourceApp3.Stop(Seconds(stopTime));

    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.Install(nodes);

    Simulator::Stop(Seconds(stopTime));

    monitor->SerializeToXmlFile("MyResult/FlowPerformance.xml", true, true);

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
