#include "benchmark/queue-length-benchmark.h"
#include <iostream>

using namespace ns3;

int main(int argc, char* argv[]) {
    // General parameters
    uint32_t nWifis = 50;
    uint32_t maxQueueLength = 200;
    uint32_t queueStep = 1;
    double txpDistance = 50.0;
    double nodeSpeed = 10.0;
    bool appLogging = false;
    bool queueLengthBenchmark = true;
    bool hopCountBenchmark = true;
    uint32_t packetSize = 1024;

    // Epidemic routing parameters
    uint32_t hopCount = 50;
    Time queueEntryExpireTime = Seconds(1000);
    Time beaconInterval = Seconds(5);

    CommandLine cmd;
    cmd.Usage("Benchmark example shows epidemic routing scenario presented "
              "in the original paper.  There are 50 nodes in an area of 1500 m x 300 m."
              " 45 nodes are selected to send a message of size 1KB to the other "
              "44 nodes. The total messages are 45 * 44 = 1980 messages.  The buffer "
              "size change after every iteration of the simulation from 0 to the maxQueueLength.  The ranges for "
              "the transmission are from 10 m to 250 m while the default is set to "
              "50 m.\n");
    cmd.AddValue("nWifis", "Number of \"extra\" Wifi nodes/devices", nWifis);
    cmd.AddValue("appLogging", "Tell echo applications to log if true", appLogging);
    cmd.AddValue("nodeSpeed", "Node speed in RandomWayPoint model", nodeSpeed);
    cmd.AddValue("packetSize", "The packet size", packetSize);
    cmd.AddValue("txpDistance", "Specify node's transmit range", txpDistance);
    cmd.AddValue("hopCount", "Specify number of hopCount", hopCount);
    cmd.AddValue("maxQueueLength", "Specify number of maxQueueLength", maxQueueLength);
    cmd.AddValue("queueStep", "Specify number of queueStep", queueStep);
    cmd.AddValue("queueEntryExpireTime", "Specify queue Entry Expire Time", queueEntryExpireTime);
    cmd.AddValue("beaconInterval", "Specify beaconInterval", beaconInterval);
    cmd.AddValue("queueLengthBenchmark", "Tell to run the queueLengthBenchmark if true", queueLengthBenchmark);
    cmd.AddValue("hopCountBenchmark", "Tell to run the hopCountBenchmark if true", hopCountBenchmark);

    cmd.Parse(argc, argv);

    if (queueLengthBenchmark) {
        QueueLengthBenchmark qlb(
            nWifis, txpDistance, nodeSpeed, appLogging, packetSize, hopCount, 
            queueEntryExpireTime, beaconInterval, maxQueueLength, queueStep
        );

        std::cout << qlb << std::endl;
        qlb.run();
    }

    return 0;
}
