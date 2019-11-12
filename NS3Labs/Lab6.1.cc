/*
 * Lab6.1.cc
 *
 *  Created on: 14-Mar-2018
 *      Author: abhinav
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Lab6.1");


int main (int argc, char *argv[])
{
  double lat = 2.0;
  uint64_t rate = 4000000;

  CommandLine cmd;
  cmd.AddValue ("latency", "P2P link Latency in miliseconds", lat);
  cmd.AddValue ("rate", "P2P data rate in bps", rate);

  cmd.Parse (argc, argv);

   LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
   LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);
//Commented is Proxy Server
  NodeContainer n;
  n.Create (2);//3


  PointToPointHelper p2p;
  p2p.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (lat)));
  p2p.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (rate)));

  NetDeviceContainer dev = p2p.Install (n.Get(0), n.Get(1));
  //NetDeviceContainer dev2 = p2p.Install (n.Get(1), n.Get(2));


  InternetStackHelper internet;
  internet.Install (n);
  Ipv4AddressHelper ipv4;


  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (dev);

  /*ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i2 = ipv4.Assign (dev2);*/

  UdpServerHelper server1 (8000);
  UdpServerHelper server2 (8080);
  ApplicationContainer apps;
  apps = server2.Install (n.Get (1));
  apps = server1.Install (n.Get (1));


  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (10.0));

  UdpClientHelper client2 (i.GetAddress (1), 8080);
  UdpClientHelper client1 (i.GetAddress (1),8000);



  client1.SetAttribute ("MaxPackets", UintegerValue (10));
  client1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  client1.SetAttribute ("PacketSize", UintegerValue (1024));

  client2.SetAttribute ("MaxPackets", UintegerValue (10));
  client2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  client2.SetAttribute ("PacketSize", UintegerValue (1024));

  apps = client2.Install (n.Get (0));
  apps = client1.Install (n.Get (0));


  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();



  p2p.EnablePcapAll("lab61");


  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();


  Simulator::Stop (Seconds(11.0));

  AnimationInterface anim ("lab6.1.xml");
  //anim.SetConstantPosition(n.Get(0),10.0,20.0);
  //anim.SetConstantPosition(n.Get(1),30.0,20.0);
  //anim.SetConstantPosition(n.Get(2),45.0, 10.0);


  Simulator::Run ();

  monitor->CheckForLostPackets ();
  double throughput=0,tpackets=0,rpackets=0;
  ns3::Time delay;
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
	  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
	  std::cout<< "\nSource Address : "<<t.sourceAddress<<"\t"<<"Destination Address : "<<t.destinationAddress<<"\n";
	  std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";

	  std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
	  std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";

	  tpackets+=(double)i->second.txPackets;
	  rpackets+=(double)i->second.rxPackets;
	  std::cout<<"  Delay : "<<i->second.delaySum<<"\n";
	  delay += (i->second.delaySum)/(double)i->second.rxPackets;
	  std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
	  throughput+=(i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024);
     }



  monitor->SerializeToXmlFile("lab-6.1flow.xml", true, true);

  Simulator::Destroy ();


  return 0;
}


