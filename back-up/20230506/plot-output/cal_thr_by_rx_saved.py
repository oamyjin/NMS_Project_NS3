import matplotlib.pyplot as plt
import os
plt.rc('xtick', labelsize=14) 
plt.rc('ytick', labelsize=14) 
plt.rc('axes', labelsize=15) 

def dir_high_weight_file_names(file_dir):
    file_names = []
    for root, dirs, files in os.walk(file_dir):
        for file in files:
            if os.path.splitext(file)[1] == '.txt':
                file_names.append(file)
    return file_names

if __name__ == "__main__":
    period = 0.00012
    sche = ['ns-allinone-3.37/ns-3.37/MyResult/throuput.png', 'ns-allinone-3.37/ns-3.37/MyResult/rx_log/']

    fig_name = sche[0] 
    folders = [sche[1]]

    xs = [] # time
    ys = [] # thoughput_delta [pifo, sppifo]

    time_thoughput_pair = [] # per flow
    max_delta_throughput_time_pair = [] # per schemes
    flow_id = []

    for folder in folders:
        for file in dir_high_weight_file_names(folder):
            flow_id.append(int(file[5:-4]))
            lines = open(folder + file, "r").readlines()
            # read (timestamp, received bytes) from file
            time = []
            rx = []
            for line in lines:
                l = line.strip().split(' ')
                for idx in range(len(l)):
                    if "flowRxBytes" in l[idx]:
                        rx.append(float(l[idx].strip().split(":")[1]))
                time.append(float(l[0]))
                
            # print("flow_id:", flow_id)
            # print("   time:", len(time), time[3], "-", time[2], "=", time[3]- time[2])
            # print("     rx:", len(rx), rx[3], "-", rx[2], "=", rx[3]- rx[2])
            # print("    thr:", len(rx), (rx[3]- rx[2]) / (time[3]- time[2]))
            # calculate throuput
            x = []
            y = []
            # first thr: 0
            # x.append(0)
            # y.append(0)
            # first sampling thr is spcifically calculated here, because the timestamp and sampling period is not perfectly matched
            # thr = 8 * (rx[1] - rx[0]) / ((time[1] - time[0]) * 1024 * 1024 * 1024) # Gbps
            # print(time[0], rx[0], thr)
            # x.append(time[1])
            # y.append(thr)
            prev_time = time[1]
            prev_r = rx[1]
            prev_t_idx = 0
            #print(prev_time, thr)
            for t, r in zip (time[2:], rx[2:]):
                t_idx, _ = divmod(t - time[0], period)
                if t_idx != prev_t_idx:
                    # calculate thoughput
                    thr = 8 * (r - prev_r) / (period * 1024 * 1024 * 1024) # Gbps
                    x.append(t)
                    y.append(thr)
                    #print(t, prev_time, r, prev_r, t_idx, prev_t_idx, thr)
                    prev_t_idx = t_idx
                    prev_r = r
            # thr when the flow is active
            idx = len(y)
            while y[idx - 1] == 0:
                idx -= 1

            x = x[:idx]
            y = y[:idx]

            # TODO
            #xs.append(x)
            #ys.append(y)
            xs.append(x[:-10])
            ys.append(y[:-10])

    print(len(xs), len(ys))
    print(flow_id)
    plt.figure(figsize=[15,5])
    # plotting line points 
    labels = flow_id #[i for i in range(1, 21)]
    #labels = ["PIFO", "SPPIFO"]
    for x, y, lab in zip(xs, ys, labels):
        print(len(x), len(y), lab)
        plt.plot(x, y, label = lab)
    # plt.plot(xs[1], ys[1], label = labels[1])
    print(xs[1][:10])
    print(ys[1][:10])
    print(labels[1])
    # naming the x axis
    plt.xlabel('Time (s)')
    # naming the y axis
    plt.ylabel('Throughput (Gbps)')
    # giving a title to my graph
    #plt.title('SPPIFO Scheduler')
    
    # show a legend on the plot
    plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()