#include "stats.h"

namespace statistics {
Stats::Stats() {
    this->receivedPackets = 0;
    this->sendedPackets = 0;
}

uint64_t Stats::getReceivedPackets() {
    return this->receivedPackets;
}

uint64_t Stats::getSendedPackets() {
    return this->sendedPackets;
}

uint64_t Stats::getPacketLost() {
    return (this->sendedPackets - this->receivedPackets);
}

double Stats::getPacketLoss() {
    return (double)(this->getPacketLost())/(double)(this->getSendedPackets())*100.0;
}

void Stats::incrementReceivedPackets() {
    this->receivedPackets++;
}

void Stats::setSendedPackets(uint64_t sendedPackets) {
    this->sendedPackets = sendedPackets;
}

std::ostream& operator<<(std::ostream& os, Stats& s) {
    os << "[BENCHMARK]" << std::endl;
    os << "Sended Packets: " << s.getSendedPackets() << std::endl;
    os << "Received Packets: " << s.getReceivedPackets() << std::endl;
    os << "Lost Packets: " << s.getPacketLost() << std::endl;
    os << "Packet Loss: " << s.getPacketLoss() << "%" << std::endl;
    return os;
}
}