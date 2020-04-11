#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

// Compression Network Topology
//
//       10.1.1.0           10.1.1.0
// n1 -------------- n2 -------------- n3 -------------- n4
//    point-to-point
//
 
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{

  NS_LOG_INFO("Setting nPackets");
  uint32_t nPackets = 1;

  CommandLine cmd;
  cmd.AddValue("nPackets", "Number of packets to echo", nPackets);
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);


   NS_LOG_INFO ("Create nodes.");
   NodeContainer nodes;
   nodes.Create (4);


  PointToPointHelper pointToPoint;

  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("5ms"));
  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes.Get(0), nodes.Get(1));


  PointToPointHelper pointToPoint2;

  pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  pointToPoint2.SetChannelAttribute ("Delay", StringValue ("5ms"));
  NetDeviceContainer devices1;
  devices1 = pointToPoint2.Install (nodes.Get(1), nodes.Get(2));

  PointToPointHelper pointToPoint3;

  pointToPoint3.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
  pointToPoint3.SetChannelAttribute ("Delay", StringValue ("5ms"));
  NetDeviceContainer devices2;
  devices2 = pointToPoint3.Install (nodes.Get(2), nodes.Get(3));



  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces0 = address.Assign (devices);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces1 = address.Assign (devices1);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces2 = address.Assign (devices2);

  UdpEchoServerHelper echoServer (9999);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get(3));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces2.GetAddress (1), 9999);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get(0));
  clientApps.Start(Seconds (2.0));
  clientApps.Stop(Seconds (7.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  Simulator::Stop(Seconds (30));

  NS_LOG_INFO ("Run Simulation.");

  Simulator::Run ();
  Simulator::Destroy ();

  NS_LOG_INFO ("Done.");
  return 0;
}
