#include "fifo-pifo.h"

#include "ns3/Replace_string.h"
#include "ns3/flow-id-tag.h"
#include "ns3/gearbox-pkt-tag.h"
#include "ns3/ipv4-header.h"
#include "ns3/ipv4-queue-disc-item.h"
#include "ns3/ipv6-header.h"
#include "ns3/log.h"
#include "ns3/object-factory.h"
#include "ns3/ppp-header.h"
#include "ns3/ptr.h"
#include "ns3/queue-disc.h"
#include "ns3/queue.h"
#include "ns3/seq-ts-header.h"
#include "ns3/simulator.h"
#include "ns3/socket.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("FifoPifo");
NS_OBJECT_ENSURE_REGISTERED(FifoPifo);

FifoPifo::FifoPifo()
{
    ObjectFactory factory;
    factory.SetTypeId("ns3::DropTailQueue<QueueDiscItem>");
    factory.Set("MaxSize", QueueSizeValue(QueueSize(QueueSizeUnit::PACKETS, 1)));
	for (int i = 0; i < DEFAULT_VOLUME; i++)
    {
        AddInternalQueue(factory.Create<InternalQueue>());
    }
    size = 0;
    maxUid = 0;
    currentRound = 0;

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

    cout << "FifoPifo CREATED" << endl;
}

bool
FifoPifo::DoEnqueue(Ptr<QueueDiscItem> item)
{
	cout << "EQ" << endl;
    cout << "size:" << size << " internalqs_rank:" << internalqs_rank.size() << endl;
    enque += 1;
    NS_LOG_FUNCTION(this);
    // 1. calculate the incoming pkt's rank
    string flowlabel = getFlowLabel(item);
	cout << "flowLabel:" << flowlabel << endl;
    Flow_pl* currFlow = getFlowPtr(flowlabel);	
    int rank = RankComputation(GetPointer(item), currFlow);
	cout << "rank:" << rank << endl;
    // int rank = weights.at(currFlow->getFlowNo() - 1);

    // 2. add tag values, including rank and uid
    GearboxPktTag tag;
    Packet* packet = GetPointer(item->GetPacket());
    packet->PeekPacketTag(tag);
    uid = uid + 1;
    packet->AddPacketTag(
        GearboxPktTag(currFlow->getFlowNo(), uid, rank, Simulator::Now().GetSeconds()));

    // Pifo Enqueue
    // TODO: currently drop once overflow regardless of rank
    if (internalqs_rank.size() < DEFAULT_VOLUME){
        for (int i = 0; i < DEFAULT_VOLUME; i++){
            if (GetInternalQueue(i)->GetNPackets() == 0){
                GetInternalQueue(i)->Enqueue(item);
                // 3. update the flow's last finish time
                this->updateFlowPtr(rank, flowlabel, currFlow);
                addSchePkt(uid, rank);
                size += 1;
                max_size = size > max_size ? size : max_size;
                internalqs_rank[i] = rank;
                cout << "{{{{{{{{{{{}}}}}}}}}}} i:" << i << " rank:" << rank << " " << internalqs_rank[i] << " uid:" << uid << " size:" << size << " flowNo:" << currFlow->getFlowNo() << endl;         
                cout << "EQ TRUE" << item << " internalqs_rank.size():" << internalqs_rank.size() << endl;
                return true;
            }
        }
    }
    else{
        //int tail_qid = find_tail_qid(internalqs_rank, rank);
        //if (tail_qid == -1){
            DropBeforeEnqueue(item, "Overflow");
	        cout << "EQ FALSE" << item << endl;
            return false;
        //}
        //else{
            
        //}
    }
}

string
FifoPifo::getFlowLabel(Ptr<QueueDiscItem> item)
{
    NS_LOG_DEBUG("getFlowLabel");
    FlowIdTag tag;
    Packet* packet = GetPointer(item->GetPacket());
    packet->PeekPacketTag(tag);
    stringstream ss;
    //ss << ipHeader.GetSource().Get() << header.GetSourcePort();
	ss << tag.GetFlowId();
    string flowLabel = ss.str();
    //cout << ipHeader.GetSource().Get() << " " << header.GetSourcePort() << " flowLabel:" << flowLabel << endl;
	return flowLabel;
}

string
FifoPifo::convertKeyValue(string fid)
{
    NS_LOG_DEBUG("convertKeyValue");
    stringstream ss;
    ss << fid;
    string key = ss.str();

    return key;
}

Flow_pl*
FifoPifo::insertNewFlowPtr(string fid, int fno, int weight, int burstness)
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

Flow_pl*
FifoPifo::getFlowPtr(string flowlabel)
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

int
FifoPifo::updateFlowPtr(int departureRound, string fid, Flow_pl* flowPtr)
{
    NS_LOG_DEBUG("update FlowPtr");
    string key = convertKeyValue(fid);
    // update flow info
    flowPtr->setLastFinishRound(
        departureRound +
        flowPtr->getWeight()); // only update last packet finish time if the packet wasn't dropped
    this->flowMap.insert(pair<string, Flow_pl*>(key, flowPtr));

    return 0;
}

int
FifoPifo::RankComputation(QueueDiscItem* item, Flow_pl* currFlow)
{
    NS_LOG_DEBUG("Rank computation");
    // calculate the rank(departureRound) value
    int curLastFinishRound = currFlow->getLastFinishRound();
    // cout << "currentRound:" << currentRound << " curLastFinishRound:" << curLastFinishRound <<
    // endl;
    return max(currentRound, curLastFinishRound);
}

int FifoPifo::find_tail_qid(map<int, int>& M, int rank)
{
    // Declare vector of pairs
    vector<pair<int, int> > A;
 
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
 
    int tail_qid = -1;
    int tail_rank = rank;
    for (int i = 0; i < A.size(); i++){
        if (A[i].second > tail_rank){
            tail_rank = A[i].second;
            tail_qid = A[i].first;
        }
    }
    return tail_qid;
}

int FifoPifo::find_top_qid(map<int, int>& M)
{
    // Declare vector of pairs
    vector<pair<int, int> > A;
 
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
 
    int top_qid = 0;
    int top_rank = A[0].second;
    cout << "-------------------find_top_qid A.size():" << A.size() << " top_rank:" << top_rank << endl;
    for (int i = 0; i < A.size(); i++){
        cout << " i:" << i << " A[i].first:" << A[i].first << " A[i].second:" << A[i].second << endl;
        if (A[i].second < top_rank){
            top_rank = A[i].second;
            top_qid = A[i].first;
        }
    }
    cout << "top_qid:" << top_qid << endl;
    return top_qid;
}

Ptr<QueueDiscItem>
FifoPifo::DoDequeue()
{
	cout << "DQ" << endl;
    cout << "size:" << size << " internalqs_rank:" << internalqs_rank.size() << endl;
	//cout << "size:" << size << " pifo.Size():" << pifo.Size() << " GetInternalQueue(0):" << GetInternalQueue(0)->GetNPackets() << endl;
    deque += 1;
    
    if (size <= 0)
    {
        return 0;
    }
    // dequeue
    int top_queue_id = find_top_qid(internalqs_rank);
    cout << internalqs_rank[top_queue_id] << " " << GetInternalQueue(top_queue_id)->GetNPackets() << endl;
    Ptr<QueueDiscItem> item = GetInternalQueue(top_queue_id)->Dequeue();
    if (item == NULL){
        return 0;
    }
    cout << "item:" << item << endl;
    size -= 1;
    internalqs_rank.erase(top_queue_id);
    // update vt to be the pkt's rank
    GearboxPktTag tag;
    GetPointer(item->GetPacket())->PeekPacketTag(tag);
    currentRound = tag.GetDepartureRound();
    cout << "currentRound" << currentRound << " uid:" << tag.GetUid() << " fid:" << tag.GetFlowNo() << endl;
    // if (item != NULL)
    // {
    //     this->Record("DequeuedPktsList.txt", GetPointer(item));
    // }

    std::ofstream thr("MyResult/size.dat", std::ios::out | std::ios::app);
    thr << Simulator::Now().GetSeconds() << " " << size << endl;

    // update the map which records all pkts currently in the scheduler
	cout << "removeSchePkt" << endl;
    removeSchePkt(tag.GetUid());
    int inversion = cal_inversion_mag(currentRound);
    if (inversion > 0)
    {
        inv_count += 1;
        inv_mag += inversion;
    }
    std::ofstream thr2("MyResult/inversion_record.dat", std::ios::out);
    thr2 << "count: " << inv_count << "  magnitude: " << inv_mag << endl;

    std::ofstream thr3("MyResult/CountStat.dat", std::ios::out);
    dequed += 1;
    thr3 << Simulator::Now().GetSeconds() << " enque:" << enque << " deque:" << deque
         << " enqued:" << enqued << " dequed:" << dequed << " drop:" << drop << " drop_rate:" << 0.01*drop/enque << " flowNo:" << flowNo
         << std::endl;

    // Ptr<QueueDiscItem> item2 = StaticCast<QueueDiscItem>(GetInternalQueue(0)->Dequeue());
    // GearboxPktTag tag2;
    // GetPointer(item2->GetPacket())->PeekPacketTag(tag2);
    // while (tag2.GetUid() != tag.GetUid()){
    //     GetInternalQueue(0)->Enqueue(Ptr<QueueDiscItem>(item2));
    //     item2 = StaticCast<QueueDiscItem>(GetInternalQueue(0)->Dequeue());
    //     GetPointer(item2->GetPacket())->PeekPacketTag(tag2);
    // }
	// remove packet tag
    GetPointer(item->GetPacket())->RemovePacketTag(tag);
    cout << "AFterDQ=========:" << GetInternalQueue(0)->GetNPackets() << " " << size << endl;
    return item;
}

void
FifoPifo::Record(string fname, Ptr<QueueDiscItem> item)
{
    GearboxPktTag tag;
    item->GetPacket()->PeekPacketTag(tag);
    int dp = tag.GetDepartureRound();

    string path = "MyResult/pktsList/";
    path.append(fname);

    FILE* fp;
    fp = fopen(path.data(), "a+"); // open and write
    // fprintf(fp, "(");
    fprintf(fp, "%d", dp);
    // fprintf(fp, ",");
    // fprintf(fp, "%d", currentRound);
    // fprintf(fp, ")");
    fprintf(fp, "\t");
    fclose(fp);
}

Ptr<QueueDiscItem>
FifoPifo::DoRemove(void)
{
    // NS_LOG_FUNCTION (this);
    return 0;
}

Ptr<const QueueDiscItem>
FifoPifo::DoPeek(void)
{
    // NS_LOG_FUNCTION (this);
    Ptr<const QueueDiscItem> item = GetInternalQueue(find_top_qid(internalqs_rank))->Peek();

    if (!item)
    {
        NS_LOG_LOGIC("Queue empty");
        return nullptr;
    }
    return item;
}

FifoPifo::~FifoPifo()
{
    NS_LOG_FUNCTION(this);
}

TypeId
FifoPifo::GetTypeId(void)

{
    static TypeId tid = TypeId("ns3::FifoPifo")
                            .SetParent<QueueDisc>()
                            .SetGroupName("TrafficControl")
                            .AddConstructor<FifoPifo>()

        ;

    return tid;
}

bool
FifoPifo::CheckConfig(void)
{
    NS_LOG_FUNCTION(this);

    // if (GetNQueueDiscClasses() > 0)
    // {
    //     NS_LOG_ERROR("FifoPifo cannot have classes");
    //     return false;
    // }

    // if (GetNPacketFilters() != 0)
    // {
    //     NS_LOG_ERROR("FifoPifo needs no packet filter");
    //     return false;
    // }
    // if (GetNInternalQueues() > 0)
    // {
    //     NS_LOG_ERROR("FifoPifo cannot have internal queues");
    //     return false;
    // }
    return true;
}

void
FifoPifo::InitializeParams(void)
{
    NS_LOG_FUNCTION(this);
}

int
FifoPifo::addSchePkt(int uid, int departureRound)
{
    qpkts[uid] = departureRound;
    return qpkts.size();
}

int
FifoPifo::removeSchePkt(int uid)
{
    if (0 == qpkts.erase(uid))
    {
        cout << "cannot erase from map" << endl;
    }
    return qpkts.size();
}

int
FifoPifo::cal_inversion_mag(int dp)
{
    int magnitude = 0;
    for (auto it = qpkts.begin(); it != qpkts.end(); ++it)
    {
        // compare the dequeued dp with all pkts' dp in the scheduler
        if (dp > it->second)
        {
            magnitude += dp - it->second;
        }
    }
    return magnitude;
}

} // namespace ns3
