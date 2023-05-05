import json

f = open('MyResult/delay.json')
data = json.load(f)
for i in data:
    print(i["FlowID"], i["FlowSize"], i["Average Delay"], i["95% Delay"], i["97% Delay"], i["99% Delay"])
f.close()

# python load-json_delay.py > 04122023-fattree-test/test6/delay/AFQ-delay.txt