/*
 * Lab5.cc
 *
 *  Created on: 12-Mar-2018
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

NS_LOG_COMPONENT_DEFINE ("Lab5.1");

int main(int argc,char *argv[])
{
	bool verbose = true;
	  uint32_t nCsma = 3;

	  CommandLine cmd;
	  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
	  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

	  cmd.Parse (argc,argv);

	  if (verbose)
	    {
	      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	    }

	  nCsma = nCsma == 0 ? 1 : nCsma;

	  NodeContainer p2pNodes;
	    p2pNodes.Create (2);

	    NodeContainer csmaNodes;
	    csmaNodes.Add (p2pNodes.Get (1));
	    csmaNodes.Create (nCsma);

	    PointToPointHelper pointToPoint;
	     pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
	     pointToPoint.SetChannelAttribute ("Delay", StringValue ("1ms"));

	     NetDeviceContainer p2pDevices;
	       p2pDevices = pointToPoint.Install (p2pNodes);

	      int x=6500;
	       CsmaHelper csma;
	         csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
	         csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (x)));

	      NetDeviceContainer csmaDevices;
	         csmaDevices = csma.Install (csmaNodes);

	      InternetStackHelper stack;
	        stack.Install (p2pNodes.Get (0));
	        stack.Install (csmaNodes);


	      Ipv4AddressHelper address;
	        address.SetBase ("10.1.1.0", "255.255.255.0");
	        Ipv4InterfaceContainer p2pInterfaces;
	        p2pInterfaces = address.Assign (p2pDevices);

	        address.SetBase ("10.1.2.0", "255.255.255.0");
	          Ipv4InterfaceContainer csmaInterfaces;
	          csmaInterfaces = address.Assign (csmaDevices);

	        UdpEchoServerHelper echoServer (9);

	        ApplicationContainer serverApps = echoServer.Install (p2pNodes.Get (0));
	          serverApps.Start (Seconds (1.0));
	          serverApps.Stop (Seconds (15.0));

	          UdpEchoClientHelper echoClient (p2pInterfaces.GetAddress (0), 9);
	            echoClient.SetAttribute ("MaxPackets", UintegerValue (5));
	            echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
	            echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

	            ApplicationContainer clientApps = echoClient.Install (csmaNodes.Get (1));
	            clientApps.Start (Seconds (2.0));
	            clientApps.Stop (Seconds (15.0));
	            ApplicationContainer clientApps1 = echoClient.Install (csmaNodes.Get (2));
	            clientApps1.Start (Seconds (3.0));
	            clientApps1.Stop (Seconds (15.0));
	            ApplicationContainer clientApps2 = echoClient.Install (csmaNodes.Get (3));
	            clientApps2.Start (Seconds (4.0));
	            clientApps2.Stop (Seconds (15.0));

	            Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

	              pointToPoint.EnablePcapAll ("second");
	              csma.EnablePcapAll ("second");
	              FlowMonitorHelper flowHelper;
	              Ptr<FlowMonitor> flowMonitor;

	              flowMonitor = flowHelper.InstallAll();
	              Simulator :: Stop(Seconds(15.0));
	              //For animation
	             AnimationInterface anim ("lab5.xml");
	                 /*anim.SetConstantPosition(p2pNodes.Get(0),10.0,20.0);
	                 anim.SetConstantPosition(p2pNodes.Get(1),30.0,20.0);
	                 anim.SetConstantPosition(csmaNodes.Get(1),45.0, 10.0);
	                 anim.SetConstantPosition(csmaNodes.Get(2), 45.0, 20.0);
	                 anim.SetConstantPosition(csmaNodes.Get(3),45.0,30.0);*/

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
	                std::cout<<"  Delay : "<<i->second.delaySum<<"\n";
	              	  delay += (i->second.delaySum)/(double)i->second.rxPackets;
	              	std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
	              	throughput+=(i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024);
	                   }


	                std::cout<<"\nTotal transmitted packets : "<<tpackets<<"\n";
	                std::cout<<"Total received packets : "<<rpackets<<"\n";
	                std::cout<<"Average Throughput : " <<throughput/6<<" Mbps\n";
	                std::cout<<"Average Delay : "<<delay/6<<"\n";

	               flowMonitor->SerializeToXmlFile("lab5Flow.xml",true, true);
	               Simulator::Destroy ();
	               return 0;

}


