import matplotlib.pyplot as plt
import os

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
    #sche = ['MyResult-sppifo/rx_pkt_id.png', 'MyResult-sppifo/rx_log/']
    # sche = ['MyResult/rx_pkt_id.png', 'MyResult/rx_log/']
    #sche = ['MyResult-pifo-notfinished-withvtupdate/rx_pkt_id_line.png', 'MyResult-pifo-notfinished-withvtupdate/rx_log/']
    #fig_title = 'PIFO'
    #sche = ['MyResult-afq/rx_pkt_id_line_partial.png', 'MyResult-afq/rx_log/']
    #fig_title = 'PCQ'
    sche = ['MyResult-0508-reno-sppifo-8-128-nosack/rx_pkt_id_all.png', 'MyResult-0508-reno-sppifo-8-128-nosack/rx_log/']
    fig_title = 'with SACK'
    

    fig_name = sche[0] 
    folders = [sche[1]]

    xs = [] # time
    ys = [] # thoughput_delta [pifo, sppifo]

    time_thoughput_pair = [] # per flow
    max_delta_throughput_time_pair = [] # per schemes
    flow_id = []

    for folder in folders:
        for file in dir_file_names(folder):
            prev_id = -1
            flow_id.append(int(file[5:-4]))
            print(flow_id)
            lines = open(folder + file, "r").readlines()
            # read (timestamp, received bytes) from file
            pktId = []
            pktTime = []
            time_start = 12
            time_end = 13#0.07
            cnt = 0
            for line in lines:
                l = line.strip().split(' ')
                time = float(l[0])
                if time < time_start or time > time_end:
                    continue
                cnt += 1
                for idx in range(len(l)):
                    if "pktId" in l[idx] : #and int(file[5:-4]) == 2
                        cur_id = int(l[idx].strip().split(":")[1])
                        if prev_id == -1:
                            prev_id = cur_id
                            cnt = cur_id
                        pktId.append(cur_id) # - prev_id
                        pktTime.append(cnt) # time
                        prev_id = cur_id
                
            print(len(pktTime), len(pktId))
            xs.append(pktTime)
            ys.append(pktId)
    
    flow_idx = 0
    y_ideal = []
    ideal_pktId = ys[flow_idx][0]
    for i in range(len(ys[flow_idx])):
        y_ideal.append(ideal_pktId)
        ideal_pktId += 1
    print(len(y_ideal), len(ys[1]), len(xs[0]), len(xs[1]))

    plt.figure(figsize=[20,5])
    # plotting line points 
    labels = flow_id #[i for i in range(1, 21)]
    #print(labels)
    # labels = ["PIFO", "SPPIFO"]
    labels = ["high priority flow", "low priority flow"]
    colors = {"1":"#1f77b4", "2s":"orange"}
    plt.scatter(xs[flow_idx], ys[flow_idx], s=1, label = labels[flow_idx])
    #plt.scatter(xs[flow_idx], y_ideal, s=1, color="green")
    # for x, y, lab in zip(xs, ys, labels):
    #    plt.plot(x, y, label = lab)
    #plt.plot(xs[5], ys[5], label = labels[5])
    # naming the x axis
    plt.xlabel('# received pkt') #simulation time
    # naming the y axis
    plt.ylabel('received packet id')
    # giving a title to my graph
    # plt.title(fig_title)
    
    # show a legend on the plot
    plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()