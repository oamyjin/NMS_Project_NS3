# NMS_Project_NS3

This is the repository for NMS course project. We evaluate the performance (fairness) of the co-existence of different packets scheudler and congestion controls.

## Environment

NS-3.37 simulator installation guide can be found in https://www.nsnam.org/docs/release/3.37/tutorial/html/quick-start.html#downloading-ns-3

macOS version: 13.3.1

clang version in Xcode: 14.0.3

## Packet schedulers implementation

PIFO, SP-PIFO, PCQ are implmented as queue disciples in `ns-allinone-3.37/ns-3.37/src/traffic-control/model`.

## Topology with different congestion controls

We provide different topology files in the `ns-allinone-3.37/ns-3.37/scratch` and different packet schedulers can be selected in topo files.


## Run
### Inversion Impact experiments
`cd ns-allinone-3.37/ns-3.37/scratch/`

Configure different packets shedulers in topology files by modifying `qdiscTypeId` attribute.

Single-node start topology: `bash scratch/nms-inversionimpact.sh`

Fat-Tree topology: `bash scratch/nms-fattree.sh`


### Co-existence experiments
`cd ns-allinone-3.37/ns-3.37/scratch/`

Configure different packets shedulers in topology files by modifying `qdiscTypeId` attribute.

TCP NewReno: `bash scratch/nms-reno.sh`

TCP Cubic: `bash scratch/nms-cubic.sh`

BBR: `bash scratch/nms-bbr.sh`

DCTCP: `bash scratch/nms-dctcp.sh`


## Result
Results and logs will be generated in `ns-allinone-3.37/ns-3.37/MyResult`.


