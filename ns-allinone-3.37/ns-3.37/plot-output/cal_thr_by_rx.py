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

# init: thr_time = period
# idx_pre_thr, idx_thr = find_idx(time, thr_time - period, period)
# thr = 8 * (rx[idx_thr] - rx[idx_pre_thr]) / (period * 1024 * 1024 * 1024) # Gbps
def find_idx(time, pre_thr_time, thr_time):
    pre_thr_time_idx = 0
    thr_time_idx = 0
    for i in range(len(time)):
        if time[i] <= pre_thr_time and time[i+1] > pre_thr_time:
            pre_thr_time_idx = i
        if time[i] <= thr_time and time[i+1] > thr_time:
            thr_time_idx = i
    return pre_thr_time_idx, thr_time_idx


if __name__ == "__main__":
    period = 0.00012
    sche = ['MyResult/throuput.png', 'MyResult/rx_log/']

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
            print(flow_id)
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
                
            x = []
            y = []
            x.append(time[0])
            y.append(0)
            # ignore the first rx time
            thr_time = time[0] + period
            while thr_time <= time[-1]:
                idx_pre_thr, idx_thr = find_idx(time, thr_time - period, thr_time)
                thr = 8 * (rx[idx_thr] - rx[idx_pre_thr]) / (period * 1024 * 1024 * 1024) # Gbps
                thr_time += period
                x.append(thr_time)
                y.append(thr)
            print(len(x), len(y))
            # thr when the flow is active
            idx = len(y)
            while y[idx - 1] == 0.0:
                idx -= 1

            x = x[:idx]
            y = y[:idx]

            xs.append(x)
            ys.append(y)

    plt.figure(figsize=[15,5])
    # plotting line points 
    labels = flow_id #[i for i in range(1, 21)]
    print(labels)
    # labels = ["PIFO", "SPPIFO"]
    for x, y, lab in zip(xs, ys, labels):
       plt.plot(x, y, label = lab)
    #plt.plot(xs[5], ys[5], label = labels[5])
    # naming the x axis
    plt.xlabel('Time (s)')
    # naming the y axis
    plt.ylabel('Throughput (Gbps)')
    # giving a title to my graph
    #plt.title('SPPIFO Scheduler')
    
    # show a legend on the plot
    #plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()