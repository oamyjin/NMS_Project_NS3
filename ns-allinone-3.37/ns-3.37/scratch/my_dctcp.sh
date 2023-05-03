#!bin/bash
sudo rm -rf MyResult
mkdir MyResult
mkdir MyResult/pktsList
mkdir MyResult/pktsDelay
mkdir MyResult/pktsDelay_flows
mkdir MyResult/plotsData
mkdir MyResult/Performance
mkdir MyResult/Rx
./ns3 run my-test-dctcp
python scratch/my-flowmon-parse-results.py MyResult/FlowPerformance.xml