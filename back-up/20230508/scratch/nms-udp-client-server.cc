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
#include <vector>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("MyTopoUDP");

int
main(int argc, char* argv[])
{
    double stopTime = 15.0;

    CommandLine cmd;
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    // LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    // LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    // LogComponentEnable ("DropTailQueue", LOG_LEVEL_INFO);
    LogComponentEnable ("PifoQueueDisc", LOG_LEVEL_INFO);
    //LogComponentEnable ("QueueDisc", LOG_LEVEL_INFO);

    int clientNum = 8;
    NodeContainer clientNodes, routers, serverNode;
    routers.Create(1);     // 0
    clientNodes.Create(clientNum); // 1,2,3
    serverNode.Create(1);  // 4
    NodeContainer nodes = NodeContainer(routers, clientNodes, serverNode);
    std::vector<NodeContainer> nodeAdjacencyList(clientNum+1);
    for (int i = 0; i < clientNum+1; i++){
        nodeAdjacencyList[i] = NodeContainer(nodes.Get(0), nodes.Get(i+1)); // router(0),A(1)
    }
    // nodeAdjacencyList[0] = NodeContainer(nodes.Get(0), nodes.Get(1)); // router(0),A(1)
    // nodeAdjacencyList[1] = NodeContainer(nodes.Get(0), nodes.Get(2)); // router(0),A(2)
    // nodeAdjacencyList[2] = NodeContainer(nodes.Get(0), nodes.Get(3)); // router(0),A(3)
    // nodeAdjacencyList[3] = NodeContainer(nodes.Get(0), nodes.Get(4)); // router(0),S(4)

    std::vector<PointToPointHelper> p2p(clientNum+1);
    for (int i = 0; i < clientNum; i++)
    {
        p2p[i].SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p[i].SetChannelAttribute("Delay", StringValue("1ms"));
        p2p[i].SetQueue("ns3::DropTailQueue", "MaxSize", QueueSizeValue(QueueSize("1000p")));
    }
    // bottleneck: from router to server
    p2p[clientNum].SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p[clientNum].SetChannelAttribute("Delay", StringValue("1ms"));
    p2p[clientNum].SetQueue("ns3::DropTailQueue", "MaxSize", QueueSizeValue(QueueSize("1p")));

    std::vector<NetDeviceContainer> devices(clientNum+1);
    for (int i = 0; i < clientNum+1; i++)
    {
        devices[i] = p2p[i].Install(nodeAdjacencyList[i]);
    }

    InternetStackHelper stack;
    stack.Install(nodes);

    // NS_LOG_INFO ("Assign IP address.");
    Ipv4AddressHelper address;
    std::vector<Ipv4InterfaceContainer> interfaces(clientNum+1);
    for (uint32_t i = 0; i < clientNum+1; i++)
    {
        std::ostringstream subset;
        subset << "10.1." << i + 1 << ".0";
        address.SetBase(subset.str().c_str(), "255.255.255.0");
        interfaces[i] = address.Assign(
            devices[i]);
    }

    TrafficControlHelper tch;
    for (int i = 0; i < clientNum+1; i++)
    {
        tch.Uninstall(devices[i]);
    }

    std::string qdiscTypeId = "ns3::SppifoQueueDisc"; //"ns3::SppifoQueueDisc" "ns3::FifoQueueDisc" "ns3::PifoQueueDisc" "ns3::AFQQueueDisc"

    Config::SetDefault(qdiscTypeId + "::MaxSize", QueueSizeValue(QueueSize("10000p")));
    tch.SetRootQueueDisc(qdiscTypeId);
    tch.Install(devices[clientNum]);

    // Create router nodes, initialize routing database and set up the routing tables in the nodes.
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    uint32_t MaxPacketSize = 1024;
    Time interPacketInterval = Seconds(0.001);//15Mbps:0.000546
    uint32_t maxPacketCount = 1000;

    uint16_t port = 4000;
    UdpServerHelper server(port);
    ApplicationContainer apps = server.Install(nodes.Get(clientNum+1));
    apps.Start(Seconds(0.0));
    apps.Stop(Seconds(20.0));

    UdpClientHelper client(interfaces[clientNum].GetAddress(1), port);
    client.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
    client.SetAttribute("Interval", TimeValue(interPacketInterval));
    client.SetAttribute("PacketSize", UintegerValue(MaxPacketSize));

    int weights[] = {80, 70, 60, 50, 40, 30, 20, 10};
    double intervalT = 0.2;
    //clientNum = 2;
    for(int i = 0; i < clientNum; i++)
    {
        nodes.Get(i+1)->SetWeight(weights[i]);
        apps = client.Install(nodes.Get(i+1));
        apps.Start(Seconds(1.0+intervalT*i));
        apps.Stop(Seconds(15.0));
    }

    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.Install(nodes);

    Simulator::Stop(Seconds(stopTime));

    monitor->SerializeToXmlFile("MyResult/FlowPerformance.xml", true, true);

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
