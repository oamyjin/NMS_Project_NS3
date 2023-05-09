#!bin/bash
sudo rm -rf MyResult
mkdir MyResult
mkdir MyResult/rx_log
mkdir MyResult/cr_update_log 
#./ns3 run nms-dctcp-example-diffweights > MyResult/log.txt 
./ns3 run nms-dctcp-example > MyResult/log.txt
python scratch/my-flowmon-parse-results-to-json.py MyResult/FlowPerformance.xml
python plot-output/cal_thr_by_rx.py
# python plot-output/plot_vt_update.py