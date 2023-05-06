#!/bin/bash
cd /ns3/ns-3.38/
./ns3 run "epidemic-benchmark $@"
mkdir -p /gnuplot/ && mv *.plt /gnuplot/
