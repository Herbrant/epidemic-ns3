#ifndef HOP_COUNT_BENCHMARK_H
#define HOP_COUNT_BENCHMARK_H
#include "benchmark.h"

class HopCountBenchmark : public Benchmark {
public:
    uint32_t maxHopCount;
    uint32_t hopCountStep;

    HopCountBenchmark(
        uint32_t nWifis, double txpDistance, double nodeSpeed, 
        bool appLogging, uint32_t packetSize, uint32_t hopCount, uint32_t queueLength, Time queueEntryExpireTime,
        Time beaconInterval, uint32_t maxHopCount, uint32_t hopCountStep
    );
    
    void run();
    friend std::ostream& operator<<(std::ostream& os, HopCountBenchmark &b);
};

#endif