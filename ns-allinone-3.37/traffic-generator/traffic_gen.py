import sys
import random
import math
import heapq
from optparse import OptionParser
from custom_rand import CustomRand

class Flow:
    def __init__(self, src, dst, size, t):
        self.src, self.dst, self.size, self.t = src, dst, size, t
    def __str__(self):
        return "%d %d 3 100 %d %.9f"%(self.src, self.dst, self.size, self.t)

def translate_bandwidth(b):
    if b == None:
        return None
    if type(b)!=str:
        return None
    if b[-1] == 'G':
        return float(b[:-1])*1e9
    if b[-1] == 'M':
        return float(b[:-1])*1e6
    if b[-1] == 'K':
        return float(b[:-1])*1e3
    return float(b)

def poisson(lam):
    return -math.log(1-random.random())*lam

if __name__ == "__main__":
    port = 80
    parser = OptionParser()
    parser.add_option("-c", "--cdf", dest = "cdf_file", help = "the file of the traffic size cdf", default = "uniform_distribution.txt")
    parser.add_option("-n", "--nhost", dest = "nhost", help = "number of hosts")
    parser.add_option("-l", "--load", dest = "load", help = "the percentage of the traffic load to the network capacity, by default 0.3", default = "0.3")
    parser.add_option("-b", "--bandwidth", dest = "bandwidth", help = "the bandwidth of host link (G/M/K), by default 10G", default = "10G")
    parser.add_option("-t", "--time", dest = "time", help = "the total run time (s), by default 10", default = "10")
    parser.add_option("-o", "--output", dest = "output", help = "the output file", default = "traffic.txt")
    options,args = parser.parse_args()
    base_t = 0#2000000000
    total_size = 0
    if not options.nhost:
        print("please use -n to enter number of hosts")
        sys.exit(0)
    nhost = int(options.nhost)
    load = float(options.load)
    bandwidth = translate_bandwidth(options.bandwidth)
    time = float(options.time)*1e9 # translates to ns
    output = options.output
    if bandwidth == None:
        print("bandwidth format incorrect")
        sys.exit(0)

    fileName = options.cdf_file
    file = open(fileName, "r")
    lines = file.readlines()
    # read the cdf, save in cdf as [[x_i, cdf_i] ...]
    cdf = []
    for line in lines:
        x, y = map(float, line.strip().split(' '))
        cdf.append([x,y])

    # create a custom random generator, which takes a cdf, and generate number according to the cdf
    customRand = CustomRand()
    if not customRand.setCdf(cdf):
        print("Error: Not valid cdf")
        sys.exit(0)

    ofile = open(output, "w")

    # generate flows
    avg = customRand.getAvg()
    src_port = {} # key:node, value:port
    dst_port = {} # key:node, value:port

    #avg_inter_arrival = 1 / (bandwidth * load / 8. / avg) * 1000000000
    avg_inter_arrival = 1 / (bandwidth * load / 8. / avg / nhost) * 1000000000
    n_flow_estimate = int(time / avg_inter_arrival * nhost)
    n_flow = 0
    ofile.write("%3d \n" % 000)
    host_list = [(base_t + int(poisson(avg_inter_arrival)), i + 1) for i in range(nhost - 1)]
    heapq.heapify(host_list)
    src_record = []
    while len(host_list) > 0:
        t,src = host_list[0]
        inter_t = int(poisson(avg_inter_arrival))
        new_tuple = (src, t + inter_t)
        dst = nhost + 1
        #dst = random.randint(1, nhost)
        #while (dst == src):
        #    dst = random.randint(1, nhost)
        if (t + inter_t > time + base_t):
            heapq.heappop(host_list)
        else:
            size = int(customRand.rand())
            if size <= 0:
                size = 1
            n_flow += 1
            #if (src not in src_record):
            src_record.append(src)
            size = math.ceil(size /1500)
            if src not in src_port.keys():
                src_port[src] = 49153
            else:
                src_port[src] += 1
            if dst not in dst_port.keys():
                dst_port[dst] = 8888
            else:
                dst_port[dst] += 1
            # generate diff pkt sizes according to flow size
            #pkt_sizes = gen_pkts(size)
            ofile.write("%d %d %d %d %d %.9f\n"%(src, src_port[src], dst, dst_port[dst], size, t * 1e-9))
            total_size = total_size + size
            heapq.heapreplace(host_list, (t + inter_t, src))
            #if len(src_record) == 15000:
            #	break


    ofile.seek(0)
    ofile.write("%d" % n_flow)
    print("# flow:", n_flow)
    print("# pkts:", total_size)
    print("# pkts/flow:", total_size / n_flow)
    ofile.close()

'''
    f_list = []
    avg = customRand.getAvg()
    avg_inter_arrival = 1/(bandwidth*load/8./avg)*1000000000
    # print avg_inter_arrival
    for i in range(nhost):
        t = base_t
        while True:
            inter_t = int(poisson(avg_inter_arrival))
            t += inter_t
            dst = random.randint(0, nhost-1)
            while (dst == i):
                dst = random.randint(0, nhost-1)
            if (t > time + base_t):
                break
            size = int(customRand.rand())
            if size <= 0:
                size = 1
            f_list.append(Flow(i, dst, size, t * 1e-9))
    f_list.sort(key = lambda x: x.t)
    print len(f_list)
    for f in f_list:
        print f
'''

# python traffic_gen.py -c WebSearch_distribution.txt -n 128 -l 0.7 -b 10G -t 2
# python traffic_gen.py -c WebSearch_distribution.txt -n 64 -l 0.5 -b 100M -t 1
# python traffic_gen.py -c DataMining_distribution.txt -n 128 -l 0.7 -b 10G -t 2