/*
 * Copyright (c) 2019 NITK Surathkal
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
 * Authors: Apoorva Bhargava <apoorvabhargava13@gmail.com>
 */

// Network topology
// orig:
//       n0 ---------- n1 ---------- n2 ---------- n3
//            10 Mbps       1 Mbps        10 Mbps
//             1 ms         10 ms          1 ms
//
// my:
//       n4 ------------
//                     |
//       n0 ---------- n1 ---------- n2 ---------- n3
//            10 Gbps       1 Gbps        10 Gbps
//             1 us         10 us          1 us
//
// - TCP flow from n0 to n3 using BulkSendApplication.
// - The following simulation output is stored in results/ in ns-3 top-level directory:
//   - cwnd traces are stored in cwndTraces folder
//   - queue length statistics are stored in queue-size.dat file
//   - pcaps are stored in pcap folder
//   - queueTraces folder contain the drop statistics at queue
//   - queueStats.txt file contains the queue stats and config.txt file contains
//     the simulation configuration.
// - The cwnd and queue length traces obtained from this example were tested against
//   the respective traces obtained from Linux Reno by using ns-3 Direct Code Execution.
//   See internet/doc/tcp.rst for more details.

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/flow-monitor-helper.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace ns3;
std::string dir = "results_test/";
Time stopTime = Seconds(12);
double srcStartTime = 10.0;
double dstStartTime = 10.0;
Time checkQSizeTimeInterval = Seconds(0.0001);
uint32_t segmentSize = 524;

// Function to check queue length of Router 1
void
CheckQueueSize(Ptr<QueueDisc> queue)
{
    uint32_t qSize = queue->GetCurrentSize().GetValue();

    // Check queue size every 1/100 of a second
    Simulator::Schedule(checkQSizeTimeInterval, &CheckQueueSize, queue);
    std::ofstream fPlotQueue(std::stringstream(dir + "queue-size.dat").str(),
                             std::ios::out | std::ios::app);
    fPlotQueue << Simulator::Now().GetSeconds() << " " << qSize << std::endl;
    fPlotQueue.close();
}

// Function to trace change in cwnd at n0
static void
CwndChange(uint32_t oldCwnd, uint32_t newCwnd)
{
    std::ofstream fPlotQueue(dir + "cwndTraces/n0.dat", std::ios::out | std::ios::app);
    fPlotQueue << Simulator::Now().GetSeconds() << " " << newCwnd / segmentSize << std::endl;
    fPlotQueue.close();
}

// Function to calculate drops in a particular Queue
static void
DropAtQueue(Ptr<OutputStreamWrapper> stream, Ptr<const QueueDiscItem> item)
{
    *stream->GetStream() << Simulator::Now().GetSeconds() << " 1" << std::endl;
}

// Trace Function for cwnd
void
TraceCwnd(uint32_t node, uint32_t cwndWindow, Callback<void, uint32_t, uint32_t> CwndTrace)
{
    Config::ConnectWithoutContext("/NodeList/" + std::to_string(node) +
                                      "/$ns3::TcpL4Protocol/SocketList/" +
                                      std::to_string(cwndWindow) + "/CongestionWindow",
                                  CwndTrace);
}


// Function to install BulkSend application
void
InstallBulkSend(Ptr<Node> node,
                Ipv4Address address,
                uint16_t port,
                std::string socketFactory,
                uint32_t nodeId,
                uint32_t cwndWindow,
                Time srcStartTime,
                Callback<void, uint32_t, uint32_t> CwndTrace)
{
    BulkSendHelper source(socketFactory, InetSocketAddress(address, port));
    source.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer sourceApps = source.Install(node);
    sourceApps.Start(srcStartTime);
    Simulator::Schedule(srcStartTime + Seconds(0.001), &TraceCwnd, nodeId, cwndWindow, CwndTrace);
    sourceApps.Stop(stopTime);
}

// Function to install sink application
void
InstallPacketSink(Ptr<Node> node, uint16_t port, std::string socketFactory)
{
    PacketSinkHelper sink(socketFactory, InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sinkApps = sink.Install(node);
    sinkApps.Start(Seconds(dstStartTime));
    sinkApps.Stop(stopTime);
}

int
main(int argc, char* argv[])
{
    uint32_t stream = 1;
    std::string socketFactory = "ns3::TcpSocketFactory";
    std::string tcpTypeId = "ns3::TcpNewReno";
    std::string recovery = "ns3::TcpClassicRecovery";
    bool isSack = true;
    uint32_t delAckCount = 0;
    char const *p2pRouterRate = "1Gbps";
    char const *p2pRouterDelay = "10us";
    char const *p2pLeafRate = "10Gbps"; //10Gbps
    char const *p2pLeafDelay = "1us";
    std::string qdiscTypeId = "ns3::AFQQueueDisc"; //"ns3::SppifoQueueDisc" "ns3::FifoQueueDisc" "ns3::PifoQueueDisc" "ns3::AFQQueueDisc"

    // LogComponentEnable ("QueueDisc", LOG_LEVEL_INFO);
    // LogComponentEnable ("SppifoQueueDisc", LOG_LEVEL_INFO);

    CommandLine cmd;
    cmd.AddValue("tcpTypeId",
                 "TCP variant to use (e.g., ns3::TcpNewReno, ns3::TcpLinuxReno, etc.)",
                 tcpTypeId);
    //cmd.AddValue("qdiscTypeId", "Queue disc for gateway (e.g., ns3::CoDelQueueDisc)", qdiscTypeId);
    cmd.AddValue("segmentSize", "TCP segment size (bytes)", segmentSize);
    cmd.AddValue("delAckCount", "Delayed ack count", delAckCount);
    cmd.AddValue("enableSack", "Flag to enable/disable sack in TCP", isSack);
    cmd.AddValue("stopTime",
                 "Stop time for applications / simulation time will be stopTime",
                 stopTime);
    cmd.AddValue("recovery", "Recovery algorithm type to use (e.g., ns3::TcpPrrRecovery", recovery);
    cmd.Parse(argc, argv);

    TypeId qdTid;
    NS_ABORT_MSG_UNLESS(TypeId::LookupByNameFailSafe(qdiscTypeId, &qdTid),
                        "TypeId " << qdiscTypeId << " not found");

    // Set recovery algorithm and TCP variant
    Config::SetDefault("ns3::TcpL4Protocol::RecoveryType",
                       TypeIdValue(TypeId::LookupByName(recovery)));
    if (tcpTypeId == "ns3::TcpWestwoodPlus")
    {
        // TcpWestwoodPlus is not an actual TypeId name; we need TcpWestwood here
        Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpWestwood::GetTypeId()));
        // the default protocol type in ns3::TcpWestwood is WESTWOOD
        Config::SetDefault("ns3::TcpWestwood::ProtocolType", EnumValue(TcpWestwood::WESTWOODPLUS));
    }
    else
    {
        TypeId tcpTid;
        NS_ABORT_MSG_UNLESS(TypeId::LookupByNameFailSafe(tcpTypeId, &tcpTid),
                            "TypeId " << tcpTypeId << " not found");
        Config::SetDefault("ns3::TcpL4Protocol::SocketType",
                           TypeIdValue(TypeId::LookupByName(tcpTypeId)));
    }

    // Create nodes
    NodeContainer leftNodes;
    NodeContainer rightNodes;
    NodeContainer routers;
    int num_clients = 6;
    routers.Create(2);
    leftNodes.Create(num_clients);
    rightNodes.Create(1);

    std::vector<NetDeviceContainer> leftToRouter;
    std::vector<NetDeviceContainer> routerToRight;

    // Create the point-to-point link helpers and connect two router nodes
    PointToPointHelper pointToPointRouter;
    pointToPointRouter.SetDeviceAttribute("DataRate", StringValue(p2pRouterRate));
    pointToPointRouter.SetChannelAttribute("Delay", StringValue(p2pRouterDelay));
    NetDeviceContainer r1r2ND = pointToPointRouter.Install(routers.Get(0), routers.Get(1));

    // Create the point-to-point link helpers and connect leaf nodes to router
    PointToPointHelper pointToPointLeaf;
    pointToPointLeaf.SetDeviceAttribute("DataRate", StringValue(p2pLeafRate));
    pointToPointLeaf.SetChannelAttribute("Delay", StringValue(p2pLeafDelay));
    for (int i = 0; i < num_clients; i++)
    {
        leftToRouter.push_back(pointToPointLeaf.Install(leftNodes.Get(i), routers.Get(0)));
    }
    routerToRight.push_back(pointToPointLeaf.Install(routers.Get(1), rightNodes.Get(0)));

    InternetStackHelper internetStack;

    internetStack.Install(leftNodes);
    internetStack.Install(rightNodes);
    internetStack.Install(routers);

    // Assign IP addresses to all the network devices
    Ipv4AddressHelper ipAddresses("10.0.0.0", "255.255.255.0");

    Ipv4InterfaceContainer r1r2IPAddress = ipAddresses.Assign(r1r2ND);
    ipAddresses.NewNetwork();

    std::vector<Ipv4InterfaceContainer> leftToRouterIPAddress;
    for (int i = 0; i < num_clients; i++)
    {
        leftToRouterIPAddress.push_back(ipAddresses.Assign(leftToRouter[i]));
        ipAddresses.NewNetwork();
    }

    std::vector<Ipv4InterfaceContainer> routerToRightIPAddress;
    routerToRightIPAddress.push_back(ipAddresses.Assign(routerToRight[0]));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Set default sender and receiver buffer size as 1MB
    Config::SetDefault("ns3::TcpSocket::SndBufSize", UintegerValue(1 << 20));
    Config::SetDefault("ns3::TcpSocket::RcvBufSize", UintegerValue(1 << 20));

    // Set default initial congestion window as 10 segments
    Config::SetDefault("ns3::TcpSocket::InitialCwnd", UintegerValue(10));

    // Set default delayed ack count to a specified value
    Config::SetDefault("ns3::TcpSocket::DelAckCount", UintegerValue(delAckCount));

    // Set default segment size of TCP packet to a specified value
    Config::SetDefault("ns3::TcpSocket::SegmentSize", UintegerValue(segmentSize));

    // Enable/Disable SACK in TCP
    Config::SetDefault("ns3::TcpSocketBase::Sack", BooleanValue(isSack));

    // Create directories to store dat files
    struct stat buffer;
    int retVal [[maybe_unused]];
    if ((stat(dir.c_str(), &buffer)) == 0)
    {
        std::string dirToRemove = "rm -rf " + dir;
        retVal = system(dirToRemove.c_str());
        NS_ASSERT_MSG(retVal == 0, "Error in return value");
    }
    std::string dirToSave = "mkdir -p " + dir;
    retVal = system(dirToSave.c_str());
    NS_ASSERT_MSG(retVal == 0, "Error in return value");
    //retVal = system((dirToSave + "/pcap/").c_str());
    //NS_ASSERT_MSG(retVal == 0, "Error in return value");
    retVal = system((dirToSave + "/queueTraces/").c_str());
    NS_ASSERT_MSG(retVal == 0, "Error in return value");
    retVal = system((dirToSave + "/cwndTraces/").c_str());
    NS_ASSERT_MSG(retVal == 0, "Error in return value");

    // Set default parameters for queue discipline
    Config::SetDefault(qdiscTypeId + "::MaxSize", QueueSizeValue(QueueSize("50p"))); //4MB

    // Install queue discipline on router
    TrafficControlHelper tch;
    tch.SetRootQueueDisc(qdiscTypeId);
    QueueDiscContainer qd;
    tch.Uninstall(routers.Get(0)->GetDevice(0));
    qd.Add(tch.Install(routers.Get(0)->GetDevice(0)).Get(0));

    // Enable BQL
    tch.SetQueueLimits("ns3::DynamicQueueLimits");

    // Calls function to check queue size
    Simulator::ScheduleNow(&CheckQueueSize, qd.Get(0));

    AsciiTraceHelper asciiTraceHelper;
    Ptr<OutputStreamWrapper> streamWrapper;

    // Create dat to store packets dropped and marked at the router
    streamWrapper = asciiTraceHelper.CreateFileStream(dir + "/queueTraces/drop-0.dat");
    qd.Get(0)->TraceConnectWithoutContext("Drop", MakeBoundCallback(&DropAtQueue, streamWrapper));

    // Install packet sink at receiver side
    uint16_t port = 50000;
    InstallPacketSink(rightNodes.Get(0), port, "ns3::TcpSocketFactory");

    // Install BulkSend application

    //int weights[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int weights[] = {10, 10, 10, 1, 1, 1};
    double intervalT[] = {0.0, 0.0, 0.0, 0.5, 1.0, 1.5};
    for (int i = 0; i < num_clients; i++)
    {
        leftNodes.Get(i)->SetWeight(weights[i]);
        InstallBulkSend(leftNodes.Get(i), // node id 2
                        routerToRightIPAddress[0].GetAddress(1),
                        port,
                        socketFactory,
                        i+2,
                        0,
                        Seconds(srcStartTime + intervalT[i]), 
                        MakeCallback(&CwndChange));
    }


    // Enable PCAP on all the point to point interfaces
    //pointToPointLeaf.EnablePcapAll(dir + "pcap/ns-3", true);

	//Flow monitor
	Ptr<FlowMonitor> flowMonitor;
	FlowMonitorHelper flowHelper;
	flowMonitor = flowHelper.InstallAll();

    Simulator::Stop(stopTime);
    Simulator::Run();

	flowMonitor->SerializeToXmlFile("MyResult/FlowPerformance.xml", true, true);

    // Store queue stats in a file
    std::ofstream myfile;
    myfile.open(dir + "queueStats.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    myfile << std::endl;
    myfile << "Stat for Queue 1";
    myfile << qd.Get(0)->GetStats();
    myfile.close();

    // Store configuration of the simulation in a file
    myfile.open(dir + "config.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    myfile << "qdiscTypeId " << qdiscTypeId << "\n";
    myfile << "stream  " << stream << "\n";
    myfile << "segmentSize " << segmentSize << "\n";
    myfile << "delAckCount " << delAckCount << "\n";
    myfile << "stopTime " << stopTime.As(Time::S) << "\n";
    myfile.close();

    Simulator::Destroy();

    return 0;
}
