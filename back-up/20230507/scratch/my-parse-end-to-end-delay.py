
import os
import json
import sys

def dir_file_names(file_dir):
    file_names = []
    for root, dirs, files in os.walk(file_dir):
        for file in files:
            if os.path.splitext(file)[1] == '.txt':
                file_names.append(file)
    return file_names 

avg = lambda lst: sum(lst) / len(lst)

directory = 'MyResult/rx_log/'
flows = {} #key:fid, value:[delay]
for file in dir_file_names(directory):
    f = open(directory + file, 'r')
    fid = file.split('_')[1].split('.')[0]
    for line in f.readlines():
        if fid not in flows:
            flows[fid] = []
        flows[fid].append(float(line.split()[-1].split(":")[1][1:-2]))
            
ofile = open('MyResult/delay.json', 'w')
all_flow_delay_data = []
for fid, f_delays in flows.items():
    sorted_delays = sorted(f_delays)
    size = len(f_delays)
    flow_data_result = {"FlowID": fid,
                        "FlowSize": size,
                        "Average Delay": avg(f_delays) * 0.001,
                        "95% Delay": sorted_delays[int(size*0.95)] * 0.001,
                        "97% Delay": sorted_delays[int(size*0.97)] * 0.001,
                        "99% Delay": sorted_delays[int(size*0.99)] * 0.001}
    all_flow_delay_data.append(flow_data_result)
ofile.write(json.dumps(all_flow_delay_data))    
ofile.close()