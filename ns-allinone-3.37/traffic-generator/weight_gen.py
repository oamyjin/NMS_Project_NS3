import random
from optparse import OptionParser

def gen_same_weights(n):
    for i in range(n):
        ofile.write("%d\n" % 2)

def gen_by_5_weights(n):
    count = [0, 0, 0, 0, 0]
    for i in range(n):
        r = random.randint(1, 100) % 5
        if r == 0:
            ofile.write("%d\n" % 1)
            count[0] += 1
        elif r == 1:
            ofile.write("%d\n" % 50)
            count[1] += 1
        elif r == 2:
            ofile.write("%d\n" % 100)
            count[2] += 1
        elif r == 3:
            ofile.write("%d\n" % 150)
            count[3] += 1
        else:
            ofile.write("%d\n" % 900)
            count[4] += 1
        ofile.write("%d\n" % 2)
    print(count)


def gen_range_weights(n, max_rank):
    for i in range(n):
        r = random.randint(1, max_rank)
        ofile.write("%d\n" % r)

def gen_decreasing(n, max_rank):
    for i in range(n):
        ofile.write("%d\n" % max_rank)
        max_rank -= 1

def gen_waving(n, max_rank):
    a = 1
    b = max_rank
    for i in range(n):
        if i % 2 == 0:
            ofile.write("%d\n" % a)
            a += 1
        else:
            ofile.write("%d\n" % b)
            b -= 1

def gen_weight_by_fsize(tr_f, w_f):
    min = 0
    max = 0
    size_id = 4
    i_f = open(tr_f, "r")
    o_f = open(w_f, "w")
    for l in i_f.readlines():
        v = l.split(" ")
        if len(v) > 2:
            print(v)
            if int(v[size_id]) - 1 < min:
                min = int(v[size_id]) - 1
            if int(v[size_id]) - 1 > max:
                max = int(v[size_id]) - 1
            o_f.write("%d\n" % int(v[size_id])) #(int(v[3]) - 1)
        else:
            o_f.write("%s" % v[0])
    i_f.close()
    o_f.close()
    print(min, max)

if __name__ == "__main__":
    port = 80
    parser = OptionParser()
    parser.add_option("-n", "--number", dest="n", help="number of weight values", default="10")
    parser.add_option("-r", "--range", dest="range", help="range of weight values", default="16")
    parser.add_option("-t", "--traffic_file", dest="tr_f", help="input traffic file", default="traffic50.txt")
    parser.add_option("-w", "--weight_file", dest="w_f", help="generated weight file", default="weights50.txt")
    options, args = parser.parse_args()

    if not options.n:
        print("please use -n to enter number of weights")
        sys.exit(0)

    n = int(options.n)
    r = int(options.range)
    tr_f = options.tr_f
    w_f = options.w_f

    ofile = open("weights.txt", "w")
    ofile.write("%d\n" % n)

    '''same weight 2'''
    #gen_same_weights(n)
    '''5 weights'''
    #gen_by_5_weights(n)
    '''1-range rank'''
    #gen_range_weights(n, r)
    '''decreasing rank'''
    #gen_decreasing(n, r)
    '''waving'''
    #gen_waving(n, r)
    '''weight = flow size'''
    gen_weight_by_fsize(tr_f, w_f)

    ofile.close()

# python weight_gen.py traffic_234.txt weights_234.txt
# python weight_gen.py -n 1000
# python weight_gen.py -n 127 -r 32
# python weight_gen.py -t WebSearchTraffic/load0.7/traffic_128_0.7_10g_2s_956_1284461.txt -w weights_956.txt
# python weight_gen.py -t WebSearchTraffic/load0.9/traffic_128_0.9_10g_2s_1201_1399992.txt -w weights_1201.txt