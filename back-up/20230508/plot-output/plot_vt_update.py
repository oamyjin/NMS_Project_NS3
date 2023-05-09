import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult-pifo-notfinished-withvtupdate/vt_delta_update_all.png'
    file_path = 'MyResult-pifo-notfinished-withvtupdate/cr_update.txt'
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    # part of data
    num_lines = 10000

    start_time = 0.0
    end_time = 1.3
    x = []
    y = []
    for line in lines:
        time = float(line.strip().split()[0])
        if time < start_time or time > end_time:
                continue
        vt = line.strip().split()[1]
        prev_vt = int(vt.strip().split("->")[0].split(":")[1])
        updated_vt = int(vt.strip().split("->")[1])
        y.append(updated_vt)  # - prev_vt
        x.append(time)

    #plt.figure(figsize=[15,5])
    plt.plot(x, y)
    # naming the x axis
    plt.xlabel('simulation real time')
    # naming the y axis
    plt.ylabel('current virtual round')
    
    # show a legend on the plot
    # plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()