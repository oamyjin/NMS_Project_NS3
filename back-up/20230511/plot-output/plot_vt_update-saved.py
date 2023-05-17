import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult/vt_delta_update.png'
    file_path = 'MyResult/cr_update.txt'
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    # part of data
    num_lines = 10000

    y = []
    for line in lines:
        vt = line.strip().split()[1]
        prev_vt = int(vt.strip().split("->")[0].split(":")[1])
        updated_vt = int(vt.strip().split("->")[1])
        y.append(updated_vt-prev_vt)

    x = [i for i in range(len(y))]

    plt.figure(figsize=[15,5])
    plt.plot(x, y)
    # naming the x axis
    plt.xlabel('# pkt dequeued')
    # naming the y axis
    plt.ylabel('delta current virtual round')
    
    # show a legend on the plot
    # plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()