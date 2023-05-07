

#include "ns3/queue-disc.h"

#include "ns3/Flow_pl.h"
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace ns3
{

class SpPifo : public QueueDisc
{
  private:
    static const int DEFAULT_PQ = 10;            // 25; // # of fifo queues
    static const int DEFAULT_VOLUME = 20;       // 20; // fifo size
    static const int RANK_RANGE = 1000;         // max rank difference value
    static const int DEFAULT_WEIGHT = 2;        // weight
    static const int DEFAULT_BURSTNESS = 10000; // burstness
    uint32_t inv_count = 0;
    uint64_t inv_mag = 0;

    typedef std::map<string, Flow_pl*> FlowMap;
    FlowMap flowMap;
    vector<string> Flowlist;
    vector<int> weights;
    std::map<int, int> qpkts; // those pkts who are in the scheduler <uid, rank>

    // Queue* fifos[DEFAULT_PQ]; // queues
    Queue<QueueDiscItem>* fifos[DEFAULT_PQ]; // queues

    int bounds[DEFAULT_PQ] = {0}; // initialize all queue bounds to be 0

    int size = 0;
    int drop = 0;
    int uid = 0;
    int maxUid = 0;
    int currentRound = 0;
    int flowNo = 0;
    int totalFlowNum = 0;

    int enque = 0;
    int deque = 0;
    int fifoenque = 0;
    int fifodeque = 0;
    int empty = 0;
    int depkt = 0;
    int enpkt = 0;

    Flow_pl* getFlowPtr(string fid);
    Flow_pl* insertNewFlowPtr(string fid, int fno, int weight, int burstness);
    int updateFlowPtr(int departureRound, string fid, Flow_pl* flowPtr);
    string convertKeyValue(string fid);
    int RankComputation(QueueDiscItem* item, Flow_pl* currFlow);
    string getFlowLabel(Ptr<QueueDiscItem> item);
    
    bool DoEnqueue(Ptr<QueueDiscItem> item) override;
    Ptr<QueueDiscItem> DoDequeue(void) override;
    Ptr<QueueDiscItem> FifoDequeue(int);
    Ptr<QueueDiscItem> PifoDequeue();
    Ptr<const QueueDiscItem> DoPeek() override;
    Ptr<QueueDiscItem> DoRemove(void);

    int GetQueueSize(int);
    void FifoPrint(int);
    void Record(string fname, Ptr<QueueDiscItem> item);

    bool CheckConfig(void) override;
    void InitializeParams(void) override;

    int addSchePkt(int uid, int departureRound); // return pkts count
    int removeSchePkt(int uid);                  // return pkts count
    int cal_inversion_mag(int departureRound); // return inversion magnitude, if 0 then there is no inversion

  public:
    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();

    /**
     * \brief Gearbox_pl_fid_flex constructor
     * Creates a queue with a default or customed number of packets
     */
    SpPifo();
    ~SpPifo() override;

};
} // namespace ns3
