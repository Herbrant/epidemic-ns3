#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "../protocol/epidemic-helper.h"

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"
#include "../stats/stats.h"
#include "ns3/gnuplot.h"

using namespace ns3;

class Benchmark {
public:
    uint32_t nWifis;
    double txpDistance;
    double nodeSpeed;
    bool appLogging;
    double TotalTime;
    double dataStart;
    double dataEnd;
    uint32_t packetSize;
    uint32_t hopCount;
    uint32_t queueLength;
    Time queueEntryExpireTime;
    Time beaconInterval;
    statistics::Stats st;

    Benchmark(
        uint32_t nWifis, double txpDistance, 
        double nodeSpeed, bool appLogging, uint32_t packetSize,
        uint32_t hopCount, uint32_t queueLength, Time queueEntryExpireTime, Time beaconInterval);
    
    void SinkRxTrace(std::string context, Ptr<const Packet> pkt, const Address &addr);
    friend std::ostream& operator<<(std::ostream& os, Benchmark &b);
};

#endif