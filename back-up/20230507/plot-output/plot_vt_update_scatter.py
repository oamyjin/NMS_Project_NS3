import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult/vt_delta_update_scatter.png'
    file_path = 'MyResult/cr_update.txt'
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    # part of data
    num_lines = 10000

    flows_x = {}
    flows_y = {}
    cnt = 0
    for line in lines:
        cnt += 1
        fid = line.strip().split()[2]
        fid = int(fid.strip().split(":")[1])
        if fid > 100:
            continue
        if fid not in flows_x:
            flows_x[fid] = []
            flows_y[fid] = []
        flows_x[fid].append(cnt)
        vt = line.strip().split()[1]
        prev_vt = int(vt.strip().split("->")[0].split(":")[1])
        updated_vt = int(vt.strip().split("->")[1])
        flows_y[fid].append(updated_vt-prev_vt)

    plt.figure(figsize=[15,5])
    for fid, _ in zip(flows_x, flows_y):
        x = flows_x[fid]
        y = flows_y[fid]
        label = "flow"+ str(fid)
        plt.scatter(x, y, s=1, label=label)
    
    # naming the x axis
    plt.xlabel('# pkt dequeued')
    # naming the y axis
    plt.ylabel('delta current virtual round')
    
    # show a legend on the plot
    plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()