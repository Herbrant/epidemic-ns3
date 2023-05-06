#include "benchmark.h"

Benchmark::Benchmark(
        uint32_t nWifis, double txpDistance,double nodeSpeed, 
        bool appLogging, uint32_t packetSize, uint32_t hopCount, Time queueEntryExpireTime, 
        Time beaconInterval) {
    
    this->nWifis = nWifis;
    this->txpDistance = txpDistance;
    this->nodeSpeed = nodeSpeed;
    this->appLogging = appLogging;
    this->packetSize = packetSize;
    this->hopCount = hopCount;
    this->queueEntryExpireTime = queueEntryExpireTime;
    this->beaconInterval = beaconInterval;
    this->TotalTime = 200;
    this->dataStart = 10.0;
    this->dataEnd = 14.0;
}

void Benchmark::SinkRxTrace(std::string context, Ptr<const Packet> pkt, const Address &addr){
    this->st.incrementReceivedPackets();
}

std::ostream& operator<<(std::ostream& os, Benchmark &b) {
    os << "Number of wifi nodes: " << b.nWifis << std::endl;
    os << "Node speed: " << b.nodeSpeed << " m/s" << std::endl;
    os << "Packet size: " << b.packetSize << " b" << std::endl;
    os << "Transmission distance: " << b.txpDistance << " m" << std::endl;
    os << "Hop count: " << b.hopCount << std::endl;
    os << "Queue entry expire time: " << b.queueEntryExpireTime.GetSeconds() << " s"
              << std::endl;
    os << "Beacon interval: " << b.beaconInterval.GetSeconds() << " s" << std::endl;

    return os;
}