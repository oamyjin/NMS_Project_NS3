import matplotlib.pyplot as plt
import os
plt.rc('xtick', labelsize=14) 
plt.rc('ytick', labelsize=14) 
plt.rc('axes', labelsize=15) 

def dir_file_names(file_dir):
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
    period = 0.1
    sche = ['MyResult-0505-pifo1000-weight1-10/rx_pkt_id.png', 'MyResult-0505-pifo1000-weight1-10/rx_log/']
    sche = ['MyResult/rx_pkt_id.png', 'MyResult/rx_log/']
    sche = ['MyResult-sppifo/rx_pkt_id.png', 'MyResult-sppifo/rx_log/']
    sche = ['MyResult-0510-cubic-sppifo-20s/rx_pkt_id.png', 'MyResult-0510-cubic-sppifo-20s/rx_log/']

    fig_name = sche[0] 
    folders = [sche[1]]

    xs = [] # time
    ys = [] # thoughput_delta [pifo, sppifo]

    time_thoughput_pair = [] # per flow
    max_delta_throughput_time_pair = [] # per schemes
    flow_id = []

    for folder in folders:
        for file in dir_file_names(folder):
            flow_id.append(int(file[5:-4]))
            print(flow_id)
            lines = open(folder + file, "r").readlines()
            # read (timestamp, received bytes) from file
            pktId = []
            num_lines_a = 0 # 0 100000
            num_lines_b = len(lines) # len(lines) 105000
            cnt = 0
            for line in lines:
                cnt +=1 
                if cnt < num_lines_a or cnt > num_lines_b:
                    continue
                l = line.strip().split(' ')
                for idx in range(len(l)):
                    if "pktId" in l[idx] : #and int(file[5:-4]) == 2
                        cur_id = int(l[idx].strip().split(":")[1])
                        if cnt == num_lines_a + 1:
                            prev_id = cur_id 
                        pktId.append(cur_id) # - prev_id
                        prev_id = cur_id
                
            x = [num_lines_a+i for i in range(len(pktId))]
            y = pktId
            print(len(x), len(y))
            xs.append(x)
            ys.append(y)

    plt.figure(figsize=[15,5])
    # plotting line points 
    labels = flow_id #[i for i in range(1, 21)]
    print(labels)
    # labels = ["PIFO", "SPPIFO"]
    for x, y, lab in zip(xs, ys, labels):
       plt.scatter(x, y, s=1, label = lab)
    #plt.plot(xs[5], ys[5], label = labels[5])
    # naming the x axis
    plt.xlabel('# reveived pkt')
    # naming the y axis
    plt.ylabel('pkt id')
    # giving a title to my graph
    #plt.title('SPPIFO Scheduler')
    
    # show a legend on the plot
    plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()