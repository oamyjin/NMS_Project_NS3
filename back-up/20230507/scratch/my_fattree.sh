#!bin/bash
sudo rm -rf MyResult
mkdir MyResult
mkdir MyResult/rx_log
mkdir MyResult/cr_update_log
./ns3 run my-test-fattree > MyResult/log.txt
python scratch/my-flowmon-parse-results-to-json.py MyResult/FlowPerformance.xml
python scratch/load-json_fct_fat.py > MyResult/fct.txt
python scratch/my-parse-end-to-end-delay.py
python scratch/load-json_delay.py > MyResult/delay.txt

#python plot-output/cal_thr_by_rx.py
# python3 scratch/load-json_fct_fat.py > MyResult/SP-Pifo-fct.txt
# python3 scratch/my-parse-end-to-end-delay.py
# python3 scratch/load-json_delay.py > MyResult/SP-Pifo-delay.txt