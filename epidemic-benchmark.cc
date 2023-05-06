#include "protocol/epidemic-helper.h"

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"
#include "stats/stats.h"
#include "ns3/gnuplot.h"

#include <iostream>

using namespace ns3;

statistics::Stats st;

void SinkRxTrace(std::string context, Ptr<const Packet> pkt, const Address &addr){
    st.incrementReceivedPackets();
}


int main(int argc, char* argv[]) {
    // General parameters
    uint32_t nWifis = 50;
    uint32_t maxQueueLength = 200;
    uint32_t queueStep = 1;
    double txpDistance = 50.0;
    double nodeSpeed = 10.0;
    bool appLogging = false;

    // Application parameters
    double TotalTime = 200.0;
    double dataStart = 10.0;
    double dataEnd = 14.0;
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

    cmd.Parse(argc, argv);

    std::cout << "Number of wifi nodes: " << nWifis << std::endl;
    std::cout << "Node speed: " << nodeSpeed << " m/s" << std::endl;
    std::cout << "Packet size: " << packetSize << " b" << std::endl;
    std::cout << "Transmission distance: " << txpDistance << " m" << std::endl;
    std::cout << "Hop count: " << hopCount << std::endl;
    std::cout << "Max Queue length: " << maxQueueLength << std::endl;
    std::cout << "Queue entry expire time: " << queueEntryExpireTime.GetSeconds() << " s"
              << std::endl;
    std::cout << "Beacon interval: " << beaconInterval.GetSeconds() << " s" << std::endl << std::endl;

    // Enabling UdpClient and UdpServer logging
    if (appLogging)
    {
        LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);
        LogComponentEnable("PacketSink", LOG_LEVEL_INFO);
        LogComponentEnableAll(LOG_PREFIX_TIME);
        LogComponentEnableAll(LOG_PREFIX_NODE);
        LogComponentEnableAll(LOG_PREFIX_FUNC);
    }

    // Gnuplot
    std::string fileNameWithNoExtension = "data-loss-buffer-size" + std::to_string(maxQueueLength);
    std::string graphicsFileName        = fileNameWithNoExtension + ".png";
    std::string plotFileName            = fileNameWithNoExtension + ".plt";
    std::string plotTitle               = "Relation between data loss and buffer size";
    std::string dataTitle               = "Packet Loss %";

    // Instantiate the plot and set its title.
    Gnuplot plot(graphicsFileName);
    plot.SetTitle(plotTitle);

    // Make the graphics file, which the plot file will create when it
    // is used with Gnuplot, be a PNG file.
    plot.SetTerminal("png");

    // Set the labels for each axis.
    plot.SetLegend("Buffer size (packets)", "Packet Loss %");

    // Set the range for the x axis.
    std::stringstream extra;
    extra << "set xrange [0:" << "+" << std::to_string(maxQueueLength) << "]";
    plot.AppendExtra(extra.str());

    // Set terminal resolution
    plot.SetTerminal("png size 1920,1080");

    // Instantiate the dataset, set its title, and make the points be
    // plotted along with connecting lines.
    Gnuplot2dDataset dataset;
    dataset.SetTitle(dataTitle);
    dataset.SetStyle(Gnuplot2dDataset::LINES_POINTS);

    for (uint64_t queueLength = 0; queueLength < maxQueueLength; queueLength += queueStep) {
        std::string tag = "queueLength: " + std::to_string(queueLength);
        st.setTag(tag);
        st.setReceivedPackets(0);
        st.setSendedPackets(0);

        NodeContainer nodeContainer;
        NetDeviceContainer devices;
        nodeContainer.Create(nWifis);

        /*
        *       Mobility model Setup
        *  The parameters for mobility model matches the epidemic routing paper.
        */
        MobilityHelper mobility;
        ObjectFactory pos;
        mobility.SetPositionAllocator("ns3::RandomRectanglePositionAllocator",
                                    "X",
                                    StringValue("ns3::UniformRandomVariable[Min=0.0|Max=300.0]"),
                                    "Y",
                                    StringValue("ns3::UniformRandomVariable[Min=0.0|Max=1500.0]"));

        mobility.SetMobilityModel("ns3::SteadyStateRandomWaypointMobilityModel",
                                "MinSpeed",
                                DoubleValue(0.01),
                                "MaxSpeed",
                                DoubleValue(nodeSpeed),
                                "MinX",
                                DoubleValue(0.0),
                                "MaxX",
                                DoubleValue(300.0),
                                "MinPause",
                                DoubleValue(10),
                                "MaxPause",
                                DoubleValue(20),
                                "MinY",
                                DoubleValue(0.0),
                                "MaxY",
                                DoubleValue(1500.0));
        mobility.Install(nodeContainer);

        /*
        *       Physical and link Layers Setup
        */

        WifiMacHelper wifiMac;
        wifiMac.SetType("ns3::AdhocWifiMac");
        YansWifiPhyHelper wifiPhy;
        YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();

        wifiChannel.AddPropagationLoss("ns3::RangePropagationLossModel",
                                    "MaxRange",
                                    DoubleValue(txpDistance));
        wifiPhy.SetChannel(wifiChannel.Create());
        WifiHelper wifi;
        wifi.SetStandard(WIFI_STANDARD_80211a);
        wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                    "DataMode",
                                    StringValue("OfdmRate6Mbps"),
                                    "RtsCtsThreshold",
                                    UintegerValue(0));
        devices = wifi.Install(wifiPhy, wifiMac, nodeContainer);

        /*
        *       Epidemic Routing Setup
        * */
        EpidemicHelper epidemic;
        epidemic.Set("HopCount", UintegerValue(hopCount));
        epidemic.Set("QueueLength", UintegerValue(queueLength));
        epidemic.Set("QueueEntryExpireTime", TimeValue(queueEntryExpireTime));
        epidemic.Set("BeaconInterval", TimeValue(beaconInterval));

        /*
        *       Internet Stack Setup
        * */
        Ipv4ListRoutingHelper list;
        InternetStackHelper internet;
        internet.SetRoutingHelper(epidemic);
        internet.Install(nodeContainer);
        Ipv4AddressHelper ipv4;
        ipv4.SetBase("10.1.1.0", "255.255.255.0");
        Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

        /*
        * Application Setup
        * */

        // Sink or server setup
        uint64_t num_source = 45;
        uint64_t num_sink = 45;


        for (uint32_t i = 0; i < num_sink; ++i) {
            PacketSinkHelper sink("ns3::UdpSocketFactory",
                                InetSocketAddress(Ipv4Address::GetAny(), 80));
            ApplicationContainer apps_sink = sink.Install(nodeContainer.Get(i));

            Ptr<PacketSink> pktSink = StaticCast<PacketSink> (apps_sink.Get(0));
            std::stringstream ss; ss << "Sink Application Callback";
            pktSink->TraceConnect("Rx", ss.str(), MakeCallback (&SinkRxTrace));
            apps_sink.Start(Seconds(0.0));
            apps_sink.Stop(Seconds(TotalTime));
        }

        // Client setup
        for (uint32_t source = 0; source < num_source; ++source) {
            for (uint32_t sink = 0; sink < num_sink; ++sink) {
                if (sink != source) {
                    OnOffHelper onoff1("ns3::UdpSocketFactory",
                                    Address(InetSocketAddress(interfaces.GetAddress(sink), 80)));
                    onoff1.SetConstantRate(DataRate("1024B/s"));
                    onoff1.SetAttribute("PacketSize", UintegerValue(packetSize));
                    ApplicationContainer app = onoff1.Install(nodeContainer.Get(source));
                    
                    app.Start(Seconds(dataStart));
                    app.Stop(Seconds(dataEnd));
                }
            }
        }

        st.setSendedPackets((dataEnd - dataStart - 1) * num_source * (num_sink - 1));

        Simulator::Stop(Seconds(TotalTime));
        Simulator::Run();

        std::cout << st << std::endl;
        dataset.Add(queueLength, st.getPacketLoss());

        Simulator::Destroy();
    }

    // Add the dataset to the plot.
    plot.AddDataset(dataset);

    // Open the plot file.
    std::ofstream plotFile(plotFileName.c_str());

    // Write the plot file.
    plot.GenerateOutput(plotFile);

    // Close the plot file.
    plotFile.close();

    return 0;
}
