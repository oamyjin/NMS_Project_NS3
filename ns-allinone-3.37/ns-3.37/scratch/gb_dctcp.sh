#!bin/bash
sudo rm -rf GBResult
mkdir GBResult
mkdir GBResult/pktsList
mkdir GBResult/pktsDelay
mkdir GBResult/pktsDelay_flows
mkdir GBResult/plotsData
mkdir GBResult/Performance
mkdir GBResult/Rx
./ns3 run my-test-dctcp
python scratch/my-flowmon-parse-results.py GBResult/FlowPerformance.xml