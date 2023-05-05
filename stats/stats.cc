#include "stats.h"

namespace statistics {
Stats::Stats() {
    this->tag = "";
    this->receivedPackets = 0;
    this->sendedPackets = 0;
}

std::string Stats::getTag() {
    return this->tag;
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

void Stats::setTag(std::string tag) {
    this->tag = tag;
}

void Stats::incrementReceivedPackets() {
    this->receivedPackets++;
}

void Stats::setSendedPackets(uint64_t sendedPackets) {
    this->sendedPackets = sendedPackets;
}

void Stats::setReceivedPackets(uint64_t receivedPackets) {
    this->receivedPackets = receivedPackets;
}

std::ostream& operator<<(std::ostream& os, Stats& s) {
    os << "[BENCHMARK - " << s.getTag()  << "]" << std::endl;
    os << "Sended Packets: " << s.getSendedPackets() << std::endl;
    os << "Received Packets: " << s.getReceivedPackets() << std::endl;
    os << "Lost Packets: " << s.getPacketLost() << std::endl;
    os << "Packet Loss: " << s.getPacketLoss() << "%" << std::endl;
    return os;
}
}