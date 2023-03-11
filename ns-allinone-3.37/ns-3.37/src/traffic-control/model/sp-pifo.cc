/**
* SP-PIFO:
*       q0 ======
*       q1 ======
*          ...
*   q(N-1) ======
**/

#include "ns3/Flow_pl.h"
#include "ns3/Replace_string.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "ns3/seq-ts-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv6-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ptr.h"
#include "sp-pifo.h"
#include "ns3/queue.h"
#include "ns3/queue-disc.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/ipv4-queue-disc-item.h"

using namespace std;

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE("SpPifo");
    NS_OBJECT_ENSURE_REGISTERED(SpPifo);

    SpPifo::SpPifo() {
        ObjectFactory factory;
        factory.SetTypeId("ns3::DropTailQueue");
        factory.Set("Mode", EnumValue(Queue::QUEUE_MODE_PACKETS));
        factory.Set("MaxPackets", UintegerValue(DEFAULT_VOLUME));

	// create fifos and assign the fifo length
	for (int i = 0; i < DEFAULT_PQ; i++) {
            fifos[i] = GetPointer(factory.Create<Queue>());
            uint32_t maxSize = DEFAULT_VOLUME;
            fifos[i]->SetMaxPackets(maxSize);
        }

	maxUid = 0;
        currentRound = 0;

	// initialize flow weights
	ifstream infile;
	infile.open("scratch/weights.txt");
	int no = 0;
	infile >> no;
        for (int i = 0; i < no; i++){
		int temp = 0;
		infile >> temp;
		weights.push_back(temp);
	}
	infile.close();

	cout << "SP-Pifo CREATED" << endl;
    }


    string SpPifo::getFlowLabel(Ptr<QueueDiscItem> item){
	Ptr<const Ipv4QueueDiscItem> ipItem = DynamicCast<const Ipv4QueueDiscItem>(item);
	const Ipv4Header ipHeader = ipItem->GetHeader();
	TcpHeader header;
    	GetPointer(item)->GetPacket()->PeekHeader(header);

	stringstream ss;
        ss << ipHeader.GetSource().Get() << header.GetSourcePort();
        string flowLabel = ss.str();
	return flowLabel;
    }


   string SpPifo::convertKeyValue(string fid) { 
        stringstream ss;
        ss << fid; 
        string key = ss.str();

        return key;
   }

   Flow_pl* SpPifo::insertNewFlowPtr(string fid, int fno, int weight, int burstness) {
	Flowlist.push_back(fid);
        string key = convertKeyValue(fid); 
        Flow_pl* newFlowPtr = new Flow_pl(fid, fno, weight, burstness);
	std::ofstream thr1 ("GBResult/weight.dat", std::ios::out | std::ios::app);
	thr1 << fno << " " << weight << endl;
	newFlowPtr->setStartTime(Simulator::Now().GetSeconds());
        this->flowMap.insert(pair<string, Flow_pl*>(key, newFlowPtr));
        return this->flowMap[key];
    }

 
   Flow_pl* SpPifo::getFlowPtr(string flowlabel) {
        string key = convertKeyValue(flowlabel);
	// insert new flows with assigned weight
        if (flowMap.find(key) == flowMap.end()) {
	    //int weight = rand() % 15 + 1;
	    //int weight = DEFAULT_WEIGHT;
	    /*if (flowNo % 3 == 0){
		weight = 8;
	    }*/
	    int weight = weights.at(flowNo);
	    flowNo++;
	    return this->insertNewFlowPtr(flowlabel, flowNo, weight, DEFAULT_BURSTNESS);
        }
        return this->flowMap[key];
    }


    int SpPifo::updateFlowPtr(int departureRound, string fid, Flow_pl* flowPtr) {
        string key = convertKeyValue(fid); 
	// update flow info
        flowPtr->setLastFinishRound(departureRound + flowPtr->getWeight());    // only update last packet finish time if the packet wasn't dropped
        this->flowMap.insert(pair<string, Flow_pl*>(key, flowPtr));

        return 0;
    }


    int SpPifo::RankComputation(QueueDiscItem* item, Flow_pl* currFlow){
	// calculate the rank(departureRound) value
	int curLastFinishRound = currFlow->getLastFinishRound();
	return max(currentRound, curLastFinishRound);
    }


    bool SpPifo::DoEnqueue(Ptr<QueueDiscItem> item) {
	enque += 1;
        NS_LOG_FUNCTION(this);
	
	Ptr<const Ipv4QueueDiscItem> ipItem = DynamicCast<const Ipv4QueueDiscItem>(item);
	const Ipv4Header ipHeader = ipItem->GetHeader();

	uid = uid + 1;
	maxUid = uid > maxUid ? uid : maxUid;

	// 1. calculate the incoming pkt's rank
	string flowlabel = getFlowLabel(item);
        Flow_pl* currFlow = getFlowPtr(flowlabel);
	//int flowNo = currFlow->getFlowNo();
	int rank = RankComputation(GetPointer(item), currFlow);
	//int rank = weights.at(flowNo - 1);

	// add tag values, including rank and uid
	GearboxPktTag tag;
	Packet* packet = GetPointer(item->GetPacket());
	packet->PeekPacketTag(tag);
	packet->AddPacketTag(GearboxPktTag(currFlow->getFlowNo(), uid, rank, Simulator::Now().GetSeconds()));

	// 2. enque to the target queue with bottom-up comparisions
	for (int i = DEFAULT_PQ - 1; i >= 0 ; i--){
		// push up
		if (rank >= bounds[i]){
			if (this->GetQueueSize(i) < DEFAULT_VOLUME){
				// enque
				fifos[i]->Enqueue(Ptr<QueueDiscItem>(item));	

				enpkt += 1;
				size += 1; // trace size in sp-pifo
				
				std::ofstream thr ("GBResult/SpPifoQBounds.dat", std::ios::out | std::ios::app);
				thr << rank << ": ";
				for (int k = 0; k < DEFAULT_PQ; k++){
					thr << bounds[k] << " ";
				}
				thr << " =up> ";
				
				this->Record("EnqueuedPktsList.txt", item);
				/*std::ofstream thr3 ("GBResult/pktsList/Enque_bound8.dat", std::ios::out | std::ios::app);
				thr3 << "(" << rank - bounds[7] << "," << i << "," << currFlow->getFlowNo() << ")" << " ";
				std::ofstream thr4 ("GBResult/pktsList/Size.dat", std::ios::out | std::ios::app);
				thr4 << "(" << i << "," << this->GetQueueSize(i) << "," << currFlow->getFlowNo() << ")" << " ";
				std::ofstream thr5 ("GBResult/pktsList/SizePlot7.dat", std::ios::out | std::ios::app);
				thr5 << Simulator::Now().GetSeconds() << " " << this->GetQueueSize(7) << endl;
				std::ofstream thr6 ("GBResult/pktsList/SizePlot6.dat", std::ios::out | std::ios::app);
				thr6 << Simulator::Now().GetSeconds() << " " << this->GetQueueSize(6) << endl;*/
				

				// update queue bound
				bounds[i] = rank;
				// record into the map which records all pkts who are currently in the system
				addSchePkt(uid, rank);
				// updat the flow's last finish time
				this->updateFlowPtr(rank, flowlabel, currFlow);
				fifoenque += 1;

				for (int k = 0; k < DEFAULT_PQ; k++){
					thr << bounds[k] << " ";
				}
				thr << endl;

				//if (currFlow->getFlowNo() == 9){
				if (Simulator::Now().GetSeconds() >= 0.0103700 && Simulator::Now().GetSeconds() <= 0.0103800){
					cout << "== En:" << currentRound << " dp:" << rank << " uid:" << uid << " " << Simulator::Now().GetSeconds() << endl;
					for (int i = 0; i < DEFAULT_PQ; i++){
						FifoPrint(i);
					}
				}
				std::ofstream thr2 ("GBResult/size.dat", std::ios::out | std::ios::app);
				thr2 << Simulator::Now().GetSeconds() << " " << size << endl;
				return true;
			}
			// fifo overflow
			else{
				// record queueing delay with Seq#
				TcpHeader header;
			    	GetPointer(item)->GetPacket()->PeekHeader(header);
				stringstream path;
				path << "GBResult/pktsDelay_flows/flow_" << currFlow->getFlowNo() << "_pktdelay.dat"; //plotResult
				std::ofstream thr4 (path.str(), std::ios::out | std::ios::app);
				thr4 << header.GetSequenceNumber().GetValue() << " " << tag.GetUid() << " -1" << endl;


				Drop(item);
				drop += 1;
				std::ofstream thr1 ("GBResult/SpPifodrop.dat", std::ios::out | std::ios::app);
				thr1 << Simulator::Now().GetSeconds() << " " << drop << endl;
				return false;
			}
		}
		else{
			// push down
			if (i == 0){
				if (this->GetQueueSize(i) < DEFAULT_VOLUME){
					// enque
					fifos[i]->Enqueue(Ptr<QueueDiscItem>(item));
					// record into the map which records all pkts who are currently in the system
					addSchePkt(uid, rank);
					// updat the flow's last finish time
					this->updateFlowPtr(rank, flowlabel, currFlow);
					fifoenque += 1;
					enpkt += 1;

					
					std::ofstream thr ("GBResult/SpPifoQBounds.dat", std::ios::out | std::ios::app);
					thr << rank << ": ";
					for (int k = 0; k < DEFAULT_PQ; k++){
						thr << bounds[k] << " ";
					}
					thr << " =down> ";

					// update all queue bounds
					int cost = bounds[0] - rank;
					bounds[0] = rank;
					for (int j = 1; j < DEFAULT_PQ; j++){
						bounds[j] -= cost;
					}

					size += 1;

					//std::ofstream thr ("GBResult/SpPifoQBounds.dat", std::ios::out | std::ios::app);
					//thr << rank << ": ";
					for (int k = 0; k < DEFAULT_PQ; k++){
						thr << bounds[k] << " ";
					}
					thr << endl;
					this->Record("EnqueuedPktsList.txt", item);
					/*std::ofstream thr3 ("GBResult/pktsList/Enque_bound8.dat", std::ios::out | std::ios::app);
					thr3 << Simulator::Now().GetSeconds() << rank - bounds[7] << endl;*/		

					//if (currFlow->getFlowNo() == 9){
					if (Simulator::Now().GetSeconds() >= 0.0103700 && Simulator::Now().GetSeconds() <= 0.0103800){
						cout << "En:" << currentRound << " dp:" << rank << " uid:" << uid << " " << Simulator::Now().GetSeconds() << endl;
						for (int i = 0; i < DEFAULT_PQ; i++){
							FifoPrint(i);
						}
					}
					std::ofstream thr2 ("GBResult/size.dat", std::ios::out | std::ios::app);
					thr2 << Simulator::Now().GetSeconds() << " " << size << endl;
					return true;
				}
				// fifo overflow
				else{
					// record queueing delay with Seq#
					TcpHeader header;
				    	GetPointer(item)->GetPacket()->PeekHeader(header);
					stringstream path;
					path << "GBResult/pktsDelay_flows/flow_" << currFlow->getFlowNo() + 1 << "_pktdelay.dat"; //plotResult
					std::ofstream thr4 (path.str(), std::ios::out | std::ios::app);
					thr4 << header.GetSequenceNumber().GetValue() << " " << tag.GetUid() << " -1" << endl;

					Drop(item);
					drop += 1;
					std::ofstream thr1 ("GBResult/SpPifodrop.dat", std::ios::out | std::ios::app);
					thr1 << Simulator::Now().GetSeconds() << " " << drop << endl;
					return false;
				}	
			}
		}
	}

	return true;
    }


    Ptr<QueueDiscItem> SpPifo::DoDequeue() {
	deque += 1;

        if (size <= 0) {
	    empty += 1;
            return 0;
        }
	Ptr<QueueDiscItem> item;
	// deque from the highest priority non-empty fifo
	for (int i = 0; i < DEFAULT_PQ; i++){
		if (this->GetQueueSize(i) > 0){	
			item = StaticCast<QueueDiscItem>(fifos[i]->Dequeue());
			fifodeque += 1;
			depkt += 1;
			this->Record("DequeuedPktsList.txt", item);
			size -= 1;

			// update vt to be the pkt's rank
			GearboxPktTag tag;
			GetPointer(item->GetPacket())->PeekPacketTag(tag);
			currentRound = tag.GetDepartureRound(); //20220729
			//currentRound = 0; //20220620 Jiajin
			break;
		}
	}

	// record queueing delay with Seq#
	GearboxPktTag tag;
	GetPointer(item->GetPacket())->PeekPacketTag(tag);
	TcpHeader header;
    	GetPointer(item)->GetPacket()->PeekHeader(header);
	stringstream path;
        path << "GBResult/pktsDelay_flows/flow_" << tag.GetFlowNo() << "_pktdelay.dat"; //plotResult
	std::ofstream thr4 (path.str(), std::ios::out | std::ios::app);
	thr4 << header.GetSequenceNumber().GetValue() << " " << tag.GetUid() << " " << Simulator::Now().GetSeconds() - tag.GetEnqueTimeStamp() << endl;

	// update the map which records all pkts currently in the scheduler
	removeSchePkt(tag.GetUid());
	int inversion = cal_inversion_mag(tag.GetDepartureRound());
	if (inversion > 0){
		inv_count += 1;
		inv_mag += inversion;
	}
	std::ofstream thr2 ("GBResult/inversion_record.dat", std::ios::out);
	thr2 << "count: " << inv_count << "  magnitude: " << inv_mag << endl;

	std::ofstream thr ("GBResult/CountStat.dat", std::ios::out);
	thr <<  Simulator::Now().GetSeconds() << " enque:" << enque << " deque:" << deque << " fifoenque:" << fifoenque << " fifodeque:" << fifodeque << " drop:" << drop << " flowNo:" << flowNo << std::endl;

	std::ofstream thr3 ("GBResult/size.dat", std::ios::out | std::ios::app);
	thr3 << Simulator::Now().GetSeconds() << " " << size << endl;

	//if (tag.GetFlowNo() == 9){
	if (Simulator::Now().GetSeconds() >= 0.0201165 && Simulator::Now().GetSeconds() <= 0.0201168){
		cout << "== DQ:" << currentRound << " dp:" << tag.GetDepartureRound() << " uid:" << tag.GetUid() << " " << Simulator::Now().GetSeconds() << endl;
		for (int i = 0; i < DEFAULT_PQ; i++){
			FifoPrint(i);
		}
	}
	
	return item;
    }


    void SpPifo::Record(string fname, Ptr<QueueDiscItem> item){
	GearboxPktTag tag;
        item->GetPacket()->PeekPacketTag(tag);
	int dp = tag.GetDepartureRound();
	
	string path = "GBResult/pktsList/";
	path.append(fname);
	
	FILE *fp;
	fp = fopen(path.data(), "a+"); //open and write
	/*fprintf(fp, "%d ", enque);
	fprintf(fp, "%d ", enpkt);
	fprintf(fp, "%d ", deque);
	fprintf(fp, "%d ", empty);
	fprintf(fp, "%d ", depkt);
	fprintf(fp, "(");
	fprintf(fp, "%f", Simulator::Now().GetSeconds());
	fprintf(fp, ",");*/
	//fprintf(fp, "%d", dp);
	/*fprintf(fp, ",");
	fprintf(fp, "%d", currentRound);
	fprintf(fp, ",");
	fprintf(fp, "%d", dp - currentRound);
	fprintf(fp, ")");*/
	//fprintf(fp, "\t");
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


    Ptr<QueueDiscItem> SpPifo::DoRemove(void) {
        return 0;
    }


    Ptr<const QueueDiscItem> SpPifo::DoPeek(void) const {
        return 0;
    }


    int SpPifo::GetQueueSize(int index) {
	return fifos[index]->GetNPackets();
    }

    SpPifo::~SpPifo()
    {
        NS_LOG_FUNCTION(this);
    }


    TypeId SpPifo::GetTypeId(void){
        static TypeId tid = TypeId("ns3::SpPifo")
            .SetParent<QueueDisc>()
            .SetGroupName("TrafficControl")
            .AddConstructor<SpPifo>()
            ;

        return tid;
    }


    void SpPifo::InitializeParams(void){
        NS_LOG_FUNCTION(this);
    }


    bool SpPifo::CheckConfig(void){
        NS_LOG_FUNCTION(this);

        if (GetNQueueDiscClasses() > 0){
            NS_LOG_ERROR("SpPifo cannot have classes");
            return false;
        }
        if (GetNPacketFilters() != 0){
            NS_LOG_ERROR("SpPifo needs no packet filter");
            return false;
        }
        if (GetNInternalQueues() > 0){
            NS_LOG_ERROR("SpPifo cannot have internal queues");
            return false;
        }

        return true;
    }


    void SpPifo::FifoPrint(int index){
	cout << "q" << index << " : b" << bounds[index];
	for (int i = 0; i < this->GetQueueSize(index); i++)
  	{	
		Ptr<QueueItem> item = fifos[index]->Dequeue();
    		Packet* packet = GetPointer(item->GetPacket());
	 	GearboxPktTag tag;
		packet->PeekPacketTag(tag);
		cout << " (" << i << ", " << tag.GetDepartureRound() << ", " << tag.GetUid() << ", " << tag.GetFlowNo() << ") ";
		fifos[index]->Enqueue(item);
  	}
	cout << endl;
    }

    int SpPifo::addSchePkt(int uid, int departureRound){
	qpkts[uid] = departureRound;
	return qpkts.size();
    }

    int SpPifo::removeSchePkt(int uid){
	if (0 == qpkts.erase(uid)){
		cout << "cannot erase from map" << endl;
	}
	return qpkts.size();
    }


    int SpPifo::cal_inversion_mag(int dp){
	int magnitude = 0;
	for (auto it = qpkts.begin(); it != qpkts.end(); ++it) {
		// compare the dequeued dp with all pkts' dp in the scheduler
		if (dp > it->second){
			magnitude += dp - it->second;
		}
	}
	return magnitude;
    }


}







	

