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

bool run_sim = false;

void print_map(std::map<std::string, std::string> &testing_map){
  std::map<std::string, std::string>::iterator itr;
  int i = 1;
  for(itr = testing_map.begin(); itr != testing_map.end(); ++itr){
    std::cout << i << ". " << itr->first << " = " << itr->second<< "\n";
    i++;
  }
}

void print_menu(std::map<std::string, std::string> &testing_map){

  std::cout <<"****************************************************\n";
  std::cout << " \tNetwork Compression Detection Portal\n";
  std::cout <<"****************************************************\n";
  std::cout << " "<< "To update Testing Configuration(s) please enter\t\n";
  std::cout << " "<< "the *ID Number* of the configuration item\t\n";
  std::cout << " "<< "otherwise please enter RUN to run simulator\t\n";
  std::cout << " "<< "with current Testing configurations\t\n";
  std::cout <<"___________________________________________________\n";
  std::cout << "Current Testing Configurations: \n\n";
  print_map(testing_map);
  std::cout <<"___________________________________________________\n";
  std::cout << "Would you like to update a test configuration [YES] or [RUN] for Simulation:  ";

  std::string update_menu;
  std::cin >> update_menu;

  while(update_menu == "YES" || update_menu == "RUN"){

    if(update_menu == "YES"){

      std::string id;
      std::cout << "Please enter the test configuration ID: ";
      std::cin >> id;

      int configuration_id = std::stoi(id, nullptr, 10);

      std::string value_change;

      switch(configuration_id){

        case 1:
             
              std::cout<<"Please enter numrial value for new dts_port_tcp_head:";
              std::cin >> value_change;
              testing_map["dst_port_tcp_head"] = value_change;
              break;
        case 2:
           
              std::cout<< "Please enter numrial value for new dts_port_tcp_tail:";
              std::cin >> value_change;
              testing_map["dst_port_tcp_tail"] = value_change;
              
              break;
        case 3:
           
              std::cout<<"Please enter numrial value for new dts_port_tcp_udp:";
              std::cin >> value_change;
              testing_map["dst_port_udp"] = value_change;
             
              break;
        case 4:
             
              std::cout<<"Please enter numrial value for new inter_measurement time:";
              std::cin >> value_change;
              testing_map["inter_measurement_time"]= value_change;
             
              break;
        case 5:
             
              std::cout<<"Please enter numrial value for numbr of UDP Packets: ";
              std::cin >> value_change;
              testing_map["num_udp_packets"] = value_change;
              break;
            
        case 6:
              
              std::cout<<"Please enter numrial value for new payload size:";
              std::cin >> value_change;
              testing_map["payload_sz"] = value_change;
             
              break;
        case 7:
           
              std::cout<<"Please enter new Server IP: ";
              std::cin >> value_change;
              testing_map["server_ip"] = value_change;
             
        case 8:
       
              std::cout<<"Please enter numrial value for new source port UDP:";
              std::cin >> value_change;
              testing_map["src_port_udp"] = value_change;
              break;
        case 9:
            
              std::cout<<"Please enter numrial value for new TCP Probing port:";
              std::cin >> value_change;
              testing_map["tcp_probing_port"] = value_change;
              break;
        case 10:
     
              std::cout<<"Please enter numrial value for UDP TTL:";
              std::cin >> value_change;
              testing_map["udp_ttl"] = value_change;
              break;
        default:
              std::cout << "ERROR INVALID CONFIGURATION ID";
              break;

      }

      std::cout <<"___________________________________________________\n";
      std::cout << "Testing Configurations: \n\n";
      print_map(testing_map);
      std::cout <<"___________________________________________________\n";

     std::cout << "Continue to update a test configuration [YES] or [RUN] for Simulation: ";
     std::cin >> update_menu;
     std::cout<<"\n";

    } 

    if(update_menu == "RUN"){
      std::cout <<"Simulation Test Results: \n";
      std::cout <<"-----------------------\n";
      std::cout << "\n";

      run_sim = true;
      return;
    }

  }
}

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
  print_menu(testingMap);
  AsciiTraceHelper ascii;
 
  if(run_sim){

   int dstPort = std::stoi(testingMap.at("dst_port_udp"), nullptr, 10);

   int payloadSize = std::stoi(testingMap.at("payload_sz"), nullptr, 10);

    NS_LOG_INFO("Setting nPackets");
   // uint32_t nPackets = std::stoi(testingMap.at("num_udp_packets"));
    uint32_t nPackets = 2;



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

    pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("TestingResults.tr"));


    PointToPointHelper pointToPoint2;


    pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
    pointToPoint2.SetChannelAttribute ("Delay", StringValue ("5ms"));
    NetDeviceContainer devices1;
    devices1 = pointToPoint2.Install (nodes.Get(1), nodes.Get(2));

    pointToPoint2.EnableAsciiAll ("TestingResults.tr");

    PointToPointHelper pointToPoint3;



    pointToPoint3.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
    pointToPoint3.SetChannelAttribute ("Delay", StringValue ("5ms"));
    NetDeviceContainer devices2;
    devices2 = pointToPoint3.Install (nodes.Get(2), nodes.Get(3));

    pointToPoint2.EnableAsciiAll ("TestingResults.tr");

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
  }
  return 0;
}

