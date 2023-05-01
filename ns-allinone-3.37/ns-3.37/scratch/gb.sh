#!bin/bash
sudo rm -rf GBResult
mkdir GBResult
mkdir GBResult/pktsList
mkdir GBResult/pktsDelay
mkdir GBResult/pktsDelay_flows
mkdir GBResult/plotsData
mkdir GBResult/Performance
mkdir GBResult/Rx
./ns3 run my-test > GBResult/log.txt
python scratch/my-flowmon-parse-results.py GBResult/FlowPerformance.xml
# python3 scratch/my-flowmon-parse-results-to-json.py GBResult/NameOfFile.xml
# python3 scratch/load-json_fct_fat.py > GBResult/SP-Pifo-fct.txt
# python3 scratch/my-parse-end-to-end-delay.py
# python3 scratch/load-json_delay.py > GBResult/SP-Pifo-delay.txt