import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult/vt_delta_update_scatter.png'
    file_path = 'MyResult/cr_update.txt'
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    # part of data
    num_lines_a = 0
    num_lines_b = 1000

    flows_x = {}
    flows_y = {}
    cnt = num_lines_a - 1
    for line in lines[num_lines_a : num_lines_b]:
        cnt += 1
        fid = line.strip().split()[2]
        #fid = int(fid.strip().split(":")[1])
        if int(fid.strip().split(":")[1]) > 100:
            continue
        if fid not in flows_x:
            flows_x[fid] = []
            flows_y[fid] = []
        flows_x[fid].append(cnt)
        vt = line.strip().split()[1]
        prev_vt = int(vt.strip().split("->")[0].split(":")[1])
        updated_vt = int(vt.strip().split("->")[1])
        flows_y[fid].append(updated_vt-prev_vt)

    labels = {"flowId:2":"flow1-weight1", "flowId:3":"flow2-weigh10"}
    colors = {"flowId:2":"#1f77b4", "flowId:3":"orange"}
    plt.figure(figsize=[15,5])
    for fid in sorted(flows_x.keys()):
        x = flows_x[fid]
        y = flows_y[fid]
        plt.scatter(x, y, s=1, label=labels[fid], color=colors[fid])
    
    # naming the x axis
    plt.xlabel('# pkt dequeued')
    # naming the y axis
    plt.ylabel('delta current virtual round')
    
    # show a legend on the plot
    plt.legend(loc = "lower right")
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()