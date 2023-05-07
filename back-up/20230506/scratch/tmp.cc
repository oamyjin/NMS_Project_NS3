/*
fattree topo
with queuedisc

Version description:
    IP assignemnt is done
    ecmp by flow
    record flow info in ./xml

Modifed TCP parameters

*/

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/traffic-control-module.h"

using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("FATTREE_SIMULATION");

const uint32_t CoreNum = 4;
const uint32_t PodNum = 4;
const uint32_t AggPerPod = 2;
const uint32_t TorPerPod = 2;
const uint32_t ServerPerTor = 32;
const uint32_t ServerPerPod = ServerPerTor * TorPerPod;
const uint32_t NodeNumPerPod = ServerPerPod + TorPerPod + AggPerPod;
const uint32_t ServerTotalNum = ServerPerPod * PodNum;

const char* Node2Tor_Capacity = "10Gbps";
const char* Node2Tor_Delay = "10ns";
const char* Tor2Agg_Capacity = "40Gbps";
const char* Tor2Agg_Delay = "1us";
const char* Agg2Core_Capacity = "40Gbps";
const char* Agg2Core_Delay = "1us";
const char* AppDataRate = "10Gbps";

double simulator_stop_time = 5.0;
bool ECMProuting = true;
const uint32_t PacketSize = 1448;

// only for ip assignment
const char* mask_core = "255.255.255.0";
const char* mask_pod = "255.255.255.0";
const char* mask_server = "255.255.255.0";
Ipv4Address serverAddress[ServerTotalNum];
NodeContainer pods[PodNum];
NodeContainer core;
ifstream flowf;

struct FlowInput
{
    uint32_t src, dst, maxPacketCount, port, dport;
    double start_time, stop_time;
    uint32_t idx;
};

FlowInput flow_input = {0};
uint32_t flow_num;
uint32_t totalPktSize = 0;
uint32_t total_send = 0;

/**
 * Define Application Here
 */
class MyApp : public Application
{
  public:
    MyApp();
    virtual ~MyApp();
    /**
     * Register this type.
     * \return The TypeId.
     */
    static TypeId GetTypeId(void);
    void Setup(Ptr<Socket> socket,
               Address address,
               uint32_t packetSize,
               uint32_t nPackets,
               DataRate dataRate,
               uint32_t flowId,
               double stoptime);

  private:
    virtual void StartApplication(void);
    virtual void StopApplication(void);
    void ScheduleTx(void);
    void SendPacket(void);
    Ptr<Socket> m_socket;
    Address m_peer;
    uint32_t m_packetSize;
    uint32_t m_nPackets;
    DataRate m_dataRate;
    EventId m_sendEvent;
    bool m_running;
    uint32_t m_packetsSent;
    uint32_t m_flowId;
    double m_stoptime;
};

MyApp::MyApp()
    : m_socket(0),
      m_peer(),
      m_packetSize(0),
      m_nPackets(0),
      m_dataRate(0),
      m_sendEvent(),
      m_running(false),
      m_packetsSent(0),
      m_stoptime(0.0)
{
}

MyApp::~MyApp()
{
    m_socket = 0;
}

/* static */
TypeId
MyApp::GetTypeId(void)
{
    static TypeId tid =
        TypeId("MyApp").SetParent<Application>().SetGroupName("Tutorial").AddConstructor<MyApp>();
    return tid;
}

void
MyApp::Setup(Ptr<Socket> socket,
             Address address,
             uint32_t packetSize,
             uint32_t nPackets,
             DataRate dataRate,
             uint32_t flowId,
             double stoptime)
{
    m_socket = socket;
    m_peer = address;
    m_packetSize = packetSize;
    m_nPackets = nPackets;
    m_dataRate = dataRate;
    m_flowId = flowId;
    m_stoptime = stoptime;
}

void
MyApp::StartApplication(void)
{
    m_running = true;
    m_packetsSent = 0;
    m_socket->Bind();
    m_socket->Connect(m_peer);
    SendPacket();
}

void
MyApp::StopApplication(void)
{
    m_running = false;
    if (m_sendEvent.IsRunning())
    {
        Simulator::Cancel(m_sendEvent);
    }
    if (m_socket)
    {
        m_socket->Close();
    }
}

void
MyApp::SendPacket(void)
{
    Ptr<Packet> packet = Create<Packet>(m_packetSize);
    m_socket->Send(packet);
    total_send++;
    m_packetsSent++;
    if (m_packetsSent < m_nPackets)
    {
        ScheduleTx();
    }
}

void
MyApp::ScheduleTx(void)
{
    if (m_running)
    {
        Time tNext(Seconds(m_packetSize * 8 / static_cast<double>(m_dataRate.GetBitRate())));
        m_sendEvent = Simulator::Schedule(tNext, &MyApp::SendPacket, this);
    }
}

void
ReadFlowInput()
{
    cout << "==== ReadFlowInput ====" << endl;
    char line[200];           // storage for each line
    flowf.getline(line, 100); // get each line
    while (strlen(line) == 0)
    {
        flowf.getline(line, 100);
    }
    int in_cnt = sscanf(line,
                        "%d %d %d %d %d %lf %lf",
                        &(flow_input.src),
                        &(flow_input.port),
                        &(flow_input.dst),
                        &(flow_input.dport),
                        &(flow_input.maxPacketCount),
                        &(flow_input.start_time),
                        &(flow_input.stop_time));
    if (in_cnt == 6)
    { // no input of stop_time
        flow_input.stop_time = 0;
    }
    if (flow_input.src != 0)
    {
        if (flow_input.idx < flow_num)
        {
            totalPktSize += flow_input.maxPacketCount;
            cout << "flow_input.src:" << flow_input.src << " flow_input.dst:" << flow_input.dst
                 << endl;
            stringstream path;
            path << "scratch/GBResult/Rx/rx" << flow_input.src << ".dat"; // plotResult
            std::ofstream thr0(path.str(), std::ios::out | std::ios::app);
            thr0 << flow_input.start_time << " " << 0 << endl; //<< " tx:" << localThroutx  << endl;
        }
    }
}

void
ScheduleFlowInputs()
{
    cout << "==== ScheduleFlowInputs ====" << endl;
    while (flow_input.idx < flow_num && Seconds(flow_input.start_time) == Simulator::Now())
    {
        cout << "flow_input.src:" << flow_input.src << " sip:" << serverAddress[flow_input.src - 1] << " port:" << flow_input.port
             << " dst:" << flow_input.dst << " dip:" << serverAddress[flow_input.dst - 1] << " dport:" << flow_input.dport << endl;
        // dst server
        Address sinkAddress(InetSocketAddress(serverAddress[flow_input.dst - 1], flow_input.dport));
        PacketSinkHelper sinkHelper("ns3::TcpSocketFactory",
                                    InetSocketAddress(Ipv4Address::GetAny(), flow_input.dport));
        //cout << "\tflow_input.dst - 1:" << flow_input.dst - 1 << " (flow_input.dst - 1) / NodeNumPerPod:" << (flow_input.dst - 1) / NodeNumPerPod << " " << (flow_input.dst - 1) % NodeNumPerPod << endl;
        ApplicationContainer sinkApp = sinkHelper.Install(
            pods[(flow_input.dst - 1) / ServerPerPod].Get((flow_input.dst - 1) % ServerPerPod));
        sinkApp.Start(Seconds(0));
        sinkApp.Stop(Seconds(simulator_stop_time));
        // src server
        TypeId tid = TypeId::LookupByName("ns3::TcpNewReno");
        Config::Set("/NodeList/*/$ns3::TcpL4Protocol/SocketType", TypeIdValue(tid));
        Ptr<Socket> ns3TcpSocket = Socket::CreateSocket(
            pods[(flow_input.src - 1) / ServerPerPod].Get((flow_input.src - 1) % ServerPerPod),
            TcpSocketFactory::GetTypeId());
        ns3TcpSocket->SetAttribute("SndBufSize", ns3::UintegerValue(1438000000));
        Ptr<MyApp> app = CreateObject<MyApp>();
        app->Setup(
            ns3TcpSocket,
            sinkAddress,
            PacketSize,
            flow_input.maxPacketCount,
            DataRate(AppDataRate),
            flow_input.idx,
            flow_input.stop_time); // (TODO flow size) Ptr<Socket> socket, Address address, uint32_t
                                   // packetSize, uint32_t nPackets, DataRate dataRate
        pods[(flow_input.src - 1) / NodeNumPerPod]
            .Get((flow_input.src - 1) % NodeNumPerPod)
            ->AddApplication(app);
        app->SetStartTime(Seconds(flow_input.start_time) - Simulator::Now());
        cout << "start_time:" << flow_input.start_time << " stop_time:" << flow_input.stop_time
             << endl;
        if (flow_input.stop_time != 0)
        {
            app->SetStopTime(Seconds(flow_input.stop_time - Simulator::Now().GetSeconds()));
        }
        // get the next flow input
        flow_input.idx++;
        if (flow_input.idx < flow_num)
        {
            ReadFlowInput();
        }
    }

    // schedule the next time to run this function
    if (flow_input.idx < flow_num)
    {
        Simulator::Schedule(Seconds(flow_input.start_time) - Simulator::Now(), ScheduleFlowInputs);
    }
    else
    { // no more flows, close the file
        flowf.close();
    }
}

Ipv4Address node_id_to_ip(uint32_t id){
    return Ipv4Address(0x0b000001 + ((id / 256) * 0x00010000) + ((id % 256) * 0x00000100));
}

int
main(int argc, char* argv[])
{
    enum ECMP_MODE { ECMP_NONE, ECMP_RANDOM, ECMP_PER_FLOW, ECMP_RR, ECMP_RANDOM_FLOWLET, ECMP_DRILL };

    CommandLine cmd;
    cmd.Parse (argc, argv);
    Time::SetResolution (Time::NS);
    char line[200];
    //flowf.open("scratch/traffic_368flow_40G_128host_incast.txt");
    //flowf.open("scratch/traffic_420flow_10G_incast.txt");
    //flowf.open("scratch/500_flow_640G_095_traffic.txt");
    //flowf.open("scratch/1000_flow_640G_095_traffic.txt");
    //flowf.open("scratch/traffic_1000_320G_07_256.txt");
    //flowf.open("scratch/traffic_fattree.txt");
    //flowf.open("scratch/traffic_4flows.txt");
    flowf.open("scratch/traffic.txt");
    flowf.getline(line, 100);
    sscanf(line, "%d", &(flow_num));
    cout << "flow_num:" << flow_num << endl;
    
    Config::SetDefault ("ns3::TcpSocket::DelAckTimeout", TimeValue(Seconds (0.00002412)));//0.00180 //delayed ack time out default is 200ms
    Config::SetDefault ("ns3::RttEstimator::InitialEstimation", TimeValue(Seconds (0.00000804))); //RTT(Propgation delay) = 2*(0.01+1+1+1+1+0.01) = 8.04us
    Config::SetDefault ("ns3::TcpSocketBase::MinRto", TimeValue(Seconds (0.0000402))); // 5RTT = 5*8.04 = 40.2us
    Config::SetDefault ("ns3::TcpSocket::ConnTimeout", TimeValue(Seconds (0.0000402)));// syn timeout 5rtt
    //Config::SetDefault ("ns3::TcpSocketBase::ClockGranularity", TimeValue(MilliSeconds (0.00804)));//RTT

    Config::SetDefault ("ns3::TcpSocket::DataRetries", UintegerValue(100));
    Config::SetDefault ("ns3::TcpSocket::ConnCount", UintegerValue(100));
    Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue(1448)); //default SegmentSize is 536 Bytes
    Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting", BooleanValue(ECMProuting));
    ns3::PacketMetadata::Enable ();
   
    PointToPointHelper Node2Tor;
    Node2Tor.SetDeviceAttribute("DataRate", StringValue(Node2Tor_Capacity));
    Node2Tor.SetChannelAttribute("Delay", StringValue(Node2Tor_Delay));
    Node2Tor.SetQueue ("ns3::DropTailQueue", "MaxPackets", UintegerValue(1));
    PointToPointHelper Tor2Agg;
    Tor2Agg.SetDeviceAttribute("DataRate", StringValue(Tor2Agg_Capacity));
    Tor2Agg.SetChannelAttribute("Delay", StringValue(Tor2Agg_Delay));
    Tor2Agg.SetQueue ("ns3::DropTailQueue", "MaxPackets", UintegerValue(1));
    PointToPointHelper Agg2Core;
    Agg2Core.SetDeviceAttribute("DataRate", StringValue(Agg2Core_Capacity));
    Agg2Core.SetChannelAttribute("Delay", StringValue(Agg2Core_Delay));
    Agg2Core.SetQueue ("ns3::DropTailQueue", "MaxPackets", UintegerValue(1));

    cout << "==== Create Core" << CoreNum << " ====" << endl;
    // create node containers
    core.Create(CoreNum);
    cout << "==== Create Pod" << PodNum << "*" << NodeNumPerPod << " ====" << endl;
    for (int i = 0; i < (int)PodNum; i++)
    {
        pods[i].Create(NodeNumPerPod);
    }

    cout << "==== Install InternetStack ====" << endl;
    InternetStackHelper Stack;
    for (int i = 0; i < (int)PodNum; i++)
    {
        Stack.Install(pods[i]);
    }
    Stack.Install(core);

    cout << "==== Install NetDevice ====" << endl;
    // Creating Topology, connecting by NIC between nodes
    NetDeviceContainer podDev[PodNum][NodeNumPerPod];
    cout << "\tpodDev" << "[" << PodNum << "][" << NodeNumPerPod << "]" << endl;
    // server[0 ~ ServerPerPod-1]
    // tor[ServerPerPod ~ ServerPerPod+TorPerPod-1] 
    // agg[ServerPerPod+TorPerPod ~ NodeNumPerPod-1]
    for (int p = 0; p < (int)PodNum; p++)
    {
        cout << "\tpod:" << p << endl;
        // server to tor
        for (int t = 0; t < (int)TorPerPod; t++)
        {
            int tor_id = ServerPerPod + t;
            for (int n = 0; n < (int)ServerPerTor; n++)
            {
                int server_id = t * ServerPerTor + n;
                cout << "\t\tnet_dev_id:" << server_id << " [server_id:" << server_id << " tor_id:" << tor_id << "]" << endl;
                podDev[p][server_id] =
                    Node2Tor.Install(pods[p].Get(server_id), pods[p].Get(tor_id));
            }
        }
        // tor to agg
        for (int a = 0; a < (int)AggPerPod; a++)
        {
            int agg_id = ServerPerPod + TorPerPod + a;
            for (int t = 0; t < (int)TorPerPod; t++)
            {
                int tor_id = ServerPerPod + t;
                int node_id = ServerPerPod + a * AggPerPod + t;
                cout << "\t\tnet_dev_id:" << node_id << " [tor_id:" << tor_id  << " agg_id:" << agg_id << "]" << endl;
                podDev[p][node_id] = Tor2Agg.Install(pods[p].Get(tor_id), pods[p].Get(agg_id));
            }
        }
    }
    // Core router connections: agg to core
    NetDeviceContainer coreDev[CoreNum][PodNum];
    int agg_group = 0;
    for (int c = 0; c < (int)CoreNum; c++)
    {
        cout << "\tcore:" << c << endl;
        if (c % (CoreNum / AggPerPod) == 0)
        {
            agg_group++;
        }
        for (int p = 0; p < (int)PodNum; p++)
        {
            int agg_id = ServerPerPod + TorPerPod + agg_group - 1;
            cout << "\t\tpod:" << p << " agg_id:" << agg_id << endl;
            coreDev[c][p] = Agg2Core.Install(pods[p].Get(agg_id), core.Get(c));
        }
    }

    cout << "==== Assign Ipv4Address ====" << endl;
    // Assign IP to each node
    Ipv4AddressHelper address;
    Ipv4InterfaceContainer pods_Iface[PodNum][NodeNumPerPod];
    for (int p = 0; p < (int)PodNum; p++)
    {
        cout << "\tPod" << p << endl;
        // server to tor
        for (int s = 0; s < (int)ServerPerPod; s++)
        {
            ostringstream subset;
            // Server-Tor: 10.(p+1).(server+1).0
            subset << "10." << p + 1 << "." << s + 1 << ".0";
            address.SetBase(subset.str().c_str(), mask_server);
            pods_Iface[p][s] = address.Assign(podDev[p][s]);
            //cout << "server_id_to_ip:" << node_id_to_ip(p*ServerPerPod+s) << endl;
            serverAddress[p*ServerPerPod+s] = pods_Iface[p][s].GetAddress(0);
            cout << "\t\tserver" << p*ServerPerPod+s << ":" << pods_Iface[p][s].GetAddress(0) << " tor_ip:" << pods_Iface[p][s].GetAddress(1) << endl;
        }
        // tor to agg
        for (int a = 0; a < (int)AggPerPod; a++)
        {
            for (int t = 0; t < (int)TorPerPod; t++)
            {
                int net_dev_id = ServerPerPod + a * AggPerPod + t;
                ostringstream subset;
                //10.(p+1).(serverPerPod+a*10+t+1).1
                subset << "10." << p + 1 << "." << ServerPerPod + a*10 + t + 1 << ".0";
                address.SetBase(subset.str().c_str(), mask_pod);
                pods_Iface[p][net_dev_id] = address.Assign(podDev[p][net_dev_id]);
                cout << "\t\tnet_dev_id" << net_dev_id << ":" << pods_Iface[p][net_dev_id].GetAddress(0) << " " << pods_Iface[p][net_dev_id].GetAddress(1) << "  (tor_id:" << ServerPerPod + t << " agg_id:" << ServerPerPod + TorPerPod + a << ")" << endl;
            }
        }
    }
    cout << "core ip" << endl;
    // Core router Ifaces
    Ipv4InterfaceContainer core_Iface[CoreNum][PodNum];
    for (int c = 0; c < (int)CoreNum; c++)
    {
        for (int p = 0; p < (int)PodNum; p++)
        {
            ostringstream subset;
            // 10.(c+1).(p+1).0
            subset << "10.0" << "." << 10*(c+1) + p + 1 << ".0";
            //subset << PodNum + 1 << "0." << c + 1 << "." << p + 1 << ".0";
            //cout << "subset:" << subset.str().c_str() << " mask_core:" << mask_core << " c:" << c << " p:" << p << endl;
            address.SetBase(subset.str().c_str(), mask_core);
            core_Iface[c][p] = address.Assign(coreDev[c][p]);
            
            cout << "\t\tcore_id" << c << ":" << core_Iface[c][p].GetAddress(0) << " " << core_Iface[c][p].GetAddress(1) << "  (c:" << c << " p:" << p << ")" << endl;
        }
    }

   // unintall traffic control
    TrafficControlHelper tch;
    for (int i = 0; i < (int)PodNum; i++){
        for (int j = 0; j < (int)NodeNumPerPod; j++){
            tch.Uninstall(podDev[i][j]);
        }
    }
    for (int i = 0; i < (int)CoreNum; i++){
        for (int j = 0; j < (int)PodNum; j++){
            tch.Uninstall(coreDev[i][j]);
        }
    }
    
    tch.SetRootQueueDisc ("ns3::SpPifo");
    //tch.SetRootQueueDisc ("ns3::FifoPifo");
    //tch.SetRootQueueDisc ("ns3::Fifo");
    //tch.SetRootQueueDisc ("ns3::Gearbox_pl_fid_flex"); // this is Sifter
    //tch.SetRootQueueDisc ("ns3::AFQ");
    //tch.SetRootQueueDisc ("ns3::AFQ_Pifo");
   
    // install scheduler
    for (int i = 0; i < (int)PodNum; i++){
        for (int j = 0; j < (int)NodeNumPerPod; j++){
            tch.Install(podDev[i][j].Get(0));
            tch.Install(podDev[i][j].Get(1));
        }
    }
    for (int i = 0; i < (int)CoreNum; i++){
        for (int j = 0; j < (int)PodNum; j++){ 
            tch.Install(coreDev[i][j].Get(0));
            tch.Install(coreDev[i][j].Get(1));
        }
    }


    // Routing tables
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();
    
    // Ptr<OutputStreamWrapper> routingStream =
    // Create<OutputStreamWrapper>("GBResult/global-routing-multi-switch-plus-router.routes",
    //                                 std::ios::out);
    // Ipv4GlobalRoutingHelper g;
    // g.PrintRoutingTableAllAt(Seconds(1), routingStream);

    cout << "==== Start Schedule ====" << endl;
    // Applications
    flow_input.idx = 0;
    if (flow_num > 0)
    {
        ReadFlowInput();
        Simulator::Schedule(Seconds(flow_input.start_time) - Simulator::Now(), ScheduleFlowInputs);
    }

    //Node2Tor.EnablePcapAll ("GBResult/FatTree");
    //Node2Tor.EnablePcapAll("GBResult/DCN_FatTree_Pcap");
    //AsciiTraceHelper ascii;
    //Node2Tor.EnableAsciiAll (ascii.CreateFileStream ("GBResult/myfirst.tr"));

    // Flow monitor
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    Simulator::Stop(Seconds(simulator_stop_time));
    Simulator::Run();

    flowMonitor->SerializeToXmlFile("GBResult/NameOfFile.xml", true, true);
    /*AsciiTraceHelper ascii;
    Node2Tor.EnableAsciiAll(ascii.CreateFileStream("GBResult/Node2Tor-static-routing-slash32.tr"));
    Node2Tor.EnablePcapAll("Node2Tor-static-routing-slash32");
    Tor2Agg.EnableAsciiAll(ascii.CreateFileStream("GBResult/Tor2Agg-static-routing-slash32.tr"));
    Tor2Agg.EnablePcapAll("Tor2Agg-static-routing-slash32");
    Agg2Core.EnableAsciiAll(ascii.CreateFileStream("GBResult/Agg2Core-static-routing-slash32.tr"));
    Agg2Core.EnablePcapAll("Agg2Core-static-routing-slash32");*/
    cout << "totalPkt:" << totalPktSize << endl;
    cout << "total_send:" << total_send << endl;

    NS_LOG_INFO("Running the Simulation.");
    NS_LOG_INFO("Done.");
    Simulator::Destroy();

    return 0;
}