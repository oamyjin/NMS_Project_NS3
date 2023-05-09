import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult/q_size7_update.png'
    file_path = 'MyResult/queuebound.txt'
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    # part of data
    num_lines_a = 192000
    num_lines_b = 200500
    q = 7

    flows_x = {}
    flows_y_q7size = {}
    flows_y_q6size = {}
    cnt = 0
    for line in lines:
        fid = line.strip().split()[5]
        fid = int(fid.strip().split(":")[1])
        # if (fid != 2 and fid != 3) or "EQ" in line:
        #     continue 
        if "DQ" in line and (fid == 2 or fid == 3):
            cnt += 1
            if cnt < num_lines_a or cnt > num_lines_b:
                continue
            if fid not in flows_x:
                flows_x[fid] = []
                flows_y_q7size[fid] = []
                flows_y_q6size[fid] = []
            flows_x[fid].append(cnt)
            q_7size = line.strip().split()[6]
            q_7size = int(q_7size.strip().split(":")[1].split("(")[0])
            flows_y_q7size[fid].append(q_7size)
            q_6size = line.strip().split()[7]
            q_6size = int(q_6size.strip().split(":")[1].split("(")[0])
            flows_y_q6size[fid].append(q_6size)

    labels = {2:"flow1-weight1", 3:"flow2-weigh10"}
    colors = {2:"#1f77b4", 3:"orange"}
    plt.figure(figsize=[15,5])
    for fid in sorted(flows_x.keys()):
        x = flows_x[fid]
        if q == 6:
            y = flows_y_q6size[fid]
        elif q == 7:
            y = flows_y_q7size[fid]
        plt.scatter(x, y, s=1, label=labels[fid], color=colors[fid])
    
    # naming the x axis
    plt.xlabel('# pkt dequeued')
    # naming the y axis
    plt.ylabel('q{} size'.format(q))
    
    # show a legend on the plot
    plt.legend(loc = "lower right")
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()