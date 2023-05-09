import json
  
# Opening JSON file
f = open('MyResult/flow_result_data.json')
  
# returns JSON object as 
# a dictionary
data = json.load(f)
  
# Iterating through the json
# list
for i in data['results']:
    print(i)
    #print(i["FlowID"])
  
# Closing file
f.close()