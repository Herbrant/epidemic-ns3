#ifndef QUEUE_LENGTH_BENCHMARK_H
#define QUEUE_LENGTH_BENCHMARK_H
#include "benchmark.h"

class QueueLengthBenchmark : public Benchmark {
public:
    uint32_t maxQueueLength;
    uint32_t queueStep;

    QueueLengthBenchmark(
        uint32_t nWifis, double txpDistance, double nodeSpeed, 
        bool appLogging, uint32_t packetSize, uint32_t hopCount, uint32_t queueLength, Time queueEntryExpireTime,
        Time beaconInterval, uint32_t maxQueueLength, uint32_t queueStep
    );
    
    void run();
    friend std::ostream& operator<<(std::ostream& os, QueueLengthBenchmark &b);
};

#endif