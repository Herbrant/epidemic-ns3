#ifndef STATS_H
#define STATS_H

namespace statistics {
class Stats {
private:
    uint64_t receivedPackets;
    uint64_t sendedPackets;
public:
    Stats();

    uint64_t getReceivedPackets();
    uint64_t getSendedPackets();
    uint64_t getPacketLost();
    uint8_t getPacketLoss();

    void incrementReceivedPackets();
    void incrementSendedPackets();
};
}
#endif
