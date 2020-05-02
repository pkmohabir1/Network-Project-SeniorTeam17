#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/csma-module.h"


#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <cctype>

bool run_sim = false;
bool log_flag = false;

bool is_digit(std::string s){
  for(unsigned int i = 0; i < s.length(); i++){
    if(isdigit(s[i]) == false){
      return false;
    }
  }
  return true;
}

bool parseConfig(std::map<std::string, std::string> &testing_map, std::string config_path) {

  std::ifstream inifile(config_path);

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
    return true;

  }else{
    std::cerr << "ERROR! Coud not open file ---> " << config_path<<"\n\nodes";
    return false;
  }
}

void print_map(std::map<std::string, std::string> &testing_map){
  std::map<std::string, std::string>::iterator itr;
  int i = 1;
  for(itr = testing_map.begin(); itr != testing_map.end(); ++itr){
    std::cout << i << ". " << itr->first << " = " << itr->second<< "\n";
    i++;
  }
}

void modify_testing_config(std::map<std::string, std::string> &testing_map, int configuration_id){

  std::string value_change;

  switch(configuration_id){

    case 1:
          std::cout<<"Please enter numrial value for new Destination port (TCP HEAD):";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new Destination port (TCP HEAD):";
            std::cin >> value_change;
          }
          testing_map["dst_port_tcp_head"] = value_change;
          break;
    case 2:
          std::cout<< "Please enter numrial value for new Destination port (TCP Tail):";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new Destination port (TCP Tail):";
            std::cin >> value_change;
          }
          testing_map["dst_port_tcp_tail"] = value_change;
          
          break;
    case 3:
          std::cout<<"Please enter numrial value for new Destination port (UDP):";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new Destination port (UDP):";
            std::cin >> value_change;
          }
          testing_map["dst_port_udp"] = value_change;
         
          break;
    case 4:
          std::cout<<"Please enter numrial value for new Intermeasurement Time:";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new Intermeasurement Time:";
            std::cin >> value_change;
          }
          testing_map["inter_measurement_time"]= value_change;
         
          break;
    case 5:
          std::cout<<"Please enter numrial value for number of UDP Packets: ";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for number of UDP Packets:";
            std::cin >> value_change;
          }
          testing_map["num_udp_packets"] = value_change;
          break;
        
    case 6:            
          std::cout<<"Please enter numrial value for new Payload size:";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new Payload size:";
            std::cin >> value_change;
          }
          testing_map["payload_sz"] = value_change;
         
          break;
    case 7:         
          std::cout<<"Please enter new Server IP: ";
          std::cin >> value_change;
          testing_map["server_ip"] = value_change;
         
    case 8:
          std::cout<<"Please enter numrial value for new source port (UDP):";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new source port (UDP):";
            std::cin >> value_change;
          }
          testing_map["src_port_udp"] = value_change;
          break;
    case 9:
          std::cout<<"Please enter numrial value for new TCP Probing port:";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new TCP Probing port:";
            std::cin >> value_change;
          }
          testing_map["tcp_probing_port"] = value_change;
          break;
    case 10:
          std::cout<<"Please enter numrial value for new UDP Time-to-live value:";
          std::cin >> value_change;
          while(is_digit(value_change) == false){
            std::cout<<"ERROR! INVALID INPUT ---> "<< value_change <<"\n";
            std::cout<<"Please enter numrial value for new UDP Time-to-live value:";
            std::cin >> value_change;
          }
          testing_map["udp_ttl"] = value_change;
          break;
    default:
          std::cout << "ERROR INVALID CONFIGURATION ID";
          break;
  }
}

void display_testing_file_option(std::map<std::string, std::string> &testing_map){
  std::cout << "Please be sure to save testing config file in ns-3-dev directory\n";
  std::cout << "Enter name of Testing config file. (Example ---> testing.ini): ";
  std::string config_path;
  std::cin >> config_path;
  config_path = "./" + config_path;

  bool parse_flag = parseConfig(testing_map, config_path);

  while(!parse_flag){
    std::cout << "Please make sure testing config file is saved in ns-3-dev directory\n";
    std::cout << "Enter name of Testing config file. (Example ---> testing.ini): \n";
    std::cin >> config_path;
    config_path = "./" + config_path;
    parse_flag = parseConfig(testing_map, config_path);
  }
  std::cout <<"_______________________________________________________________________\n";

}

void display_update_test_config(std::map<std::string, std::string> &testing_map){
  std::cout <<"_______________________________________________________________________\n";

  std::cout << " "<< "To update Testing Configuration(s) please enter\t\n";
  std::cout << " "<< "the *ID Number* of the configuration item\t\n";
  std::cout << " "<< "otherwise please enter RUN to run simulator\t\n";
  std::cout << " "<< "with current Testing configurations\t\n";
  std::cout <<"_______________________________________________________________________\n";

  std::cout << "Current Testing Configurations: \n\n";
  print_map(testing_map);
  
  std::cout << "\n";

  std::cout << "To update a test configuration [YES] or [RUN] for Simulation:";

  std::string update_menu;
  std::cin >> update_menu;
  std::cout << "\n";

  std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);

  while(update_menu != "yes" && update_menu != "run"){

    std::cout << "ERROR! INVALID ENTRY ---> "<< update_menu <<"\n";
    std::cout << "PLEASE enter [YES] to update Test configuration(s) or [RUN] for Simulation." << "\n";
    std::cout << "Enter [YES]/[RUN]: ";
    std::cin >> update_menu;
    std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);

  }

  while(update_menu == "yes" || update_menu == "run"){

    if(update_menu == "yes"){

      std::string id;
      std::cout << "Please enter the test configuration ID: ";
      std::cin >> id;

      int configuration_id = std::stoi(id);

      modify_testing_config(testing_map, configuration_id);
      std::cout <<"_______________________________________________________________________\n";

      std::cout << "Testing Configurations: \n\n";
      print_map(testing_map);
      std::cout <<"_______________________________________________________________________\n";
      std::cout << "Continue to update a test configuration [YES] or [RUN] for Simulation: ";
      std::cin >> update_menu;
      std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);
      while(update_menu != "yes" && update_menu != "run"){

        std::cout << "ERROR! INVALID ENTRY ---> "<< update_menu <<"\n";
        std::cout << "PLEASE enter [YES] to update Test configuration(s) or [RUN] for Simulation." << "\n";
        std::cout << "Enter [YES]/[RUN]: ";
        std::cin >> update_menu;
        std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);
      }
    } 

    if(update_menu == "run"){
      if(!log_flag){
        std::cout << "\n";
        std::cout <<"Simulation Test Results: \n";
        std::cout <<"---------------------------------------------------------------------\n";
        std::cout << "\n";
      }else{
        std::cout << "\n";
        std::cout <<"Simulation Test Results Located in files: \n";
        std::cout <<"---------------------------------------------------------------------\n";
        std::cout << "ns-3-dev/pointToPoint_sim_results.tr  -->" << " For Node 0 and Node 1\n";
        std::cout << "\n";
        std::cout << "ns-3-dev/pointToPoint2_sim_results.tr -->" << " For Node 1 and Node 2\n";
        std::cout << "\n";
        std::cout << "ns-3-dev/pointToPoint3_sim_results.tr -->" << " For Node 2 and Node 3\n";
        std::cout << "\n";
      }

      run_sim = true;
      return;
    }
  }
}

void display_log_file_option(){

  std::string log_file;

  std::cout << "\n";
  std::cout << "***The program allows offers to print Test Results onto an Ascii Trace file*** \n";
  std::cout << "\n";
  std::cout << "Please enter [Y] for test results to write to a .tr file or [n] for \n";
  std::cout << "test result in shell Environment [Y]/[n]: ";
  std::cin >> log_file;
  std::transform(log_file.begin(), log_file.end(),log_file.begin(), tolower);

  while(log_file != "y" && log_file != "n"){
    std::cout << "ERROR! INVALID INPUT ---> "<< log_file << "\n";
    std::cout << "Please enter [Y] for test results to write to a .tr file or [n] for \n";
    std::cout << "test result in shell Environment [Y]/[n]: ";
    std::cin >> log_file;
    std::transform(log_file.begin(), log_file.end(),log_file.begin(), tolower);
  }
  if(log_file == "y"){
    log_flag = true;
  }
  std::cout << "\n";
}


void print_menu(std::map<std::string, std::string> &testing_map){

  std::cout <<"********************************************************************\n";
  std::cout << "\t\tNetwork Compression Detection Portal\n";
  std::cout <<"********************************************************************\n";
  display_testing_file_option(testing_map);
  display_log_file_option();
  display_update_test_config(testing_map);
}



using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{

  std::map<std::string, std::string> testingMap;

  print_menu(testingMap);
  AsciiTraceHelper ascii;

 
  if(run_sim){

   int dstPort = std::stoi(testingMap.at("dst_port_udp"), nullptr, 10);

   int payloadSize = std::stoi(testingMap.at("payload_sz"), nullptr, 10);

   //int inter_measurement_time = std::stoi(testingMap.at("inter_measurement_time"), nullptr, 10);

    int inter_measurement_time =5;
    NS_LOG_INFO("Setting nPackets");

    //uint32_t nPackets = std::stoi(testingMap.at("num_udp_packets"));

    uint32_t nPackets = 9*2;

    Time::SetResolution (Time::NS);
    if(!log_flag){
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

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

    PointToPointHelper pointToPoint3;

    pointToPoint3.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
    pointToPoint3.SetChannelAttribute ("Delay", StringValue ("5ms"));
    NetDeviceContainer devices2;
    devices2 = pointToPoint3.Install (nodes.Get(2), nodes.Get(3));

    if(log_flag){
      pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("pointToPoint_sim_results.tr"));
      pointToPoint2.EnableAsciiAll (ascii.CreateFileStream ("pointToPoint2_sim_results.tr"));
      pointToPoint3.EnableAsciiAll (ascii.CreateFileStream ("pointToPoint3_sim_results.tr"));
    }
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
    echoServer.SetAttribute ("MaxPackets", UintegerValue (nPackets));

    ApplicationContainer serverApps = echoServer.Install (nodes.Get(3));
    serverApps.Start (Seconds (1.0));
    serverApps.Stop (Seconds (300));
    

    UdpEchoClientHelper echoClient (interfaces2.GetAddress (1), dstPort);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.0)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (payloadSize));
    echoClient.SetAttribute("inter_measurement_time", UintegerValue(inter_measurement_time));

    ApplicationContainer clientApps = echoClient.Install (nodes.Get(0));
    clientApps.Start(Seconds (2.0));
    clientApps.Stop(Seconds (55.0));
   


//____________________________end_____________________________________________
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds (320));

    NS_LOG_INFO ("Run Simulation.");

    Simulator::Run ();


    Simulator::Destroy ();

    NS_LOG_INFO ("Done.");
  }
  return 0;
}
