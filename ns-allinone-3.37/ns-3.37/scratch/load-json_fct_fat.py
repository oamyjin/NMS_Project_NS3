import json

f = open('MyResult/flow_result_data.json')
t_f = open('scratch/traffic.txt', 'r')

traffic_flow_size = {}
for line in t_f.readlines():
    if len(line.split()) > 1:
        values = line.strip().split()
        src_server_id = int(values[0])
        src_pod = int((src_server_id-1) / 64) + 1
        src_server_id_in_pod = src_server_id - (src_pod-1)*64
        dst_server_id = int(values[2])
        dst_pod = int((dst_server_id-1) / 64) + 1
        dst_server_id_in_pod = dst_server_id - (dst_pod-1)*64
        five_tuple = "10." + str(src_pod) + "." + str(src_server_id_in_pod) + ".1/" + values[1] + "-->10." + str(dst_pod) + "." + str(dst_server_id_in_pod)+ ".1/" + values[3]
        traffic_flow_size[five_tuple] = values[4]

data = json.load(f)

for i in data['results']:
    #print(i)
    if (i["FlowID"][-5] == '/'):
        #print(i["FlowID"], i["FCT"], i["RxPackets"])
        print(i["FlowID"], i["FCT"], traffic_flow_size[i["FlowID"].split()[-1]])

f.close()
t_f.close()

# python load-json_fct_fat.py > 04122023-fattree-test/test12/fct/sppifo-fct.txt