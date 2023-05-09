from __future__ import division
import sys
import os
import json
try:
    from xml.etree import cElementTree as ElementTree
except ImportError:
    from xml.etree import ElementTree

def parse_time_ns(tm):
    if tm.endswith('ns'):
        return float(tm[:-2])
    raise ValueError(tm)



## FiveTuple
class FiveTuple(object):
    ## class variables
    ## @var sourceAddress
    #  source address
    ## @var destinationAddress
    #  destination address
    ## @var protocol
    #  network protocol
    ## @var sourcePort
    #  source port
    ## @var destinationPort
    #  destination port
    ## @var __slots_
    #  class variable list
    __slots_ = ['sourceAddress', 'destinationAddress', 'protocol', 'sourcePort', 'destinationPort']
    def __init__(self, el):
        '''! The initializer.
        @param self The object pointer.
        @param el The element.
        '''
        self.sourceAddress = el.get('sourceAddress')
        self.destinationAddress = el.get('destinationAddress')
        self.sourcePort = int(el.get('sourcePort'))
        self.destinationPort = int(el.get('destinationPort'))
        self.protocol = int(el.get('protocol'))

## Histogram
class Histogram(object):
    ## class variables
    ## @var bins
    #  histogram bins
    ## @var nbins
    #  number of bins
    ## @var number_of_flows
    #  number of flows
    ## @var __slots_
    #  class variable list
    __slots_ = 'bins', 'nbins', 'number_of_flows'
    def __init__(self, el=None):
        '''! The initializer.
        @param self The object pointer.
        @param el The element.
        '''
        self.bins = []
        if el is not None:
            #self.nbins = int(el.get('nBins'))
            for bin in el.findall('bin'):
                self.bins.append( (float(bin.get("start")), float(bin.get("width")), int(bin.get("count"))) )

## Flow
class Flow(object):
    ## class variables
    ## @var flowId
    #  delay ID
    ## @var delayMean
    #  mean delay
    ## @var packetLossRatio
    #  packet loss ratio
    ## @var rxBitrate
    #  receive bit rate
    ## @var txBitrate
    #  transmit bit rate
    ## @var flowCompTime
    #  flow completion time
    ## @var fiveTuple
    #  five tuple
    ## @var packetSizeMean
    #  packet size mean
    ## @var probe_stats_unsorted
    #  unsirted probe stats
    ## @var hopCount
    #  hop count
    ## @var flowInterruptionsHistogram
    #  flow histogram
    ## @var rx_duration
    #  receive duration
    ## @var __slots_
    #  class variable list
    __slots_ = ['flowId', 'delayMean', 'packetLossRatio', 'rxBitrate', 'txBitrate', 'flowCompTime',
                'fiveTuple', 'packetSizeMean', 'probe_stats_unsorted',
                'hopCount', 'flowInterruptionsHistogram', 'rx_duration']
    def __init__(self, flow_el):
        '''! The initializer.
        @param self The object pointer.
        @param flow_el The element.
        '''
        self.flowId = int(flow_el.get('flowId'))
        rxPackets = float(flow_el.get('rxPackets'))
        txPackets = float(flow_el.get('txPackets'))

        tx_duration = (parse_time_ns (flow_el.get('timeLastTxPacket')) - parse_time_ns(flow_el.get('timeFirstTxPacket')))*1e-9
        rx_duration = (parse_time_ns (flow_el.get('timeLastRxPacket')) - parse_time_ns(flow_el.get('timeFirstRxPacket')))*1e-9
        self.flowCompTime = (parse_time_ns (flow_el.get('timeLastRxPacket')) - parse_time_ns(flow_el.get('timeFirstTxPacket')))*1e-9
        self.rx_duration = rx_duration
        self.probe_stats_unsorted = []
        if rxPackets:
            self.hopCount = float(flow_el.get('timesForwarded')) / rxPackets + 1
        else:
            self.hopCount = -1000
        if rxPackets:
            self.delayMean = float(flow_el.get('delaySum')[:-2]) / rxPackets * 1e-9
            self.packetSizeMean = float(flow_el.get('rxBytes')) / rxPackets
        else:
            self.delayMean = None
            self.packetSizeMean = None
        if rx_duration > 0:
            self.rxBitrate = float(flow_el.get('rxBytes'))*8 / rx_duration
        else:
            self.rxBitrate = None
        if tx_duration > 0:
            self.txBitrate = float(flow_el.get('txBytes'))*8 / tx_duration
        else:
            self.txBitrate = None
        lost = float(flow_el.get('lostPackets'))
        #print "rxBytes: %s; txPackets: %s; rxPackets: %s; lostPackets: %s" % (flow_el.get('rxBytes'), txPackets, rxPackets, lost)
        if rxPackets == 0:
            self.packetLossRatio = None
        else:
            self.packetLossRatio = (lost / (rxPackets + lost))

        interrupt_hist_elem = flow_el.find("flowInterruptionsHistogram")
        if interrupt_hist_elem is None:
            self.flowInterruptionsHistogram = None
        else:
            self.flowInterruptionsHistogram = Histogram(interrupt_hist_elem)

## ProbeFlowStats
class ProbeFlowStats(object):
    ## class variables
    ## @var probeId
    #  probe ID
    ## @var packets
    #  network packets
    ## @var bytes
    #  bytes
    ## @var delayFromFirstProbe
    #  delay from first probe
    ## @var __slots_
    #  class variable list
    __slots_ = ['probeId', 'packets', 'bytes', 'delayFromFirstProbe']

## Simulation
class Simulation(object):
    ## class variables
    ## @var flows
    #  list of flows
    def __init__(self, simulation_el):
        '''! The initializer.
        @param self The object pointer.
        @param simulation_el The element.
        '''
        self.flows = []
        FlowClassifier_el, = simulation_el.findall("Ipv4FlowClassifier")
        flow_map = {}
        for flow_el in simulation_el.findall("FlowStats/Flow"):
            flow = Flow(flow_el)
            flow_map[flow.flowId] = flow
            self.flows.append(flow)
        for flow_cls in FlowClassifier_el.findall("Flow"):
            flowId = int(flow_cls.get('flowId'))
            flow_map[flowId].fiveTuple = FiveTuple(flow_cls)

        for probe_elem in simulation_el.findall("FlowProbes/FlowProbe"):
            probeId = int(probe_elem.get('index'))
            for stats in probe_elem.findall("FlowStats"):
                flowId = int(stats.get('flowId'))
                s = ProbeFlowStats()
                s.packets = int(stats.get('packets'))
                s.bytes = float(stats.get('bytes'))
                s.probeId = probeId
                if s.packets > 0:
                    s.delayFromFirstProbe =  parse_time_ns(stats.get('delayFromFirstProbeSum')) / float(s.packets)
                else:
                    s.delayFromFirstProbe = 0
                flow_map[flowId].probe_stats_unsorted.append(s)


def main(argv):
    file_obj = open(argv[1])
    print("Reading XML file ", end=" ")

    sys.stdout.flush()
    level = 0
    sim_list = []
    for event, elem in ElementTree.iterparse(file_obj, events=("start", "end")):
        if event == "start":
            level += 1
        if event == "end":
            level -= 1
            if level == 0 and elem.tag == 'FlowMonitor':
                sim = Simulation(elem)
                sim_list.append(sim)
                elem.clear() # won't need this any more
                sys.stdout.write(".")
                sys.stdout.flush()
    print(" done.")

    file_out = open("MyResult/flow_result_data.json", "w")
    all_flow_data_result = []
    for sim in sim_list:
        for flow in sim.flows:
            flow_data_result = {"FlowID": "", 
                                "TX bitrate": None,
                                "RX bitrate": None,
                                "Mean Delay": None,
                                "Packet Loss Ratio": None,
                                "FCT": None}
            t = flow.fiveTuple
            proto = {6: 'TCP', 17: 'UDP'} [t.protocol]
            print("FlowID: %i (%s %s/%s --> %s/%i)" % \
                (flow.flowId, proto, t.sourceAddress, t.sourcePort, t.destinationAddress, t.destinationPort))
            flow_data_result["FlowID"] = str(flow.flowId) + " " + str(proto) + " " + str(t.sourceAddress) + "/" + str(t.sourcePort) + "-->" + str(t.destinationAddress) + "/" + str(t.destinationPort)
            #file_out.write("FlowID: %i (%s %s/%s --> %s/%i)" % \
            #    (flow.flowId, proto, t.sourceAddress, t.sourcePort, t.destinationAddress, t.destinationPort) + "\n")
            if flow.txBitrate is None:
                print("\tTX bitrate: None")
                #file_out.write("\tTX bitrate: None" + "\n")
            else:
                #print("\tTX bitrate: %.2f kbit/s" % (flow.txBitrate*1e-3,))
                print("\tTX bitrate: %.2f Mbit/s" % (flow.txBitrate*1e-6))
                flow_data_result["TX bitrate"] = str(flow.txBitrate*1e-6) + " Mbit/s"
                #file_out.write("\tTX bitrate: %.2f Mbit/s" % (flow.txBitrate*1e-6) + "\n")
            if flow.rxBitrate is None:
                print("\tRX bitrate: None")
                #file_out.write("\tRX bitrate: None" + "\n")
            else:
                #print("\tRX bitrate: %.2f kbit/s" % (flow.rxBitrate*1e-3,))
                print("\tRX bitrate: %.2f Mbit/s" % (flow.rxBitrate*1e-6))
                flow_data_result["RX bitrate"] = str(flow.rxBitrate*1e-6) + " Mbit/s"
                #file_out.write("\tRX bitrate: %.2f Mbit/s" % (flow.rxBitrate*1e-6) + "\n")
            if flow.delayMean is None:
                print("\tMean Delay: None")
                #file_out.write("\tMean Delay: None" + "\n")
            else:
                print("\tMean Delay: %.2f ms" % (flow.delayMean*1e3,))
                flow_data_result['Mean Delay'] = str(flow.delayMean*1e3) + " ms"
                #file_out.write("\tMean Delay: %.2f ms" % (flow.delayMean*1e3,) + "\n")
            if flow.packetLossRatio is None:
                print("\tPacket Loss Ratio: None")
                #file_out.write("\tPacket Loss Ratio: None" + "\n")
            else:
                print("\tPacket Loss Ratio: %.2f %%" % (flow.packetLossRatio*100))
                flow_data_result['Packet Loss Ratio'] = str(flow.packetLossRatio*100) + "%"
                #file_out.write("\tPacket Loss Ratio: %.2f %%" % (flow.packetLossRatio*100) + "\n")
            if flow.flowCompTime is None:
                print("\tFCT: None")
                #file_out.write("\tFCT: None" + "\n")
            else:
                print("\tFCT: %.2f ms" % (flow.flowCompTime*1e3))
                flow_data_result['FCT'] = str(flow.flowCompTime*1e3) + " ms"
                #file_out.write("\tFCT: %.2f ms" % (flow.flowCompTime*1e3) + "\n")
            all_flow_data_result.append(flow_data_result)
        json_data = {"results": all_flow_data_result}
        file_out.write(json.dumps(json_data))
    file_out.close()

if __name__ == '__main__':
    main(sys.argv)
