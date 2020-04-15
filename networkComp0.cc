#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>

// Compression Network Topology
//
//       10.1.1.0           10.1.1.0
// n1 -------------- n2 -------------- n3 -------------- n4
//    point-to-point
//
 
void parseConfig(std::map<std::string, std::string> &testing_map, std::string configPath) {

  std::string test = "./testing.ini";
	std::ifstream inifile(configPath);

	char c = '=';

	std::string key;

	std::string value;

	if(inifile.is_open()){

		std::string line;
		while(getline(inifile, line)){	

			size_t equal_pos = line.find(c);

			key = line.substr(0, equal_pos);
			value = line.substr(equal_pos + 1, line.length());
			testing_map[key] = value;
		}
		std::map<std::string, std::string>::iterator itr;
		for(itr = testing_map.begin(); itr != testing_map.end(); ++itr){
			std::cout << itr->first << " = " << itr->second << '\n' << std::endl;
		}

	}else{

		std::cerr << "Coud not open file" << "\n";
	}

}

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{

  std::map<std::string, std::string> testingMap;

  parseConfig(testingMap, "./testing.ini");

  // int srcPort = std::stoi(testingMap.at("src_port_udp"), nullptr, 10);

  int dstPort = std::stoi(testingMap.at("dst_port_udp"), nullptr, 10);

  int payloadSize = std::stoi(testingMap.at("payload_sz"), nullptr, 10);

  NS_LOG_INFO("Setting nPackets");
  uint32_t nPackets = std::stoi(testingMap.at("num_udp_packets"));

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

  UdpEchoServerHelper echoServer (dstPort);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get(3));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces2.GetAddress (1), dstPort);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (payloadSize));

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
