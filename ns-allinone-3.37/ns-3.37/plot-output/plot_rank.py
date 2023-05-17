import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult-sppifo/rank.png'
    file_path = 'MyResult-sppifo/queuebound.txt'
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    # part of data
    num_lines = 10000

    start_time = 0
    end_time = 15
    x = []
    y = []
    cnt = 0
    for line in lines:
        rank = line.strip().split()[2].split(":")[1]
        if "===" in rank:
            continue
        cnt += 1
        rank = int(rank)
        y.append(rank)  # - prev_vt
        x.append(cnt)

    #plt.figure(figsize=[15,5])
    plt.plot(x, y)
    # naming the x axis
    plt.xlabel('# enqueued packet')
    # naming the y axis
    plt.ylabel('packet rank')
    
    # show a legend on the plot
    # plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()