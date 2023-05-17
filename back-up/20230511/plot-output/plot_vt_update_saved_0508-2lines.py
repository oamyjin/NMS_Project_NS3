import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    fig_name = 'MyResult-0508-reno-sppifo-8-128-sack/vt_delta_update_2lines.png'
    file_paths = ['MyResult-0508-reno-sppifo-8-128-sack/cr_update.txt', 'MyResult-0508-reno-sppifo-8-128-nosack/cr_update.txt']
    labels = ["SACK", "no SACK"]
    files = [open(file_path, 'r') for file_path in file_paths]
    files_lines = [file.readlines() for file in files]
    for file in files:
        file.close() 

    # part of data
    num_lines = 10000

    xs = []
    ys = []
    start_time = 0
    end_time = 15
    for lines in files_lines:
        x = []
        y = []
        for line in lines:
            time = float(line.strip().split()[0])
            if time < start_time or time > end_time:
                continue
            vt = line.strip().split()[1]
            prev_vt = int(vt.strip().split("->")[0].split(":")[1])
            updated_vt = int(vt.strip().split("->")[1])
            y.append(updated_vt) #-prev_vt
            x.append(time)
        xs.append(x)
        ys.append(y)

    #plt.figure(figsize=[15,5])
    for i in range(len(xs)):
        plt.plot(xs[i], ys[i], label=labels[i])
    # naming the x axis
    plt.xlabel('system real time')
    # naming the y axis
    plt.ylabel('current virtual round')
    
    # show a legend on the plot
    plt.legend()
    
    # save fig
    plt.savefig(fig_name) 

    # function to show the plot
    plt.show()