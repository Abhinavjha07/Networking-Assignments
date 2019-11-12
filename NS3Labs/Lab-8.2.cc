/*
NS-3 Assignment
Done by : Abhinav Jha
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SimplePointToPointOlsrExample");

int
main (int argc, char *argv[])
{
 
  Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (210));
  Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("448kb/s"));

  CommandLine cmd;
  cmd.Parse (argc, argv);

  NS_LOG_INFO ("Create nodes.");
  NodeContainer c;
  c.Create (15);

  NodeContainer n01 = NodeContainer (c.Get (0), c.Get (1));
  NodeContainer n02 = NodeContainer (c.Get (0), c.Get (2));
  NodeContainer n03 = NodeContainer (c.Get (0), c.Get (3));
  NodeContainer n04 = NodeContainer (c.Get (0), c.Get (4));
  NodeContainer n05 = NodeContainer (c.Get (0), c.Get (5));
  NodeContainer n06 = NodeContainer (c.Get (0), c.Get (6));
  NodeContainer n07 = NodeContainer (c.Get (0), c.Get (7));
  NodeContainer n08 = NodeContainer (c.Get (0), c.Get (8));
  NodeContainer n09 = NodeContainer (c.Get (0), c.Get (9));
  NodeContainer n010 = NodeContainer (c.Get (0), c.Get (10));
  NodeContainer n011 = NodeContainer (c.Get (0), c.Get (11));
  NodeContainer n012 = NodeContainer (c.Get (0), c.Get (12));
  NodeContainer n013 = NodeContainer (c.Get (0), c.Get (13));
  NodeContainer n014 = NodeContainer (c.Get (0), c.Get (14));

  NodeContainer n12 = NodeContainer (c.Get (1), c.Get (2));
  NodeContainer n13 = NodeContainer (c.Get (1), c.Get (3));
  NodeContainer n14 = NodeContainer (c.Get (1), c.Get (4));
  NodeContainer n15 = NodeContainer (c.Get (1), c.Get (5));
  NodeContainer n16 = NodeContainer (c.Get (1), c.Get (6));
  NodeContainer n17 = NodeContainer (c.Get (1), c.Get (7));
  NodeContainer n18 = NodeContainer (c.Get (1), c.Get (8));
  NodeContainer n19 = NodeContainer (c.Get (1), c.Get (9));
  NodeContainer n110 = NodeContainer (c.Get (1), c.Get (10));
  NodeContainer n111 = NodeContainer (c.Get (1), c.Get (11));
  NodeContainer n112 = NodeContainer (c.Get (1), c.Get (12));
  NodeContainer n113 = NodeContainer (c.Get (1), c.Get (13));
  NodeContainer n114 = NodeContainer (c.Get (1), c.Get (14));

  NodeContainer n23 = NodeContainer (c.Get (2), c.Get (3));
  NodeContainer n24 = NodeContainer (c.Get (2), c.Get (4)); 
  NodeContainer n25 = NodeContainer (c.Get (2), c.Get (5));
  NodeContainer n26 = NodeContainer (c.Get (2), c.Get (6));
  NodeContainer n27 = NodeContainer (c.Get (2), c.Get (7));
  NodeContainer n28 = NodeContainer (c.Get (2), c.Get (8));
  NodeContainer n29 = NodeContainer (c.Get (2), c.Get (9));
  NodeContainer n210 = NodeContainer (c.Get (2), c.Get (10));
  NodeContainer n211 = NodeContainer (c.Get (2), c.Get (11));
  NodeContainer n212 = NodeContainer (c.Get (2), c.Get (12));
  NodeContainer n213 = NodeContainer (c.Get (2), c.Get (13));
  NodeContainer n214 = NodeContainer (c.Get (2), c.Get (14));

  NodeContainer n34 = NodeContainer (c.Get (3), c.Get (4));
  NodeContainer n35 = NodeContainer (c.Get (3), c.Get (5));
  NodeContainer n36 = NodeContainer (c.Get (3), c.Get (6));
  NodeContainer n37 = NodeContainer (c.Get (3), c.Get (7));
  NodeContainer n38 = NodeContainer (c.Get (3), c.Get (8));
  NodeContainer n39 = NodeContainer (c.Get (3), c.Get (9));
  NodeContainer n310 = NodeContainer (c.Get (3), c.Get (10));
  NodeContainer n311 = NodeContainer (c.Get (3), c.Get (11));
  NodeContainer n312 = NodeContainer (c.Get (3), c.Get (12));
  NodeContainer n313 = NodeContainer (c.Get (3), c.Get (13));
  NodeContainer n314 = NodeContainer (c.Get (3), c.Get (14));

  NodeContainer n45 = NodeContainer (c.Get (4), c.Get (5));
  NodeContainer n46 = NodeContainer (c.Get (4), c.Get (6));
  NodeContainer n47 = NodeContainer (c.Get (4), c.Get (7));
  NodeContainer n48 = NodeContainer (c.Get (4), c.Get (8));
  NodeContainer n49 = NodeContainer (c.Get (4), c.Get (9));
  NodeContainer n410 = NodeContainer (c.Get (4), c.Get (10));
  NodeContainer n411 = NodeContainer (c.Get (4), c.Get (11));
  NodeContainer n412 = NodeContainer (c.Get (4), c.Get (12));
  NodeContainer n413 = NodeContainer (c.Get (4), c.Get (13));
  NodeContainer n414 = NodeContainer (c.Get (4), c.Get (14));

  NodeContainer n56 = NodeContainer (c.Get (5), c.Get (6));
  NodeContainer n57 = NodeContainer (c.Get (5), c.Get (7));
  NodeContainer n58 = NodeContainer (c.Get (5), c.Get (8));
  NodeContainer n59 = NodeContainer (c.Get (5), c.Get (9));
  NodeContainer n510 = NodeContainer (c.Get (5), c.Get (10));
  NodeContainer n511 = NodeContainer (c.Get (5), c.Get (11));
  NodeContainer n512 = NodeContainer (c.Get (5), c.Get (12));
  NodeContainer n513 = NodeContainer (c.Get (5), c.Get (13));
  NodeContainer n514 = NodeContainer (c.Get (5), c.Get (14));

  NodeContainer n67 = NodeContainer (c.Get (6), c.Get (7));
  NodeContainer n68 = NodeContainer (c.Get (6), c.Get (8));
  NodeContainer n69 = NodeContainer (c.Get (6), c.Get (9));
  NodeContainer n610 = NodeContainer (c.Get (6), c.Get (10));
  NodeContainer n611 = NodeContainer (c.Get (6), c.Get (11));
  NodeContainer n612 = NodeContainer (c.Get (6), c.Get (12));
  NodeContainer n613 = NodeContainer (c.Get (6), c.Get (13));
  NodeContainer n614 = NodeContainer (c.Get (6), c.Get (14));

  NodeContainer n78 = NodeContainer (c.Get (7), c.Get (8));
  NodeContainer n79 = NodeContainer (c.Get (7), c.Get (9));
  NodeContainer n710 = NodeContainer (c.Get (7), c.Get (10));
  NodeContainer n711 = NodeContainer (c.Get (7), c.Get (11));
  NodeContainer n712 = NodeContainer (c.Get (7), c.Get (12));
  NodeContainer n713 = NodeContainer (c.Get (7), c.Get (13));
  NodeContainer n714 = NodeContainer (c.Get (7), c.Get (14));

  NodeContainer n89 = NodeContainer (c.Get (8), c.Get (9));
  NodeContainer n810 = NodeContainer (c.Get (8), c.Get (10));
  NodeContainer n811 = NodeContainer (c.Get (8), c.Get (11));
  NodeContainer n812 = NodeContainer (c.Get (8), c.Get (12));
  NodeContainer n813 = NodeContainer (c.Get (8), c.Get (13));
  NodeContainer n814 = NodeContainer (c.Get (8), c.Get (14));

  NodeContainer n910 = NodeContainer (c.Get (9), c.Get (10));
  NodeContainer n911 = NodeContainer (c.Get (9), c.Get (11));
  NodeContainer n912 = NodeContainer (c.Get (9), c.Get (12));
  NodeContainer n913 = NodeContainer (c.Get (9), c.Get (13));
  NodeContainer n914 = NodeContainer (c.Get (9), c.Get (14));

  NodeContainer n1011 = NodeContainer (c.Get (10), c.Get (11));
  NodeContainer n1012 = NodeContainer (c.Get (10), c.Get (12));
  NodeContainer n1013 = NodeContainer (c.Get (10), c.Get (13));
  NodeContainer n1014 = NodeContainer (c.Get (10), c.Get (14));

  NodeContainer n1112 = NodeContainer (c.Get (11), c.Get (12));
  NodeContainer n1113 = NodeContainer (c.Get (11), c.Get (13));
  NodeContainer n1114 = NodeContainer (c.Get (11), c.Get (14));

  NodeContainer n1213 = NodeContainer (c.Get (12), c.Get (13));
  NodeContainer n1214 = NodeContainer (c.Get (12), c.Get (14));

  NodeContainer n1314 = NodeContainer (c.Get (13), c.Get (14));


  // Enable OLSR
  NS_LOG_INFO ("Enabling OLSR Routing.");
  OlsrHelper olsr;

  Ipv4StaticRoutingHelper staticRouting;

  Ipv4ListRoutingHelper list;
  list.Add (staticRouting, 0);
  list.Add (olsr, 10);

  InternetStackHelper internet;
  internet.SetRoutingHelper (list); // has effect on the next Install ()
  internet.Install (c);

  // We create the channels first without any IP addressing information
  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  NetDeviceContainer nd01 = p2p.Install (n01);
  NetDeviceContainer nd02 = p2p.Install (n02);
  NetDeviceContainer nd03 = p2p.Install (n03);
  NetDeviceContainer nd04 = p2p.Install (n04);
  NetDeviceContainer nd05 = p2p.Install (n05);
  NetDeviceContainer nd06 = p2p.Install (n06);
  NetDeviceContainer nd07 = p2p.Install (n07);
  NetDeviceContainer nd08 = p2p.Install (n08);
  NetDeviceContainer nd09 = p2p.Install (n09);
  NetDeviceContainer nd010 = p2p.Install (n010);
  NetDeviceContainer nd011 = p2p.Install (n011);
  NetDeviceContainer nd012 = p2p.Install (n012);
  NetDeviceContainer nd013 = p2p.Install (n013);
  NetDeviceContainer nd014 = p2p.Install (n014);

  NetDeviceContainer nd12 = p2p.Install (n12);
  NetDeviceContainer nd13 = p2p.Install (n13);
  NetDeviceContainer nd14 = p2p.Install (n14);
  NetDeviceContainer nd15 = p2p.Install (n15);
  NetDeviceContainer nd16 = p2p.Install (n16);
  NetDeviceContainer nd17 = p2p.Install (n17);
  NetDeviceContainer nd18 = p2p.Install (n18);
  NetDeviceContainer nd19 = p2p.Install (n19);
  NetDeviceContainer nd110 = p2p.Install (n110);
  NetDeviceContainer nd111 = p2p.Install (n111);
  NetDeviceContainer nd112 = p2p.Install (n112);
  NetDeviceContainer nd113 = p2p.Install (n113);
  NetDeviceContainer nd114 = p2p.Install (n114);
 
  NetDeviceContainer nd23 = p2p.Install (n23);
  NetDeviceContainer nd24 = p2p.Install (n24);
  NetDeviceContainer nd25 = p2p.Install (n25);
  NetDeviceContainer nd26 = p2p.Install (n26);
  NetDeviceContainer nd27 = p2p.Install (n27);
  NetDeviceContainer nd28 = p2p.Install (n28);
  NetDeviceContainer nd29 = p2p.Install (n29);
  NetDeviceContainer nd210 = p2p.Install (n210);
  NetDeviceContainer nd211 = p2p.Install (n211);
  NetDeviceContainer nd212 = p2p.Install (n212);
  NetDeviceContainer nd213 = p2p.Install (n213);
  NetDeviceContainer nd214 = p2p.Install (n214);
 
  NetDeviceContainer nd34 = p2p.Install (n34);
  NetDeviceContainer nd35 = p2p.Install (n35);
  NetDeviceContainer nd36 = p2p.Install (n36);
  NetDeviceContainer nd37 = p2p.Install (n37);
  NetDeviceContainer nd38 = p2p.Install (n38);
  NetDeviceContainer nd39 = p2p.Install (n39);
  NetDeviceContainer nd310 = p2p.Install (n310);
  NetDeviceContainer nd311 = p2p.Install (n311);
  NetDeviceContainer nd312 = p2p.Install (n312);
  NetDeviceContainer nd313 = p2p.Install (n313);
  NetDeviceContainer nd314 = p2p.Install (n314);
 
  NetDeviceContainer nd45 = p2p.Install (n45);
  NetDeviceContainer nd46 = p2p.Install (n46);
  NetDeviceContainer nd47 = p2p.Install (n47);
  NetDeviceContainer nd48 = p2p.Install (n48);
  NetDeviceContainer nd49 = p2p.Install (n49);
  NetDeviceContainer nd410 = p2p.Install (n410);
  NetDeviceContainer nd411 = p2p.Install (n411);
  NetDeviceContainer nd412 = p2p.Install (n412);
  NetDeviceContainer nd413 = p2p.Install (n413);
  NetDeviceContainer nd414 = p2p.Install (n414);

  NetDeviceContainer nd56 = p2p.Install (n56);
  NetDeviceContainer nd57 = p2p.Install (n57);
  NetDeviceContainer nd58 = p2p.Install (n58);
  NetDeviceContainer nd59 = p2p.Install (n59);
  NetDeviceContainer nd510 = p2p.Install (n510);
  NetDeviceContainer nd511 = p2p.Install (n511);
  NetDeviceContainer nd512 = p2p.Install (n512);
  NetDeviceContainer nd513 = p2p.Install (n513);
  NetDeviceContainer nd514 = p2p.Install (n514);

  NetDeviceContainer nd67 = p2p.Install (n67);
  NetDeviceContainer nd68 = p2p.Install (n68);
  NetDeviceContainer nd69 = p2p.Install (n69);
  NetDeviceContainer nd610 = p2p.Install (n610);
  NetDeviceContainer nd611 = p2p.Install (n611);
  NetDeviceContainer nd612 = p2p.Install (n612);
  NetDeviceContainer nd613 = p2p.Install (n613);
  NetDeviceContainer nd614 = p2p.Install (n614);

  NetDeviceContainer nd78 = p2p.Install (n78);
  NetDeviceContainer nd79 = p2p.Install (n79);
  NetDeviceContainer nd710 = p2p.Install (n710);
  NetDeviceContainer nd711 = p2p.Install (n711);
  NetDeviceContainer nd712 = p2p.Install (n712);
  NetDeviceContainer nd713 = p2p.Install (n713);
  NetDeviceContainer nd714 = p2p.Install (n714);

  NetDeviceContainer nd89 = p2p.Install (n89);
  NetDeviceContainer nd810 = p2p.Install (n810);
  NetDeviceContainer nd811 = p2p.Install (n811);
  NetDeviceContainer nd812 = p2p.Install (n812);
  NetDeviceContainer nd813 = p2p.Install (n813);
  NetDeviceContainer nd814 = p2p.Install (n814);

  NetDeviceContainer nd910 = p2p.Install (n910);
  NetDeviceContainer nd911 = p2p.Install (n911);
  NetDeviceContainer nd912 = p2p.Install (n912);
  NetDeviceContainer nd913 = p2p.Install (n913);
  NetDeviceContainer nd914 = p2p.Install (n914);

  NetDeviceContainer nd1011 = p2p.Install (n1011);
  NetDeviceContainer nd1012 = p2p.Install (n1012);
  NetDeviceContainer nd1013 = p2p.Install (n1013);
  NetDeviceContainer nd1014 = p2p.Install (n1014);

  NetDeviceContainer nd1112 = p2p.Install (n1112);
  NetDeviceContainer nd1113 = p2p.Install (n1113);
  NetDeviceContainer nd1114 = p2p.Install (n1114);

  NetDeviceContainer nd1213 = p2p.Install (n1213);
  NetDeviceContainer nd1214 = p2p.Install (n1214);

  NetDeviceContainer nd1314 = p2p.Install (n1314);

  // Later, we add IP addresses.
  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i01 = ipv4.Assign (nd01);
  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i02 = ipv4.Assign (nd02);
  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i03 = ipv4.Assign (nd03);
  ipv4.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i04 = ipv4.Assign (nd04);
  ipv4.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer i05 = ipv4.Assign (nd05);
  ipv4.SetBase ("10.1.6.0", "255.255.255.0");
  Ipv4InterfaceContainer i06 = ipv4.Assign (nd06);
  ipv4.SetBase ("10.1.7.0", "255.255.255.0");
  Ipv4InterfaceContainer i07 = ipv4.Assign (nd07);
  ipv4.SetBase ("10.1.8.0", "255.255.255.0");
  Ipv4InterfaceContainer i08 = ipv4.Assign (nd08);
  ipv4.SetBase ("10.1.9.0", "255.255.255.0");
  Ipv4InterfaceContainer i09 = ipv4.Assign (nd09);
  ipv4.SetBase ("10.1.10.0", "255.255.255.0");
  Ipv4InterfaceContainer i010 = ipv4.Assign (nd010);
  ipv4.SetBase ("10.1.11.0", "255.255.255.0");
  Ipv4InterfaceContainer i011 = ipv4.Assign (nd011);
  ipv4.SetBase ("10.1.12.0", "255.255.255.0");
  Ipv4InterfaceContainer i012 = ipv4.Assign (nd012);
  ipv4.SetBase ("10.1.13.0", "255.255.255.0");
  Ipv4InterfaceContainer i013 = ipv4.Assign (nd013);
  ipv4.SetBase ("10.1.14.0", "255.255.255.0");
  Ipv4InterfaceContainer i014 = ipv4.Assign (nd014);


  ipv4.SetBase ("10.1.15.0", "255.255.255.0");
  Ipv4InterfaceContainer i12 = ipv4.Assign (nd12);
  ipv4.SetBase ("10.1.16.0", "255.255.255.0");
  Ipv4InterfaceContainer i13 = ipv4.Assign (nd13);
  ipv4.SetBase ("10.1.17.0", "255.255.255.0");
  Ipv4InterfaceContainer i14 = ipv4.Assign (nd14);
  ipv4.SetBase ("10.1.18.0", "255.255.255.0");
  Ipv4InterfaceContainer i15 = ipv4.Assign (nd15);
  ipv4.SetBase ("10.1.19.0", "255.255.255.0");
  Ipv4InterfaceContainer i16 = ipv4.Assign (nd16);
  ipv4.SetBase ("10.1.20.0", "255.255.255.0");
  Ipv4InterfaceContainer i17 = ipv4.Assign (nd17);
  ipv4.SetBase ("10.1.21.0", "255.255.255.0");
  Ipv4InterfaceContainer i18 = ipv4.Assign (nd18);
  ipv4.SetBase ("10.1.22.0", "255.255.255.0");
  Ipv4InterfaceContainer i19 = ipv4.Assign (nd19);
  ipv4.SetBase ("10.1.23.0", "255.255.255.0");
  Ipv4InterfaceContainer i110 = ipv4.Assign (nd110);
  ipv4.SetBase ("10.1.24.0", "255.255.255.0");
  Ipv4InterfaceContainer i111 = ipv4.Assign (nd111);
  ipv4.SetBase ("10.1.25.0", "255.255.255.0");
  Ipv4InterfaceContainer i112 = ipv4.Assign (nd112);
  ipv4.SetBase ("10.1.26.0", "255.255.255.0");
  Ipv4InterfaceContainer i113 = ipv4.Assign (nd113);
  ipv4.SetBase ("10.1.27.0", "255.255.255.0");
  Ipv4InterfaceContainer i114 = ipv4.Assign (nd114);


  ipv4.SetBase ("10.1.28.0", "255.255.255.0");
  Ipv4InterfaceContainer i23 = ipv4.Assign (nd23);
  ipv4.SetBase ("10.1.29.0", "255.255.255.0");
  Ipv4InterfaceContainer i24 = ipv4.Assign (nd24);
  ipv4.SetBase ("10.1.150.0", "255.255.255.0");
  Ipv4InterfaceContainer i25 = ipv4.Assign (nd25);
  ipv4.SetBase ("10.1.30.0", "255.255.255.0");
  Ipv4InterfaceContainer i26 = ipv4.Assign (nd26);
  ipv4.SetBase ("10.1.31.0", "255.255.255.0");
  Ipv4InterfaceContainer i27 = ipv4.Assign (nd27);
  ipv4.SetBase ("10.1.32.0", "255.255.255.0");
  Ipv4InterfaceContainer i28 = ipv4.Assign (nd28);
  ipv4.SetBase ("10.1.33.0", "255.255.255.0");
  Ipv4InterfaceContainer i29 = ipv4.Assign (nd29);
  ipv4.SetBase ("10.1.34.0", "255.255.255.0");
  Ipv4InterfaceContainer i210 = ipv4.Assign (nd210);
  ipv4.SetBase ("10.1.35.0", "255.255.255.0");
  Ipv4InterfaceContainer i211 = ipv4.Assign (nd211);
  ipv4.SetBase ("10.1.36.0", "255.255.255.0");
  Ipv4InterfaceContainer i212 = ipv4.Assign (nd212);
  ipv4.SetBase ("10.1.37.0", "255.255.255.0");
  Ipv4InterfaceContainer i213 = ipv4.Assign (nd213);
  ipv4.SetBase ("10.1.38.0", "255.255.255.0");
  Ipv4InterfaceContainer i214 = ipv4.Assign (nd214);


  ipv4.SetBase ("10.1.39.0", "255.255.255.0");
  Ipv4InterfaceContainer i34 = ipv4.Assign (nd34);
  ipv4.SetBase ("10.1.40.0", "255.255.255.0");
  Ipv4InterfaceContainer i35 = ipv4.Assign (nd35);
  ipv4.SetBase ("10.1.41.0", "255.255.255.0");
  Ipv4InterfaceContainer i36 = ipv4.Assign (nd36);
  ipv4.SetBase ("10.1.42.0", "255.255.255.0");
  Ipv4InterfaceContainer i37 = ipv4.Assign (nd37);
  ipv4.SetBase ("10.1.43.0", "255.255.255.0");
  Ipv4InterfaceContainer i38 = ipv4.Assign (nd38);
  ipv4.SetBase ("10.1.44.0", "255.255.255.0");
  Ipv4InterfaceContainer i39 = ipv4.Assign (nd39);
  ipv4.SetBase ("10.1.45.0", "255.255.255.0");
  Ipv4InterfaceContainer i310 = ipv4.Assign (nd310);
  ipv4.SetBase ("10.1.46.0", "255.255.255.0");
  Ipv4InterfaceContainer i311 = ipv4.Assign (nd311);
  ipv4.SetBase ("10.1.47.0", "255.255.255.0");
  Ipv4InterfaceContainer i312 = ipv4.Assign (nd312);
  ipv4.SetBase ("10.1.48.0", "255.255.255.0");
  Ipv4InterfaceContainer i313 = ipv4.Assign (nd313);
  ipv4.SetBase ("10.1.49.0", "255.255.255.0");
  Ipv4InterfaceContainer i314 = ipv4.Assign (nd314);


  ipv4.SetBase ("10.1.50.0", "255.255.255.0");
  Ipv4InterfaceContainer i45 = ipv4.Assign (nd45);
  ipv4.SetBase ("10.1.51.0", "255.255.255.0");
  Ipv4InterfaceContainer i46 = ipv4.Assign (nd46);
  ipv4.SetBase ("10.1.52.0", "255.255.255.0");
  Ipv4InterfaceContainer i47 = ipv4.Assign (nd47);
  ipv4.SetBase ("10.1.53.0", "255.255.255.0");
  Ipv4InterfaceContainer i48 = ipv4.Assign (nd48);
  ipv4.SetBase ("10.1.54.0", "255.255.255.0");
  Ipv4InterfaceContainer i49 = ipv4.Assign (nd49);
  ipv4.SetBase ("10.1.55.0", "255.255.255.0");
  Ipv4InterfaceContainer i410 = ipv4.Assign (nd010);
  ipv4.SetBase ("10.1.56.0", "255.255.255.0");
  Ipv4InterfaceContainer i411 = ipv4.Assign (nd411);
  ipv4.SetBase ("10.1.57.0", "255.255.255.0");
  Ipv4InterfaceContainer i412 = ipv4.Assign (nd412);
  ipv4.SetBase ("10.1.58.0", "255.255.255.0");
  Ipv4InterfaceContainer i413 = ipv4.Assign (nd413);
  ipv4.SetBase ("10.1.59.0", "255.255.255.0");
  Ipv4InterfaceContainer i414 = ipv4.Assign (nd414);


  ipv4.SetBase ("10.1.60.0", "255.255.255.0");
  Ipv4InterfaceContainer i56 = ipv4.Assign (nd56);
  ipv4.SetBase ("10.1.61.0", "255.255.255.0");
  Ipv4InterfaceContainer i57 = ipv4.Assign (nd57);
  ipv4.SetBase ("10.1.62.0", "255.255.255.0");
  Ipv4InterfaceContainer i58 = ipv4.Assign (nd58);
  ipv4.SetBase ("10.1.63.0", "255.255.255.0");
  Ipv4InterfaceContainer i59 = ipv4.Assign (nd59);
  ipv4.SetBase ("10.1.64.0", "255.255.255.0");
  Ipv4InterfaceContainer i510 = ipv4.Assign (nd510);
  ipv4.SetBase ("10.1.65.0", "255.255.255.0");
  Ipv4InterfaceContainer i511 = ipv4.Assign (nd511);
  ipv4.SetBase ("10.1.66.0", "255.255.255.0");
  Ipv4InterfaceContainer i512 = ipv4.Assign (nd512);
  ipv4.SetBase ("10.1.67.0", "255.255.255.0");
  Ipv4InterfaceContainer i513 = ipv4.Assign (nd513);
  ipv4.SetBase ("10.1.68.0", "255.255.255.0");
  Ipv4InterfaceContainer i514 = ipv4.Assign (nd514);


  ipv4.SetBase ("10.1.69.0", "255.255.255.0");
  Ipv4InterfaceContainer i67 = ipv4.Assign (nd67);
  ipv4.SetBase ("10.1.70.0", "255.255.255.0");
  Ipv4InterfaceContainer i68 = ipv4.Assign (nd68);
  ipv4.SetBase ("10.1.71.0", "255.255.255.0");
  Ipv4InterfaceContainer i69 = ipv4.Assign (nd69);
  ipv4.SetBase ("10.1.72.0", "255.255.255.0");
  Ipv4InterfaceContainer i610 = ipv4.Assign (nd610);
  ipv4.SetBase ("10.1.73.0", "255.255.255.0");
  Ipv4InterfaceContainer i611 = ipv4.Assign (nd611);
  ipv4.SetBase ("10.1.74.0", "255.255.255.0");
  Ipv4InterfaceContainer i612 = ipv4.Assign (nd612);
  ipv4.SetBase ("10.1.75.0", "255.255.255.0");
  Ipv4InterfaceContainer i613 = ipv4.Assign (nd613);
  ipv4.SetBase ("10.1.76.0", "255.255.255.0");
  Ipv4InterfaceContainer i614 = ipv4.Assign (nd614);


  ipv4.SetBase ("10.1.77.0", "255.255.255.0");
  Ipv4InterfaceContainer i78 = ipv4.Assign (nd78);
  ipv4.SetBase ("10.1.78.0", "255.255.255.0");
  Ipv4InterfaceContainer i79 = ipv4.Assign (nd79);
  ipv4.SetBase ("10.1.79.0", "255.255.255.0");
  Ipv4InterfaceContainer i710 = ipv4.Assign (nd710);
  ipv4.SetBase ("10.1.80.0", "255.255.255.0");
  Ipv4InterfaceContainer i711 = ipv4.Assign (nd711);
  ipv4.SetBase ("10.1.81.0", "255.255.255.0");
  Ipv4InterfaceContainer i712 = ipv4.Assign (nd712);
  ipv4.SetBase ("10.1.82.0", "255.255.255.0");
  Ipv4InterfaceContainer i713 = ipv4.Assign (nd713);
  ipv4.SetBase ("10.1.83.0", "255.255.255.0");
  Ipv4InterfaceContainer i714 = ipv4.Assign (nd714);


  ipv4.SetBase ("10.1.84.0", "255.255.255.0");
  Ipv4InterfaceContainer i89 = ipv4.Assign (nd89);
  ipv4.SetBase ("10.1.85.0", "255.255.255.0");
  Ipv4InterfaceContainer i810 = ipv4.Assign (nd810);
  ipv4.SetBase ("10.1.86.0", "255.255.255.0");
  Ipv4InterfaceContainer i811 = ipv4.Assign (nd811);
  ipv4.SetBase ("10.1.87.0", "255.255.255.0");
  Ipv4InterfaceContainer i812 = ipv4.Assign (nd812);
  ipv4.SetBase ("10.1.88.0", "255.255.255.0");
  Ipv4InterfaceContainer i813 = ipv4.Assign (nd813);
  ipv4.SetBase ("10.1.89.0", "255.255.255.0");
  Ipv4InterfaceContainer i814 = ipv4.Assign (nd814);


  ipv4.SetBase ("10.1.90.0", "255.255.255.0");
  Ipv4InterfaceContainer i910 = ipv4.Assign (nd910);
  ipv4.SetBase ("10.1.91.0", "255.255.255.0");
  Ipv4InterfaceContainer i911 = ipv4.Assign (nd911);
  ipv4.SetBase ("10.1.92.0", "255.255.255.0");
  Ipv4InterfaceContainer i912 = ipv4.Assign (nd912);
  ipv4.SetBase ("10.1.93.0", "255.255.255.0");
  Ipv4InterfaceContainer i913 = ipv4.Assign (nd913);
  ipv4.SetBase ("10.1.94.0", "255.255.255.0");
  Ipv4InterfaceContainer i914 = ipv4.Assign (nd914);


  ipv4.SetBase ("10.1.95.0", "255.255.255.0");
  Ipv4InterfaceContainer i1011 = ipv4.Assign (nd1011);
  ipv4.SetBase ("10.1.96.0", "255.255.255.0");
  Ipv4InterfaceContainer i1012 = ipv4.Assign (nd1012);
  ipv4.SetBase ("10.1.97.0", "255.255.255.0");
  Ipv4InterfaceContainer i1013 = ipv4.Assign (nd1013);
  ipv4.SetBase ("10.1.98.0", "255.255.255.0");
  Ipv4InterfaceContainer i1014 = ipv4.Assign (nd1014);


  ipv4.SetBase ("10.1.99.0", "255.255.255.0");
  Ipv4InterfaceContainer i1112 = ipv4.Assign (nd1112);
  ipv4.SetBase ("10.1.100.0", "255.255.255.0");
  Ipv4InterfaceContainer i1113 = ipv4.Assign (nd1113);
  ipv4.SetBase ("10.1.104.0", "255.255.255.0");
  Ipv4InterfaceContainer i1114 = ipv4.Assign (nd1114);


  ipv4.SetBase ("10.1.101.0", "255.255.255.0");
  Ipv4InterfaceContainer i1213 = ipv4.Assign (nd1213);
  ipv4.SetBase ("10.1.102.0", "255.255.255.0");
  Ipv4InterfaceContainer i1214 = ipv4.Assign (nd1214);

  ipv4.SetBase ("10.1.103.0", "255.255.255.0");
  Ipv4InterfaceContainer i1314 = ipv4.Assign (nd1314);


  // Create the OnOff application to send UDP datagrams of size
  // 210 bytes at a rate of 448 Kb/s from n0 to n4
  NS_LOG_INFO ("Create Applications.");
  uint16_t port = 9;   // Discard port (RFC 863)

  OnOffHelper onoff ("ns3::UdpSocketFactory",
                     InetSocketAddress (i34.GetAddress (1), port));
  onoff.SetConstantRate (DataRate ("448kb/s"));

  ApplicationContainer apps = onoff.Install (c.Get (0));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  // Create a packet sink to receive these packets
  PacketSinkHelper sink ("ns3::UdpSocketFactory",
                         InetSocketAddress (Ipv4Address::GetAny (), port));

  apps = sink.Install (c.Get (3));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  // Create a similar flow from n3 to n1, starting at time 1.1 seconds
  onoff.SetAttribute ("Remote",
                      AddressValue (InetSocketAddress (i12.GetAddress (0), port)));
  apps = onoff.Install (c.Get (3));
  apps.Start (Seconds (1.1));
  apps.Stop (Seconds (10.0));

  // Create a packet sink to receive these packets
  apps = sink.Install (c.Get (1));
  apps.Start (Seconds (1.1));
  apps.Stop (Seconds (10.0));

  AsciiTraceHelper ascii;
  p2p.EnableAsciiAll (ascii.CreateFileStream ("simple-point-to-point-olsr.tr"));
  p2p.EnablePcapAll ("simple-point-to-point-olsr");

  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (("olsr-15-nodes.routes"), std::ios::out);
  olsr.PrintRoutingTableAllAt (Seconds (0.1), routingStream);
 
  Simulator::Stop (Seconds (30));
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();


  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
//  Simulator->CheckForLostPackets ();

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
	  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
     
          std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
          std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
          std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
      	  std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
      
     }



  monitor->SerializeToXmlFile("olsr-monitor.flowmon", true, true);

  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");

  return 0;
}
