#ifndef STATS_H
#define STATS_H

namespace statistics {
class Stats {
private:
    std::string tag;
    uint64_t receivedPackets;
    uint64_t sendedPackets;
public:
    Stats();

    std::string getTag();
    uint64_t getReceivedPackets();
    uint64_t getSendedPackets();
    uint64_t getPacketLost();
    double getPacketLoss();

    void setTag(std::string tag);
    void incrementReceivedPackets();
    void setReceivedPackets(uint64_t receivedPackets);
    void setSendedPackets(uint64_t sendedPackets);
};

std::ostream& operator<<(std::ostream& os, Stats& s);
}
#endif
