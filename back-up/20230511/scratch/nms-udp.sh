#!bin/bash
sudo rm -rf MyResult
mkdir MyResult
mkdir MyResult/rx_log
./ns3 run nms-udp-client-server
python scratch/my-flowmon-parse-results.py MyResult/FlowPerformance.xml
python plot-output/cal_thr_by_rx.py