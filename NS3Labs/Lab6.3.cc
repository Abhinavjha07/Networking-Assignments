#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/myapp.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/packet-sink-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Lab6.3");

uint32_t MacTxDropCount, PhyTxDropCount, PhyRxDropCount,MacRxDropCount;

void
MacTxDrop(Ptr<const Packet> p)
{
  NS_LOG_INFO("Packet Drop");
  MacTxDropCount++;
}

void
MacRxDrop(Ptr<const Packet> p)
{
  NS_LOG_INFO("Packet Drop");
  MacRxDropCount++;
}

void
PrintDrop()
{
  std::cout << Simulator::Now().GetSeconds() << "\t" << MacTxDropCount << "\t"<< PhyTxDropCount << "\t" << PhyRxDropCount <<"\t"<<MacRxDropCount<< "\n";
  Simulator::Schedule(Seconds(5.0), &PrintDrop);
}

void
PhyTxDrop(Ptr<const Packet> p)
{
  NS_LOG_INFO("Packet Drop");
  PhyTxDropCount++;
}
void
PhyRxDrop(Ptr<const Packet> p)
{
  NS_LOG_INFO("Packet Drop");
  PhyRxDropCount++;
}
int main (int argc, char *argv[])
{
  std::string phyMode ("DsssRate1Mbps");
  double distance = 500;
  uint32_t numNodes = 25;
  double interval =1.0;
  uint32_t packetSize = 1024;
  uint32_t numPackets = 1000000;
  std::string rtslimit = "2200";
  CommandLine cmd;

  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
  cmd.AddValue ("distance", "distance (m)", distance);
  cmd.AddValue ("packetSize", "size of application packet sent", packetSize);
  cmd.AddValue ("interval", "interval (seconds) between packets", interval);
  cmd.AddValue ("rtslimit", "RTS/CTS Threshold (bytes)", rtslimit);

  cmd.Parse (argc, argv);
  
  Time interPacketInterval = Seconds (interval);

  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue (rtslimit));
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", StringValue (phyMode));

  NodeContainer c;
  c.Create (numNodes);

  WifiHelper wifi;

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  wifiPhy.Set ("RxGain", DoubleValue (-10) );
  wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO); 

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());

  WifiMacHelper wifiMac;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (distance),
                                 "DeltaY", DoubleValue (distance),
                                 "GridWidth", UintegerValue (5),
                                 "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (c);

  OlsrHelper olsr;

  Ipv4ListRoutingHelper list;
  list.Add (olsr, 10);

  InternetStackHelper internet;
  internet.SetRoutingHelper (list);
  internet.Install (c);

  Ipv4AddressHelper ipv4;
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer ifcont = ipv4.Assign (devices);

  uint16_t sinkPort = 9;


   Address sinkAddress1 (InetSocketAddress (ifcont.GetAddress (24), sinkPort)); // interface of n24
   PacketSinkHelper packetSinkHelper1 ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
   ApplicationContainer sinkApps1 = packetSinkHelper1.Install (c.Get (24)); //n2 as sink
   sinkApps1.Start (Seconds (0.));
   sinkApps1.Stop (Seconds (100.));

   Ptr<Socket> ns3UdpSocket1 = Socket::CreateSocket (c.Get (0), UdpSocketFactory::GetTypeId ()); //source at n0

   Ptr<MyApp> app1 = CreateObject<MyApp> ();
   app1->Setup (ns3UdpSocket1, sinkAddress1, packetSize, numPackets, DataRate ("2Mbps"));
   c.Get (0)->AddApplication (app1);
   app1->SetStartTime (Seconds (31.));
   app1->SetStopTime (Seconds (100.));

   // N10 to N14

    Address sinkAddress2 (InetSocketAddress (ifcont.GetAddress (14), sinkPort)); // interface of n14
    PacketSinkHelper packetSinkHelper2 ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
    ApplicationContainer sinkApps2 = packetSinkHelper2.Install (c.Get (14)); //n14 as sink
    sinkApps2.Start (Seconds (0.));
    sinkApps2.Stop (Seconds (100.));

    Ptr<Socket> ns3UdpSocket2 = Socket::CreateSocket (c.Get (10), UdpSocketFactory::GetTypeId ()); //source at n10

    // Create UDP application at n10
    Ptr<MyApp> app2 = CreateObject<MyApp> ();
    app2->Setup (ns3UdpSocket2, sinkAddress2, packetSize, numPackets, DataRate ("2Mbps"));
    c.Get (10)->AddApplication (app2);
    app2->SetStartTime (Seconds (31.5));
    app2->SetStopTime (Seconds (100.));

    //N20 to N4

     Address sinkAddress3 (InetSocketAddress (ifcont.GetAddress (4), sinkPort)); // interface of n4
     PacketSinkHelper packetSinkHelper3 ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
     ApplicationContainer sinkApps3 = packetSinkHelper3.Install (c.Get (4)); //n2 as sink
     sinkApps3.Start (Seconds (0.));
     sinkApps3.Stop (Seconds (100.));

     Ptr<Socket> ns3UdpSocket3 = Socket::CreateSocket (c.Get (20), UdpSocketFactory::GetTypeId ()); //source at n20

     // Create UDP application at n20
     Ptr<MyApp> app3 = CreateObject<MyApp> ();
     app3->Setup (ns3UdpSocket3, sinkAddress3, packetSize, numPackets, DataRate ("2Mbps"));
     c.Get (20)->AddApplication (app3);
     app3->SetStartTime (Seconds (32.));
     app3->SetStopTime (Seconds (100.));


  // Install FlowMonitor on all nodes
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();


  // Trace Collisions
  Config::ConnectWithoutContext("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Mac/MacTxDrop", MakeCallback(&MacTxDrop));
  Config::ConnectWithoutContext("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/PhyTxDrop", MakeCallback(&PhyTxDrop));
  Config::ConnectWithoutContext("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/PhyRxDrop", MakeCallback(&PhyRxDrop));
  Config::ConnectWithoutContext("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Mac/MacRxDrop", MakeCallback(&MacRxDrop));
  

  Simulator::Schedule(Seconds(5.0), &PrintDrop);

  Simulator::Stop (Seconds (100.0));
  AnimationInterface anim ("lab6.3.xml");
  Simulator::Run ();

  PrintDrop();

  monitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator iter = stats.begin (); iter != stats.end (); ++iter)
    {
	  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (iter->first);

      /*if ((t.sourceAddress == Ipv4Address("10.1.1.1") && t.destinationAddress == Ipv4Address("10.1.1.25"))
    	|| (t.sourceAddress == Ipv4Address("10.1.1.11") && t.destinationAddress == Ipv4Address("10.1.1.15"))
    	|| (t.sourceAddress == Ipv4Address("10.1.1.21") && t.destinationAddress == Ipv4Address("10.1.1.5")))
        {*/
    	  NS_LOG_UNCOND("\nFlow ID: " << iter->first << " Source Addrress " << t.sourceAddress << " Destination Addrress " << t.destinationAddress);
    	  NS_LOG_UNCOND("Tx Packets = " << iter->second.txPackets);
    	  NS_LOG_UNCOND("Rx Packets = " << iter->second.rxPackets);
    	  //NS_LOG_UNCOND("Packets Lost= " << iter->second.txPackets-iter->second.rxPackets);
    	  NS_LOG_UNCOND("Times forwarded = " << iter->second.timesForwarded);
    	  NS_LOG_UNCOND("Packets lost = " << iter->second.lostPackets);
    	  NS_LOG_UNCOND("Throughput: " << iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024  << " Kbps");
    	  NS_LOG_UNCOND("Throughput percent: " << (iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024 )/10000 <<" %" );
       // }
    }
  monitor->SerializeToXmlFile("Lab6.3.flow.xml", true, true);

  Simulator::Destroy ();

  return 0;
}

