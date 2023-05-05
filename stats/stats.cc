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
    return this->receivedPackets;
}

uint64_t Stats::getPacketLost() {
    return (this->sendedPackets - this->receivedPackets);
}

uint8_t Stats::getPacketLoss() {
    return (this->sendedPackets - this->receivedPackets)/this->sendedPackets * 100;
}

void Stats::incrementReceivedPackets() {
    this->receivedPackets++;
}

void Stats::incrementSendedPackets() {
    this->sendedPackets++;
}
}