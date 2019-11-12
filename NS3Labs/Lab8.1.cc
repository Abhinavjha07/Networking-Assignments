

#include <iostream>
#include <fstream>
#include <string>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/ipv4-static-routing.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace std;
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("DynamicRoutingProtocol");

ofstream fp;
FlowMonitorHelper flowmon;
Ptr<FlowMonitor> monitor;

uint32_t txPacketsum = 1;
uint32_t rxPacketsum = 1;
uint32_t DropPacketsum = 0;
uint32_t LostPacketsum = 0;
double Delaysum = 0;

void calculateLoss () {
  double total=0;

  monitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  map<FlowId, FlowMonitor::FlowStats>::const_iterator i;
  double j=0,m=0;
  for ( i = stats.begin (); i != stats.end (); ++i)
  {
     Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
      if(t.destinationAddress == "10.1.3.2")
      {
    	  std::cout <<"\nSource Address : "<<t.sourceAddress<<"\tDestination Address : "<<t.destinationAddress<<std::endl;
        j += i->second.txPackets;
        m += i->second.lostPackets;
        std::cout<<"Transmitted packets : "<<i->second.txPackets<<"\tLost packets : "<< i->second.lostPackets<<std::endl;
      }
  }
  total = m/j ;
  fp << Simulator::Now ().GetSeconds () <<" "<< total << endl;
}

int main (int argc, char *argv[])
{
  string latency = "2ms";
  string rate = "1Mbps";
  string n3_n4rate = "500Kbps";
  bool enableFlowMonitor = true;

  fp.open ("Question8-loss.txt");
  if (!fp) {
    cout << "Cannot open the output file" << endl;
    exit (1);
  }

  Config::SetDefault ("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue (true));

  CommandLine cmd;
  cmd.AddValue ("latency", "P2P link Latency in miliseconds", latency);
  cmd.AddValue ("rate", "P2P data rate in bps", rate);
  cmd.AddValue ("n3_n4rate", "P2P data rate for n3-n4 link in bps", n3_n4rate);
  cmd.AddValue ("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);

  cmd.Parse (argc, argv);


  NS_LOG_INFO ("Create nodes.");
  NodeContainer nodes;
  nodes.Create(5);

  NodeContainer n0n3 = NodeContainer (nodes.Get (0), nodes.Get (3));
  NodeContainer n0n1 = NodeContainer (nodes.Get (0), nodes.Get (1));
  NodeContainer n1n2 = NodeContainer (nodes.Get (1), nodes.Get (2));
  NodeContainer n2n4 = NodeContainer (nodes.Get (2), nodes.Get (4));
  NodeContainer n3n4 = NodeContainer (nodes.Get (3), nodes.Get (4));

  /* Install Internet Stack */
  InternetStackHelper stack;
  stack.Install (nodes);

  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue (rate));
  p2p.SetChannelAttribute ("Delay", StringValue (latency));

  NetDeviceContainer d0d3 = p2p.Install (n0n3);

  NetDeviceContainer d0d1 = p2p.Install (n0n1);
  NetDeviceContainer d1d2 = p2p.Install (n1n2);
  NetDeviceContainer d2d4 = p2p.Install (n2n4);

  p2p.SetDeviceAttribute ("DataRate", StringValue (n3_n4rate));
  NetDeviceContainer d3d4 = p2p.Install (n3n4);

  /* Add IP addresses. */
  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i0i3 = ipv4.Assign (d0d3);

  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i0i1 = ipv4.Assign (d0d1);

  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i1i2 = ipv4.Assign (d1d2);

  ipv4.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i2i4 = ipv4.Assign (d2d4);

  ipv4.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer i3i4 = ipv4.Assign (d3d4);

  NS_LOG_INFO ("Enable static global routing.");

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  NS_LOG_INFO ("Create Applications.");



  ApplicationContainer cbrApps;
  uint16_t cbrPort = 8080;
  OnOffHelper onoff ("ns3::UdpSocketFactory",  InetSocketAddress (i1i2.GetAddress (1), cbrPort));
  onoff.SetAttribute ("OnTime",  StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  onoff.SetAttribute ("PacketSize", UintegerValue (200));

  // flow n0 to n2 at 1sec 900Kbps
  onoff.SetAttribute ("DataRate", StringValue ("900Kbps"));
  onoff.SetAttribute ("StartTime", TimeValue (Seconds (1.000000)));
  onoff.SetAttribute ("StopTime", TimeValue (Seconds (3.500000)));
  cbrApps.Add (onoff.Install (nodes.Get (0)));

  // flow n0 to n1 at 1.5sec 300Kbps
  onoff.SetAttribute ("DataRate", StringValue ("300Kbps"));
  onoff.SetAttribute ("StartTime", TimeValue (Seconds (1.500000)));
  onoff.SetAttribute ("StopTime", TimeValue (Seconds (3.000000)));
  onoff.SetAttribute ("Remote",  AddressValue (Address (InetSocketAddress (i0i1.GetAddress (1), cbrPort))) );
  cbrApps.Add (onoff.Install (nodes.Get (0)));

  uint16_t  echoPort = 9;


  UdpEchoClientHelper echoClientHelper (i0i1.GetAddress (1), echoPort);
  echoClientHelper.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClientHelper.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
  echoClientHelper.SetAttribute ("PacketSize", UintegerValue (10));
  ApplicationContainer apps;

  // again using different start times to workaround Bug 388 and Bug 912
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.001)));
  apps.Add (echoClientHelper.Install (nodes.Get (0)));


  echoClientHelper.SetAttribute ("RemoteAddress", AddressValue (i1i2.GetAddress (1)) );
  echoClientHelper.SetAttribute ("RemotePort", UintegerValue (echoPort));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.006)));
  apps.Add (echoClientHelper.Install (nodes.Get (0)));


  Ptr<Node> n1 = nodes.Get (1);
  Ptr<Ipv4> ipv41 = n1->GetObject<Ipv4> ();

  uint32_t ipv4ifIndex1 = 1;

  Simulator::Schedule (Seconds (2.0), &Ipv4::SetDown, ipv41, ipv4ifIndex1);
  Simulator::Schedule (Seconds (2.7), &Ipv4::SetUp, ipv41, ipv4ifIndex1);

  // Increase UDP Rate
  //  Simulator::Schedule (Seconds(30.0), &IncRate, app2, DataRate("500kbps"));

  /* Tracing */
  AsciiTraceHelper ascii;
  Ptr<OutputStreamWrapper> stream = ascii.CreateFileStream ("dynamic-global-routing.tr");
  p2p.EnableAsciiAll (stream);

  stack.EnableAsciiIpv4All (stream);
  p2p.EnablePcapAll("DynamicRoutingProtocol");

  // Flow Monitor
    if (enableFlowMonitor)
    {
      monitor = flowmon.InstallAll ();
      //monitor = flowmon.Install (nodes.Get (0));
      monitor->Start (Seconds (0.5));
    }

  for(double k=1;k<=7.0;k = k + 0.05)
  {
    Simulator::Schedule (Seconds(k), &calculateLoss);
  }
std::cout<<"\nStarting the simulator\n"<<std::endl;
  /* Now, do the actual simulation. */
  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop (Seconds(8.0));
  Simulator::Run ();
std::cout<<"\nSimulator stop\n"<<std::endl;
  if (enableFlowMonitor)
    {
	  monitor->CheckForLostPackets ();

	  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
	  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
	  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
	    {
		  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
		  NS_LOG_UNCOND("\nFlow ID: " << i->first << " Source Address " << t.sourceAddress << " Destination Address " << t.destinationAddress);
		  NS_LOG_UNCOND("Tx Packets = " << i->second.txPackets);
		      	  NS_LOG_UNCOND("Rx Packets = " << i->second.rxPackets);
		      	  //NS_LOG_UNCOND("Packets Lost= " << iter->second.txPackets-iter->second.rxPackets);
		      	  NS_LOG_UNCOND("Times forwarded = " << i->second.timesForwarded);
		      	  NS_LOG_UNCOND("Packets lost = " << i->second.lostPackets);

	      if (i->first > 2)
	        {

                  if(t.destinationAddress == "10.1.3.2")
                  {

                    txPacketsum += i->second.txPackets;
                    rxPacketsum += i->second.rxPackets;
                    LostPacketsum += i->second.lostPackets;
                    DropPacketsum += i->second.packetsDropped.size();
                    Delaysum += i->second.delaySum.GetSeconds();
                  }
	        }
	    }
	  cout<<"\n Result of the simulation : \n";
		cout << "  Transmitted Packets: " << txPacketsum << "\n";
        	cout << "  Received Packets: " << rxPacketsum << "\n";
	        cout << "  Delay: " << Delaysum / txPacketsum << "\n";
	        cout << "  Lost Packets: " << LostPacketsum << "\n";
	        cout << "  Drop Packets: " << DropPacketsum << "\n";
	        cout << "  Packets Delivery Ratio: " << ((rxPacketsum * 100) / txPacketsum) << "%" << "\n";
	        cout << "  Packets Lost Ratio: " << ((LostPacketsum * 100) / txPacketsum) << "%" << "\n";
	monitor->SerializeToXmlFile("Question8.flowmon", true, true);
    }

  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
  return 0;
}
