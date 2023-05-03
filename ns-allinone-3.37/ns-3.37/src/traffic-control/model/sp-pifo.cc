/**
 * SP-PIFO:
 *       q0 ======
 *       q1 ======
 *          ...
 *   q(N-1) ======
 **/

#include "sp-pifo.h"

#include "ns3/log.h"
#include "ns3/object-factory.h"
#include "ns3/queue.h"
#include "ns3/socket.h"
#include "ns3/flow-id-tag.h"
#include "ns3/gearbox-pkt-tag.h"

#include "ns3/Replace_string.h"
#include "ns3/ipv4-queue-disc-item.h"
#include "ns3/ptr.h"
#include "ns3/simulator.h"

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

NS_LOG_COMPONENT_DEFINE("SpPifo");
NS_OBJECT_ENSURE_REGISTERED(SpPifo);

SpPifo::SpPifo()
{
    ObjectFactory factory;
    factory.SetTypeId("ns3::DropTailQueue<QueueDiscItem>");
    //factory.Set("MaxSize", QueueSizeValue(GetMaxSize()));
    factory.Set("MaxSize", QueueSizeValue(QueueSize(QueueSizeUnit::PACKETS, DEFAULT_VOLUME)));

    // uint32_t maxSize = DEFAULT_VOLUME;

    // factory.Set("Mode", EnumValue(Queue::QUEUE_MODE_PACKETS));
    // factory.Set("Mode", EnumValue(Queue<QueueDiscItem>::QUEUE_MODE_PACKETS));

    // factory.Set("MaxPackets", UintegerValue(DEFAULT_VOLUME));

    // create fifos and assign the fifo length
    for (int i = 0; i < DEFAULT_PQ; i++)
    {
        // fifos[i] = GetPointer(factory.Create<Queue>());
        // fifos[i] = GetPointer(factory.Create<InternalQueue>());
        AddInternalQueue(factory.Create<InternalQueue>());

        // uint32_t maxSize = DEFAULT_VOLUME;
        // fifos[i]->SetMaxPackets(maxSize);
    }

    maxUid = 0;
    currentRound = 0;

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
    cout << "SP-Pifo CREATED" << endl;
    NS_LOG_FUNCTION(this);
}

string
SpPifo::getFlowLabel(Ptr<QueueDiscItem> item)
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

string
SpPifo::convertKeyValue(string fid)
{
    stringstream ss;
    ss << fid;
    string key = ss.str();

    return key;
}

Flow_pl*
SpPifo::insertNewFlowPtr(string fid, int fno, int weight, int burstness)
{
    Flowlist.push_back(fid);
    string key = convertKeyValue(fid);
    Flow_pl* newFlowPtr = new Flow_pl(fid, fno, weight, burstness);
    std::ofstream thr1("MyResult/weight.dat", std::ios::out | std::ios::app);
    thr1 << fno << " " << weight << endl;
    newFlowPtr->setStartTime(Simulator::Now().GetSeconds());
    this->flowMap.insert(pair<string, Flow_pl*>(key, newFlowPtr));
    return this->flowMap[key];
}

Flow_pl*
SpPifo::getFlowPtr(string flowlabel)
{
    // // ack or fin pkt flow
    // if (stoi(flowlabel) > totalFlowNum){
    //     return this->insertNewFlowPtr(flowlabel, stoi(flowlabel), DEFAULT_WEIGHT, DEFAULT_BURSTNESS);
    // }
    // string key = convertKeyValue(flowlabel);
    // // insert new flows with assigned weight
    // if (flowMap.find(key) == flowMap.end())
    // {
    //     int weight = weights.at(flowNo);
    //     flowNo++;
    //     return this->insertNewFlowPtr(flowlabel, flowNo, weight, DEFAULT_BURSTNESS);
    // }
    // return this->flowMap[key];
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
SpPifo::updateFlowPtr(int departureRound, string fid, Flow_pl* flowPtr)
{
    string key = convertKeyValue(fid);
    // update flow info
    flowPtr->setLastFinishRound(
        departureRound +
        flowPtr->getWeight()); // only update last packet finish time if the packet wasn't dropped
    this->flowMap.insert(pair<string, Flow_pl*>(key, flowPtr));

    return 0;
}

int
SpPifo::RankComputation(QueueDiscItem* item, Flow_pl* currFlow)
{
    // calculate the rank(departureRound) value
    int curLastFinishRound = currFlow->getLastFinishRound();
    cout << "curLastFinishRound:" << curLastFinishRound << " currentRound:" << currentRound << endl;
    return max(currentRound, curLastFinishRound);
}

bool
SpPifo::DoEnqueue(Ptr<QueueDiscItem> item)
{
    enque += 1;
    NS_LOG_FUNCTION(this);
    cout << "EQ " << GetNPackets() << endl;

    uid = uid + 1;
    maxUid = uid > maxUid ? uid : maxUid;

    // 1. calculate the incoming pkt's rank
    string flowlabel = getFlowLabel(item);
    Flow_pl* currFlow = getFlowPtr(flowlabel);
    // int flowNo = currFlow->getFlowNo();
    int rank = RankComputation(GetPointer(item), currFlow);
    //int rank = weights.at(flowNo - 1);
    cout << "flowlabel:" << flowlabel << " rank:" << rank << endl;

    // add tag values, including rank and uid
    GearboxPktTag tag;
    Packet* packet = GetPointer(item->GetPacket());
    packet->PeekPacketTag(tag);
    packet->AddPacketTag(
        GearboxPktTag(currFlow->getFlowNo(), uid, rank, Simulator::Now().GetSeconds()));

    // 2. enque to the target queue with bottom-up comparisions
    for (int i = DEFAULT_PQ - 1; i >= 0; i--)
    {
        // push up
        if (rank >= bounds[i])
        {
            if (this->GetQueueSize(i) < DEFAULT_VOLUME)
            {
                // enque
                GetInternalQueue(i)->Enqueue(Ptr<QueueDiscItem>(item));

                enpkt += 1;
                size += 1; // trace size in sp-pifo

                std::ofstream thr("MyResult/SpPifoQBounds.dat", std::ios::out | std::ios::app);
                thr << rank << ": ";
                for (int k = 0; k < DEFAULT_PQ; k++)
                {
                    thr << bounds[k] << " ";
                }
                thr << " =up> ";

                this->Record("EnqueuedPktsList.txt", item);
                
                // update queue bound
                bounds[i] = rank;
                // record into the map which records all pkts who are currently in the system
                addSchePkt(uid, rank);
                // updat the flow's last finish time
                this->updateFlowPtr(rank, flowlabel, currFlow);
                fifoenque += 1;

                for (int k = 0; k < DEFAULT_PQ; k++)
                {
                    thr << bounds[k] << " ";
                }
                thr << endl;
                return true;
            }
            // fifo overflow
            else
            {
                // record queueing delay with Seq#
                // TcpHeader header;
                // GetPointer(item)->GetPacket()->PeekHeader(header);
                FlowIdTag tag;
                Packet* packet = GetPointer(item->GetPacket());
                packet->PeekPacketTag(tag);
                stringstream path;
                path << "MyResult/pktsDelay_flows/flow_" << currFlow->getFlowNo()
                     << "_pktdelay.dat"; // plotResult
                std::ofstream thr4(path.str(), std::ios::out | std::ios::app);
                // thr4 << header.GetSequenceNumber().GetValue() << " " << tag.GetUid() << " -1"
                //     << endl;

                // Drop(item);
                DropBeforeEnqueue(item, "Fifo overflow");

                drop += 1;
                std::ofstream thr1("MyResult/SpPifodrop.dat", std::ios::out | std::ios::app);
                thr1 << Simulator::Now().GetSeconds() << " " << drop << endl;
                return false;
            }
        }
        else
        {
            // push down
            if (i == 0)
            {
                if (this->GetQueueSize(i) < DEFAULT_VOLUME)
                {
                    // enque
                    GetInternalQueue(i)->Enqueue(Ptr<QueueDiscItem>(item));
                    // record into the map which records all pkts who are currently in the system
                    addSchePkt(uid, rank);
                    // updat the flow's last finish time
                    this->updateFlowPtr(rank, flowlabel, currFlow);
                    fifoenque += 1;
                    enpkt += 1;

                    std::ofstream thr("MyResult/SpPifoQBounds.dat", std::ios::out | std::ios::app);
                    thr << rank << ": ";
                    for (int k = 0; k < DEFAULT_PQ; k++)
                    {
                        thr << bounds[k] << " ";
                    }
                    thr << " =down> ";

                    // update all queue bounds
                    int cost = bounds[0] - rank;
                    bounds[0] = rank;
                    for (int j = 1; j < DEFAULT_PQ; j++)
                    {
                        bounds[j] -= cost;
                    }

                    size += 1;
                    
                    for (int k = 0; k < DEFAULT_PQ; k++)
                    {
                        thr << bounds[k] << " ";
                    }
                    thr << endl;
                    this->Record("EnqueuedPktsList.txt", item);
                    std::ofstream thr2("MyResult/size.dat", std::ios::out | std::ios::app);
                    thr2 << Simulator::Now().GetSeconds() << " " << size << endl;
                    return true;
                }
                // fifo overflow
                else
                {
                    DropBeforeEnqueue(item, "Reason for droppin item");
                    drop += 1;
                    std::ofstream thr1("MyResult/SpPifodrop.dat", std::ios::out | std::ios::app);
                    thr1 << Simulator::Now().GetSeconds() << " " << drop << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

Ptr<QueueDiscItem>
SpPifo::DoDequeue()
{
    deque += 1;
    cout << "DQ " << GetNPackets() << endl;
    if (GetNPackets() <= 0){
        empty += 1;
        return 0;
    }
    Ptr<QueueDiscItem> item;
    // deque from the highest priority non-empty fifo
    for (int i = 0; i < DEFAULT_PQ; i++)
    {
        if (this->GetQueueSize(i) > 0)
        {
            item = StaticCast<QueueDiscItem>(GetInternalQueue(i)->Dequeue());

            fifodeque += 1;
            depkt += 1;
            this->Record("DequeuedPktsList.txt", item);
            size -= 1;

            // update vt to be the pkt's rank
            GearboxPktTag tag;
            GetPointer(item->GetPacket())->PeekPacketTag(tag);
            currentRound = tag.GetDepartureRound();
            // currentRound = 0; // Jiajin
            break;
        }
    }

    // record queueing delay with Seq#
    GearboxPktTag tag;
    GetPointer(item->GetPacket())->PeekPacketTag(tag);

    // update the map which records all pkts currently in the scheduler
    removeSchePkt(tag.GetUid());
    int inversion = cal_inversion_mag(tag.GetDepartureRound());
    if (inversion > 0)
    {
        inv_count += 1;
        inv_mag += inversion;
    }
    std::ofstream thr2("MyResult/inversion_record.dat", std::ios::out);
    thr2 << "count: " << inv_count << "  magnitude: " << inv_mag << endl;

    std::ofstream thr("MyResult/CountStat.dat", std::ios::out);
    thr << Simulator::Now().GetSeconds() << " enque:" << enque << " deque:" << deque
        << " fifoenque:" << fifoenque << " fifodeque:" << fifodeque << " drop:" << drop
        << " flowNo:" << flowNo << std::endl;

    std::ofstream thr3("MyResult/size.dat", std::ios::out | std::ios::app);
    thr3 << Simulator::Now().GetSeconds() << " " << size << endl;

    // remove packet tag
    GetPointer(item->GetPacket())->RemovePacketTag(tag);
    return item;
}

void
SpPifo::Record(string fname, Ptr<QueueDiscItem> item)
{
    GearboxPktTag tag;
    item->GetPacket()->PeekPacketTag(tag);
    int dp = tag.GetDepartureRound();

    string path = "MyResult/pktsList/";
    path.append(fname);

    FILE* fp;
    fp = fopen(path.data(), "a+"); // open and write
    /*fprintf(fp, "%d ", enque);
    fprintf(fp, "%d ", enpkt);
    fprintf(fp, "%d ", deque);
    fprintf(fp, "%d ", empty);
    fprintf(fp, "%d ", depkt);
    fprintf(fp, "(");
    fprintf(fp, "%f", Simulator::Now().GetSeconds());
    fprintf(fp, ",");*/
    // fprintf(fp, "%d", dp);
    /*fprintf(fp, ",");
    fprintf(fp, "%d", currentRound);
    fprintf(fp, ",");
    fprintf(fp, "%d", dp - currentRound);
    fprintf(fp, ")");*/
    // fprintf(fp, "\t");
    fprintf(fp, "%s", "(");
    fprintf(fp, "%d", dp);
    fprintf(fp, "%s", ",");
    fprintf(fp, "%d", int(tag.GetFlowNo()));
    fprintf(fp, "%s", ",");
    fprintf(fp, "%f", Simulator::Now().GetSeconds());
    fprintf(fp, "%s", ")");
    fprintf(fp, "\t");

    fclose(fp);
}

Ptr<QueueDiscItem>
SpPifo::DoRemove(void)
{
    return 0;
}

Ptr<const QueueDiscItem>
SpPifo::DoPeek()
{
    Ptr<const QueueDiscItem> item;

    for (uint32_t i = 0; i < GetNInternalQueues(); i++)
    {
        if ((item = GetInternalQueue(i)->Peek()))
        {
            NS_LOG_LOGIC("Peeked from band " << i << ": " << item);
            NS_LOG_LOGIC("Number packets band " << i << ": " << GetInternalQueue(i)->GetNPackets());
            cout << "Number packets band " << i << ": " << GetInternalQueue(i)->GetNPackets() << endl;
            return item;
        }
    }
}

int
SpPifo::GetQueueSize(int index)
{
    return GetInternalQueue(index)->GetNPackets();
}

SpPifo::~SpPifo()
{
    NS_LOG_FUNCTION(this);
}

TypeId
SpPifo::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::SpPifo")
                            .SetParent<QueueDisc>()
                            .SetGroupName("TrafficControl")
                            .AddConstructor<SpPifo>();

    return tid;
}

void
SpPifo::InitializeParams()
{
    NS_LOG_FUNCTION(this);
}

bool
SpPifo::CheckConfig(void)
{
    NS_LOG_FUNCTION(this);

    if (GetNQueueDiscClasses() > 0)
    {
        NS_LOG_ERROR("SpPifo cannot have classes");
        return false;
    }
    if (GetNPacketFilters() != 0)
    {
        NS_LOG_ERROR("SpPifo needs no packet filter");
        return false;
    }
    // if (GetNInternalQueues() > 0)
    // {
    //     NS_LOG_ERROR("SpPifo cannot have internal queues");
    //     return false;
    // }

    return true;
}

void
SpPifo::FifoPrint(int index)
{
    cout << "q" << index << " : b" << bounds[index];
    for (int i = 0; i < this->GetQueueSize(index); i++)
    {
        Ptr<QueueItem> item = GetInternalQueue(i)->Dequeue();
        Packet* packet = GetPointer(item->GetPacket());
        GearboxPktTag tag;
        packet->PeekPacketTag(tag);
        cout << " (" << i << ", " << tag.GetDepartureRound() << ", " << tag.GetUid() << ", "
             << tag.GetFlowNo() << ") ";
        // fifos[index]->Enqueue(item);
        // Ensure 'item' is of the correct type
        Ptr<QueueDiscItem> itemToEnqueue = DynamicCast<QueueDiscItem>(item);

        // Use the correctly typed item
        GetInternalQueue(i)->Enqueue(itemToEnqueue);
    }
    cout << endl;
}

int
SpPifo::addSchePkt(int uid, int departureRound)
{
    qpkts[uid] = departureRound;
    return qpkts.size();
}

int
SpPifo::removeSchePkt(int uid)
{
    if (0 == qpkts.erase(uid))
    {
        cout << "cannot erase from map" << endl;
    }
    return qpkts.size();
}

int
SpPifo::cal_inversion_mag(int dp)
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
