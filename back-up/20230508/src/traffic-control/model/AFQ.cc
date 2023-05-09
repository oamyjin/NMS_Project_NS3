#include "AFQ.h"

#include "ns3/Flow_pl.h"
#include "ns3/Level_afq.h"
#include "ns3/gearbox-pkt-tag.h"
#include "ns3/log.h"
#include "ns3/ppp-header.h"
#include "ns3/ptr.h"
#include "ns3/queue-disc.h"
#include "ns3/queue.h"
#include "ns3/simulator.h"
#include "ns3/flow-id-tag.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

namespace ns3
{
NS_LOG_COMPONENT_DEFINE("AFQ");
NS_OBJECT_ENSURE_REGISTERED(AFQ);

AFQ::AFQ()
    : AFQ(DEFAULT_VOLUME)
{
}

AFQ::AFQ(int volume)
{
    NS_LOG_FUNCTION(this);
    this->volume = volume;
    currentRound = 0;
    pktCount = 0; // 07072019 Peixuan
    flowNo = 0;
    typedef std::map<string, Flow_pl*> FlowMap;
    FlowMap flowMap;

    for (int i = 0; i < DEFAULT_VOLUME; i++)
    {
        levels[i].SetLevel(i);
    }

   // initialize flow weights
    ifstream infile;
    infile.open("scratch/weights.txt");
    infile >> totalFlowNum;
    for (int i = 0; i < totalFlowNum; i++)
    {
        int temp = 0;
        infile >> temp;
        weights.push_back(temp);
    }
    infile.close();
    cout << "AFQ CREATED" << endl;
    NS_LOG_FUNCTION(this);
}

int
AFQ::findearliestpacket(int volume)
{
    int level_min = -1;

    for (int i = 0; i < volume; i++)
    {
        const QueueItem* item = levels[i].fifopeek1();
        if (item != NULL)
        {
            level_min = i;
        }
    }
    return level_min;
}

void
AFQ::setCurrentRound(int cr)
{
    this->currentRound = max(cr, this->currentRound); // 20220729 Jiajin
    int level_currentFifo = cr / GRANULARITY_PER_FIFO % FIFO_PER_LEVEL;
    levels[0].setCurrentIndex(level_currentFifo);
    // cout<<"dp= "<< currentRound<<"setcurrent index = "<<level_currentFifo<<endl;
}

void
AFQ::setPktCount(int pktCount)
{
    this->pktCount = pktCount;
}

int
AFQ::RankComputation(QueueDiscItem* item, Flow_pl* currFlow)
{
    // calculate the rank(departureRound) value
    // float curWeight = currFlow->getWeight();
    int curLastDepartureRound = currFlow->getLastFinishRound();
    int curStartRound = max(currentRound, curLastDepartureRound);

    // int curDeaprtureRound = (int)(curStartRound + curWeight);
    return curStartRound;
}

string
AFQ::getFlowLabel(Ptr<QueueDiscItem> item)
{
     FlowIdTag tag;
    Packet* packet = GetPointer(item->GetPacket());
    packet->PeekPacketTag(tag);
    //cout << "pktsize:" << packet->GetSize() << " uid:" << packet->GetUid() << endl;
    stringstream ss;
    ss << tag.GetFlowId();
    string flowLabel = ss.str();
    cout << "tag.GetFlowId():" << tag.GetFlowId() << " ss:" << flowLabel << endl;
    return flowLabel;
}

Flow_pl*
AFQ::getFlowPtr(string flowlabel)
{
    NS_LOG_DEBUG("getFlowPtr");
	// ack or fin pkt flow
	flowlabel = flowlabel.substr(0, 8);
	cout << "flowlabel" << flowlabel << endl;
    if (stoi(flowlabel) > totalFlowNum){
		cout << "flowlabel1:" << flowlabel << endl;
		//ackFlowNum += 1;
		//return this->insertNewFlowPtr(to_string(totalFlowNum + 100 + ackFlowNum), stoi(flowlabel), DEFAULT_WEIGHT, DEFAULT_BURSTNESS);
        return this->insertNewFlowPtr(flowlabel, stoi(flowlabel), DEFAULT_WEIGHT, DEFAULT_BURSTNESS);
    }
    string key = convertKeyValue(flowlabel);
    // insert new flows with assigned weight
    if (flowMap.find(key) == flowMap.end())
    {
        int weight = weights.at(flowNo);
        flowNo++;
        return this->insertNewFlowPtr(flowlabel, flowNo, weight, DEFAULT_BURSTNESS);
    }
	cout << "key2:" << key << endl;
    return this->flowMap[key];
}

bool
AFQ::DoEnqueue(Ptr<QueueDiscItem> item)
{
    enque += 1;
    uid = uid + 1;

   // 1. calculate the incoming pkt's rank
    string flowlabel = getFlowLabel(item);
    Flow_pl* currFlow = getFlowPtr(flowlabel);
    int flowid = currFlow->getFlowNo();
    // calculate rank value, which is the value of departure round in this case
    int departureRound = RankComputation(GetPointer(item), currFlow);
    // departureRound = weights.at(flowid - 1);
    GearboxPktTag tag;
    Packet* packet = GetPointer(item->GetPacket());
    packet->PeekPacketTag(tag);
    packet->AddPacketTag(
        GearboxPktTag(currFlow->getFlowNo(), uid, departureRound, Simulator::Now().GetSeconds()));


    // std::ofstream thr ("MyResult/pktsList/rankVtDifference.dat", std::ios::out | std::ios::app);
    // thr << departureRound - currentRound << " ";

    if (departureRound > ((currentRound / GRANULARITY_PER_FIFO) * GRANULARITY_PER_FIFO +
                          (GRANULARITY_PER_FIFO * FIFO_PER_LEVEL) - 1))
    {
        ////cout << " DROP!!! TOO LARGE DEPARTURE_ROUND!  departureRound:"  << departureRound << "
        /// currentRound:" << currentRound << endl;

        // Drop(item);
        DropBeforeEnqueue(item, "Reason for dropping item");

        drop += 1;
        int maxRange = (currentRound / GRANULARITY_PER_FIFO) * GRANULARITY_PER_FIFO +
                       (GRANULARITY_PER_FIFO * FIFO_PER_LEVEL) - 1;
        std::ofstream thr3("MyResult/pktsList/drop.dat", std::ios::out | std::ios::app);
        thr3 << Simulator::Now().GetSeconds() << " dp:" << departureRound << " max:" << maxRange
             << " diff:" << departureRound - maxRange << " vt:" << currentRound
             << " fid:" << currFlow->getFlowNo() << endl;
        dropCount = dropCount + 1;
        dropCountA = dropCountA + 1;

        this->setDropCount(dropCount);
        return false; // 07072019 Peixuan: exceeds the maximum round
    }
    int curBrustness = currFlow->getBurstness();
    if ((departureRound - currentRound) >= curBrustness)
    {
        ////cout << " DROP!!! TOO BURST!  departureRound:"  << departureRound << " currentRound:" <<
        /// currentRound << " curBrustness:" << curBrustness << endl;

        // Drop(item);
        DropBeforeEnqueue(item, "Reason for dropping item");

        drop += 1;
        std::ofstream thr3("MyResult/pktsList/drop.dat", std::ios::out | std::ios::app);
        thr3 << Simulator::Now().GetSeconds() << " " << 0 << endl;
        dropCount = dropCount + 1;
        dropCountC = dropCountC + 1;
        this->setDropCount(dropCount);
        return false; // 07102019 Peixuan: exceeds the maximum brustness
    }

    int index = departureRound / GRANULARITY_PER_FIFO % FIFO_PER_LEVEL;

    if (levels[0].fifoEnque(GetPointer(item), index, currFlow->getFlowNo()) != 0)
    { // re = item

        // Drop(item);
        DropBeforeEnqueue(item, "Reason for dropping item");

        std::ofstream thr5("MyResult/pktsList/drop.dat", std::ios::out | std::ios::app);
        thr5 << Simulator::Now().GetSeconds() << " " << 0 << endl;
        drop += 1;
        dropCount = dropCount + 1;
        dropCountB = dropCountB + 1;
        this->setDropCount(dropCount);
        return false;
    }
    else
    {
        Record("EnqueuedPktsList.txt", departureRound, item);
        NS_LOG_INFO("At time " << Simulator::Now().GetSeconds() << " Enque " << packet);
        this->updateFlowPtr(departureRound, flowlabel, currFlow);
        levels[0].addSchePkt(uid, departureRound); // record into the map which records all pkts who
                                                   // are currently in the system
        return true;
    }
}

bool
AFQ::LevelEnqueue(QueueDiscItem* item, int flowid, int departureRound, int uid)
{
    bool result;
    // if there is inversion, for example, enqueued pkt is smaller than vt, enqueue to current fifo
    // in level 0
    AddTag(flowid, departureRound, uid, item);
    result = FifoEnqueue(item, departureRound / GRANULARITY_PER_FIFO % FIFO_PER_LEVEL, 0);
    return result;
}

bool
AFQ::FifoEnqueue(QueueDiscItem* item, int index, int level)
{
    ////cout<<endl;
    ////cout<<"Gearbox FifoEnqueue <<<<<<<<<<<<<<<<Start"<<endl;
    Packet* packet = GetPointer(item->GetPacket());
    GearboxPktTag tag;
    packet->PeekPacketTag(tag);
    QueueDiscItem* re = levels[level].fifoEnque(item, index, tag.GetFlowNo());

    if (re != 0)
    { //?if(re != 0)

        
        // Drop(re);
        DropBeforeEnqueue(re, "Reason for dropping item");

        std::ofstream thr5("MyResult/pktsList/drop.dat", std::ios::out | std::ios::app);
        thr5 << Simulator::Now().GetSeconds() << " " << 0 << endl;
        std::ofstream thr6("MyResult/pktsList/Level0_fifo_drop.dat", std::ios::out | std::ios::app);
        thr6 << (index - levels[0].getEarliestFifo() + FIFO_PER_LEVEL) % FIFO_PER_LEVEL << " ";
        drop += 1;
        dropCount = dropCount + 1;
        dropCountB = dropCountB + 1;
        this->setDropCount(dropCount);
        return false;
    }
    else
    {
        return true;
    }
}

void
AFQ::AddTag(int flowid, int departureRound, int uid, QueueDiscItem* item)
{
    GearboxPktTag tag;
    Packet* packet = GetPointer(item->GetPacket());
    packet->PeekPacketTag(tag);
    packet->AddPacketTag(GearboxPktTag(flowid, uid, departureRound, Simulator::Now().GetSeconds()));
}

Ptr<QueueDiscItem>
AFQ::DoDequeue()
{
    deque += 1;
    ////cout<<endl;
    ////cout <<"Gearbox DoDequeue<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Start"<<endl;
    int earliestLevel = findearliestpacket(DEFAULT_VOLUME);
    if ((earliestLevel == -1))
    {
        return NULL;
    }
    Ptr<QueueDiscItem> re = NULL;
    // cout<<"earliestlevel"<<earliestLevel<<endl;

    re = FifoDequeue(earliestLevel);

    // Set the finish time of flow
    string flowlabel = getFlowLabel(re);
    Flow_pl* currFlow = getFlowPtr(flowlabel);
    currFlow->setFinishTime(Simulator::Now().GetSeconds());
    GearboxPktTag tag;
    Packet* packet = GetPointer(GetPointer(re)->GetPacket());
    packet->PeekPacketTag(tag);
    int departureround = tag.GetDepartureRound();
    Record("DequeuedPktsList.txt", departureround, re);

    for (int i = 0; i < DEFAULT_VOLUME; i++)
    {
        int currentfifo = levels[i].getEarliestFifo();
        // cout<<currentfifo;
        if (currentfifo == -1)
        {
            currentfifo = 0;
        }
    }
    ////cout <<"Gearbox DoDequeue<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<End"<<endl;

    // update the map which records all pkts currently in the scheduler
    levels[0].removeSchePkt(tag.GetUid());
    int inversion = levels[0].cal_inversion_mag(departureround);
    if (inversion > 0)
    {
        inv_count += 1;
        inv_mag += inversion;
    }
    std::ofstream thr2("MyResult/inversion_record.dat", std::ios::out);
    thr2 << "count: " << inv_count << "  magnitude: " << inv_mag << endl;

    std::ofstream thr3("MyResult/CountStat.dat", std::ios::out);
    thr3 << Simulator::Now().GetSeconds() << " drop:" << drop << " dropCountA:" << dropCountA
         << " dropCountB:" << dropCountB << " flowNo:" << flowNo << std::endl;
    // remove packet tag
    GetPointer(re->GetPacket())->RemovePacketTag(tag);
    return re;
}

Ptr<QueueDiscItem>
AFQ::FifoDequeue(int earliestLevel)
{
    ////cout<<endl;
    ////cout <<"Gearbox FifoDequeue<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Start"<<endl;
    QueueDiscItem* fifoitem;

    int earliestFifo = levels[earliestLevel].getEarliestFifo();
    fifoitem = levels[earliestLevel].fifoDeque(earliestFifo);
    if (fifoitem != 0)
    {
        dequeCount += 1; // sucessfully deque from fifo, deque+1
    }
    GearboxPktTag tag;
    fifoitem->GetPacket()->PeekPacketTag(tag);

    // cout<<"tag.getDepartureRound"<<tag.GetDepartureRound()<<endl;
    this->setCurrentRound(tag.GetDepartureRound());
    // this->setCurrentRound(0); //20220620 Jiajin
    Ptr<QueueDiscItem> p = fifoitem;
    setPktCount(pktCount - 1);
    ////cout<<"Deque pkt "<<tag.GetDepartureRound()<<" from fifo in level "<< 0 <<endl;

    ////cout <<"Gearbox FifoDequeue<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<End"<<endl;
    return p;
}

void
AFQ::setDropCount(int count)
{
    this->dropCount = count;
}

int
AFQ::getDropCount()
{
    return dropCount;
}

Flow_pl*
AFQ::insertNewFlowPtr(string fid, int fno, int weight, int burstness)
{  
    NS_LOG_DEBUG("insertNewFlowPtr");
    Flowlist.push_back(fid);
    string key = convertKeyValue(fid);
	cout << "key0:" << key << endl;
    Flow_pl* newFlowPtr = new Flow_pl(fid, fno, weight, burstness);
    newFlowPtr->setStartTime(Simulator::Now().GetSeconds());
    this->flowMap.insert(pair<string, Flow_pl*>(key, newFlowPtr));
	cout << "key1:" << key << endl;
    return this->flowMap[key];
}

int
AFQ::updateFlowPtr(int departureRound, string fid, Flow_pl* flowPtr)
{ 
    string key = convertKeyValue(fid);
    // update flow info
    flowPtr->setLastFinishRound(
        departureRound +
        flowPtr->getWeight()); // only update last packet finish time if the packet wasn't dropped
    this->flowMap.insert(pair<string, Flow_pl*>(key, flowPtr));
    return 0;
}

string
AFQ::convertKeyValue(string fid)
{ 
    NS_LOG_DEBUG("convertKeyValue");
    stringstream ss;
    ss << fid;
    string key = ss.str();

    return key;
}

Ptr<QueueDiscItem>
AFQ::DoRemove(void)
{
    // NS_LOG_FUNCTION (this);
    return 0;
}

Ptr<const QueueDiscItem>
AFQ::DoPeek(void) const
{
    // NS_LOG_FUNCTION (this);
    return 0;
}

AFQ::~AFQ()
{
    NS_LOG_FUNCTION(this);
}

TypeId
AFQ::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::AFQ")
                            .SetParent<QueueDisc>()
                            .SetGroupName("TrafficControl")
                            .AddConstructor<AFQ>();
    return tid;
}

bool
AFQ::CheckConfig(void)
{
    NS_LOG_FUNCTION(this);
    if (GetNQueueDiscClasses() > 0)
    {
        NS_LOG_ERROR("AFQ cannot have classes");
        return false;
    }
    if (GetNPacketFilters() != 0)
    {
        NS_LOG_ERROR("AFQ needs no packet filter");
        return false;
    }
    if (GetNInternalQueues() > 0)
    {
        NS_LOG_ERROR("AFQ cannot have internal queues");
        return false;
    }
    return true;
}

void
AFQ::InitializeParams(void)
{
    NS_LOG_FUNCTION(this);
}

void
AFQ::Record(string fname, int departureRound, Ptr<QueueDiscItem> item)
{
    GearboxPktTag tag;
    item->GetPacket()->PeekPacketTag(tag);
    // int uid = tag.GetUid();
    int dp = tag.GetDepartureRound();
    // int uid = tag.GetUid();
    string path = "MyResult/pktsList/";
    path.append(fname);
    FILE* fp;
    ////cout<<path<<endl;
    fp = fopen(path.data(), "a+"); // open and write
    // fprintf(fp, "%s", "(");
    fprintf(fp, "%d", dp);
    /*fprintf(fp, "%s", ", ");
    fprintf(fp, "%d", currFlow->getFlowNo());
    fprintf(fp, "%s", ", ");
    fprintf(fp, "%d", uint32_t(ipHeader.GetSource().Get()));
    fprintf(fp, "%s", ", ");
    fprintf(fp, "%d", uint16_t (header.GetSourcePort()));
    fprintf(fp, "%s", ", ");
    fprintf(fp, "%f", Simulator::Now().GetSeconds());
    fprintf(fp, "%s", ")");
    fprintf(fp, "%s", "(");
    fprintf(fp, "%d", dp);
    fprintf(fp, "%s", ",");
    fprintf(fp, "%d", enque);
    fprintf(fp, "%s", ",");
    fprintf(fp, "%d", deque);
    fprintf(fp, "%s", ",");
    fprintf(fp, "%d", drop);
    fprintf(fp, "%s", ",");
    fprintf(fp, "%f", Simulator::Now().GetSeconds());
    fprintf(fp, "%s", ")");*/
    fprintf(fp, "\t");
    fclose(fp);

    FILE* fpl0;

    fpl0 = fopen("MyResult/pktsList/Level0", "a+"); // open and write
    fprintf(fpl0, "%f", Simulator::Now().GetSeconds());
    fprintf(fpl0, "\t%d", levels[0].getFifoMaxNPackets());
    fprintf(fpl0, "\n");
    fclose(fpl0);
    /*FILE *fpl1;
    fpl1 = fopen("MyResult/pktsList/Level1", "a+"); //open and write
    fprintf(fpl1, "%f", Simulator::Now().GetSeconds());
    fprintf(fpl1, "\t%d", levels[1].getFifoMaxNPackets());
    fprintf(fpl1, "\n");
    fclose(fpl1);
    FILE *fpl2;
    fpl2 = fopen("MyResult/pktsList/Level2", "a+"); //open and write
    fprintf(fpl2, "%f", Simulator::Now().GetSeconds());
    fprintf(fpl2, "\t%d", levels[2].getFifoMaxNPackets());
    fprintf(fpl2, "\n");
    fclose(fpl2);*/
}

void
AFQ::RecordFlow(string flowlabel, int departureRound)
{
    string path = "MyResult/pktsList/";
    path.append(flowlabel);
    FILE* fp;
    ////cout<<path<<endl;
    fp = fopen(path.data(), "a+"); // open and write
    // fprintf(fp, "%f", Simulator::Now().GetSeconds());
    fprintf(fp, "%d", departureRound);
    fprintf(fp, "\t");
    fclose(fp);
}

void
AFQ::Rate(int enqueCount, int dequeCount, int overflowCount, int reloadCount, int migrationCount)
{
    curTime = Simulator::Now();
    if ((curTime.GetSeconds() - prevTime1.GetSeconds()) > 1)
    {
        prevTime1 = curTime;
    }
}

void
AFQ::PacketRecord(string fname, int departureRound, Ptr<QueueDiscItem> item)
{
    // get pkt information
    GearboxPktTag tag;
    item->GetPacket()->PeekPacketTag(tag);
    /*int fifoenque = tag.GetFifoenque();
    int fifodeque = tag.GetFifodeque();
    int pifoenque = tag.GetPifoenque();
    int pifodeque = tag.GetPifodeque();
    int overflow = tag.GetOverflow();
    int reload = tag.GetReload();
    int dp = tag.GetDepartureRound();
    int migration = tag.GetMigration();
    int uid = tag.GetUid();
    double queuingDelay = tag.GetDequeTime() - tag.GetEnqueTime();
    enqueCount += fifoenque + pifoenque;
    dequeCount += fifodeque + pifodeque;
    overflowCount += overflow;
    reloadCount +=  reload;
    queuingCount += queuingDelay;
    migrationCount += migration;*/
    // Rate(enqueCount,dequeCount,overflowCount,reloadCount,migrationCount);
}

void
AFQ::tagRecord(int flowiid, int uid, int departureRound, Ptr<QueueDiscItem> item)
{
    // GearboxPktTag tag;
    // item->GetPacket()->PeekPacketTag(tag);
    // int dp = tag.GetDepartureRound();
    // int uid = tag.GetUid();
    FILE* fp2;

    string path = "MyResult/pktsList/tagRecord";
    // path.append(to_string(flowiid));
    path.append(".txt");
    fp2 = fopen(path.data(), "a+"); // open and write
    fprintf(fp2, "%f", Simulator::Now().GetSeconds());
    fprintf(fp2, "  %s", "vt:");
    fprintf(fp2, "%d", currentRound);
    fprintf(fp2, "  %s", "dp:");
    fprintf(fp2, "%d", departureRound);
    fprintf(fp2, "  %s", "uid:");
    fprintf(fp2, "%d", uid);
    fprintf(fp2, "  %s", "fifoenque:");
    fprintf(fp2, "%d", 0);
    fprintf(fp2, "%s", "  ");
    fprintf(fp2, "%s", "fifodeque:");
    fprintf(fp2, "%d", 0);
    fprintf(fp2, "%s", "  ");
    fprintf(fp2, "%s", "overflow:");
    fprintf(fp2, "%d", 0);
    fprintf(fp2, "%s", "  ");
    fprintf(fp2, "%s", "queueing_delay:");
    fprintf(fp2, "%lf", 0.000000);
    fprintf(fp2, "%s", "  ");
    fprintf(fp2, "%s", "enquetime:");
    fprintf(fp2, "%lf", 0.000000);
    fprintf(fp2, "%s", "  ");
    fprintf(fp2, "%s", "dequetime:");
    fprintf(fp2, "%lf", 0.000000);
    fprintf(fp2, "\n");
    fclose(fp2);
}
} // namespace ns3
