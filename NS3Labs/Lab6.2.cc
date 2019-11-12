/*
 * Lab6.2.cc
 *
 *  Created on: 14-Mar-2018
 *      Author: abhinav
 */


#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Lab6.2");

int
main (int argc, char *argv[])
{

	bool verbose = true;
	  uint32_t nCsma = 3;
	  uint32_t nWifi = 3;
	  bool tracing = false;

	  CommandLine cmd;
	  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
	  cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
	  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
	  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);

	  cmd.Parse (argc,argv);

	  if (nWifi > 18)
	      {
	        std::cout << "nWifi should be 18 or less; otherwise grid layout exceeds the bounding box" << std::endl;
	        return 1;
	      }

	    if (verbose)
	      {
	        LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	        LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	      }

	    NodeContainer p2pNodes;
	    p2pNodes.Create (2);

	    PointToPointHelper pointToPoint;
	    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

	    NetDeviceContainer p2pDevices;
	    p2pDevices = pointToPoint.Install (p2pNodes);

	    NodeContainer csmaNodes;
	    csmaNodes.Add (p2pNodes.Get (1));
	    csmaNodes.Create (nCsma);

	    CsmaHelper csma;
	    csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
	    csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

	    NetDeviceContainer csmaDevices;
	    csmaDevices = csma.Install (csmaNodes);

	    NodeContainer wifiStaNodes;
	    wifiStaNodes.Create (nWifi);
	    NodeContainer wifiApNode = p2pNodes.Get (0);

	    YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
	    YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
	    phy.SetChannel (channel.Create ());

	    WifiHelper wifi;
	    wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

	    WifiMacHelper mac;
	    Ssid ssid = Ssid ("ns-3-ssid");
	    mac.SetType ("ns3::StaWifiMac",
	                 "Ssid", SsidValue (ssid),
	                 "ActiveProbing", BooleanValue (false));

	    NetDeviceContainer staDevices;
	    staDevices = wifi.Install (phy, mac, wifiStaNodes);

	    mac.SetType ("ns3::ApWifiMac",
	                 "Ssid", SsidValue (ssid));

	    NetDeviceContainer apDevices;
	    apDevices = wifi.Install (phy, mac, wifiApNode);

	    MobilityHelper mobility;

	    mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
	                                   "MinX", DoubleValue (0.0),
	                                   "MinY", DoubleValue (0.0),
	                                   "DeltaX", DoubleValue (5.0),
	                                   "DeltaY", DoubleValue (10.0),
	                                   "GridWidth", UintegerValue (3),
	                                   "LayoutType", StringValue ("RowFirst"));

	    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
	                               "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));
	    mobility.Install (wifiStaNodes);

	    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	    mobility.Install (wifiApNode);

	    InternetStackHelper stack;
	    stack.Install (csmaNodes);
	    stack.Install (wifiApNode);
	    stack.Install (wifiStaNodes);

	    Ipv4AddressHelper address;

	    address.SetBase ("10.1.1.0", "255.255.255.0");
	    Ipv4InterfaceContainer p2pInterfaces;
	    p2pInterfaces = address.Assign (p2pDevices);

	    address.SetBase ("10.1.2.0", "255.255.255.0");
	    Ipv4InterfaceContainer csmaInterfaces;
	    csmaInterfaces = address.Assign (csmaDevices);

	    address.SetBase ("10.1.3.0", "255.255.255.0");
	    address.Assign (staDevices);
	    address.Assign (apDevices);

	    UdpEchoServerHelper echoServer (9);

	    ApplicationContainer serverApps = echoServer.Install (p2pNodes.Get (0));
	    serverApps.Start (Seconds (1.0));
	    serverApps.Stop (Seconds (15.0));

	    UdpEchoClientHelper echoClient (p2pInterfaces.GetAddress (0), 9);
	    echoClient.SetAttribute ("MaxPackets", UintegerValue (5));
	    echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
	    echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

	    ApplicationContainer clientApps = echoClient.Install (csmaNodes.Get (1));
	   	ApplicationContainer clientApps1 = echoClient.Install (csmaNodes.Get (2));
	    ApplicationContainer clientApps2 = echoClient.Install (csmaNodes.Get (3));
	    ApplicationContainer clientApps3 = echoClient.Install (wifiStaNodes.Get (nWifi-1));
	    ApplicationContainer clientApps4 = echoClient.Install (wifiStaNodes.Get (nWifi-2));
	    ApplicationContainer clientApps5 = echoClient.Install (wifiStaNodes.Get (nWifi-3));

	    clientApps.Start (Seconds (2.0));
	    clientApps.Stop (Seconds (15.0));
	    clientApps1.Start (Seconds (3.0));
	    clientApps1.Stop (Seconds (15.0));
	    clientApps2.Start (Seconds (4.0));
	    clientApps2.Stop (Seconds (15.0));
	    clientApps3.Start (Seconds (4.0));
	    clientApps3.Stop (Seconds (15.0));
	    clientApps4.Start (Seconds (4.0));
	    clientApps4.Stop (Seconds (15.0));
	    clientApps5.Start (Seconds (4.0));
	    clientApps5.Stop (Seconds (15.0));

	    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


	    if (tracing == true)
	      {
	        pointToPoint.EnablePcapAll ("lab6.2");
	        phy.EnablePcapAll ("lab6.2");
	        csma.EnablePcapAll ("lab6.2");
	      }

	    FlowMonitorHelper flowHelper;
	    Ptr<FlowMonitor> flowMonitor;

	    flowMonitor = flowHelper.InstallAll();

	    Simulator::Stop (Seconds (15.0));

	    Simulator::Run ();

	    double throughput=0,tpackets=0,rpackets=0;
	    ns3::Time delay;

	    flowMonitor->CheckForLostPackets();
	    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowHelper.GetClassifier ());
	    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats ();
	    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
	    {
	    	Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);

	    	std::cout<< "\nSource Address : "<<t.sourceAddress<<"\t"<<"Destination Address : "<<t.destinationAddress<<"\n";
	    	std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";

	    	std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
	    	std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";

	    	tpackets+=(double)i->second.txPackets;
	    	rpackets+=(double)i->second.rxPackets;
	    	std::cout<<"  Delay : "<<(i->second.delaySum)/(double)i->second.rxPackets<<"\n";
	    	delay += (i->second.delaySum)/(double)i->second.rxPackets;
	    	std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
	    	throughput+=(i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024);
	    }


	    	                std::cout<<"\nTotal transmitted packets : "<<tpackets<<"\n";
	    	                std::cout<<"Total received packets : "<<rpackets<<"\n";
	    	                std::cout<<"Average Throughput : " <<throughput/6<<" Mbps\n";
	    	                std::cout<<"Average Delay : "<<delay/6<<"\n";

	    	               flowMonitor->SerializeToXmlFile("lab6.2Flow.xml",true, true);
	    	               Simulator::Destroy ();

	return 0;
}




