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
    double getPacketLoss();

    void incrementReceivedPackets();
    void setSendedPackets(uint64_t sendedPackets);
};

std::ostream& operator<<(std::ostream& os, Stats& s);
}
#endif
