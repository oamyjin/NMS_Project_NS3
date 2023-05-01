#!bin/bash
sudo rm -rf GBResult
mkdir GBResult
mkdir GBResult/pktsList
mkdir GBResult/pktsDelay
mkdir GBResult/pktsDelay_flows
mkdir GBResult/plotsData
mkdir GBResult/Performance
mkdir GBResult/Rx
./ns3 run my-test-udp
python scratch/my-flowmon-parse-results.py GBResult/FlowPerformance.xml