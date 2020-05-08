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
#include <limits>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <cctype>

bool run_sim = false;
bool log_flag = false;
bool run_tests = false;
bool debug = false;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

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
    std::cerr << "ERROR! Coud not open file ---> " << config_path<<"\n";
    return false;
  }
}

void print_map(std::map<std::string, std::string> &testing_map){
  std::map<std::string, std::string>::iterator itr;
  int i = 1;
  for(itr = testing_map.begin(); itr != testing_map.end(); ++itr){
    std::string param;
    if (itr->first == "dst_port_tcp_head") {
      param = "TCP Head Packet Destination Port";
    } else if (itr->first == "dst_port_tcp_tail") {
      param = "TCP Tail Packet Destination Port";
    } else if (itr->first == "dst_port_udp") {
      param = "UDP Destination Port";
    } else if (itr->first == "inter_measurement_time") {
      param = "Inter-Measurment Time";
    } else if (itr->first == "num_udp_packets") {
      param = "Number of UDP Packets";
    } else if (itr->first == "payload_sz") {
      param = "Payload Size";
    } else if (itr->first == "server_ip") {
      param = "Server IP Address";
    } else if (itr->first == "src_port_udp") {
      param = "UDP Source Port";
    } else if (itr->first == "tcp_probing_port") {
      param = "Pre/Post-Probing TCP Port";
    } else if (itr->first == "udp_ttl") {
      param = "UDP TTL";
    } 

    std::cout << i << ". " << param << " = " << itr->second<< "\n";
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
	  break;
         
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
  std::cout << "Enter name of Testing config file. Press ENTER to use default config file. (Example ---> testing.ini): ";
  std::string config_path;
  getline(std::cin, config_path);
  if (config_path.empty()) {
    config_path = "./testing.ini";
  } else {
    config_path = "./" + config_path;
  }

  bool parse_flag = parseConfig(testing_map, config_path);

  while(!parse_flag){
    std::cout << "Please make sure testing config file is saved in ns-3-dev directory\n";
    std::cout << "Enter name of Testing config file. (Example ---> testing.ini): ";
    getline(std::cin, config_path);
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

  std::cout << "To update a test configuration enter [YES], [RUN] for Simulation, [TEST] for Test Cases\n";
  std::cout << "Enter [YES]/[RUN]/[TEST]: ";

  std::string update_menu;
  std::cin >> update_menu;
  std::cout << "\n";

  std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);

  while(update_menu != "yes" && update_menu != "run" && update_menu != "test"){

    std::cout << "ERROR! INVALID ENTRY ---> "<< update_menu <<"\n";
      std::cout << "To update a test configuration enter [YES], [RUN] for Simulation, [TEST] for Test Cases\n";
    std::cout << "Enter [YES]/[RUN]/[TEST]: ";
    std::cin >> update_menu;
    std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);

  }

  while(update_menu == "yes" || update_menu == "run" || update_menu == "test"){

    if(update_menu == "yes"){

      std::string id;
      std::cout << "Please enter the test configuration ID: ";
      std::cin >> id;

      int configuration_id = std::stoi(id);

      modify_testing_config(testing_map, configuration_id);
      std::cout <<"_______________________________________________________________________\n";

      std::cout << "Testing Configurations: \n\n";
      print_map(testing_map);
      std::cout << "\n";
      std::cout << "To update a test configuration enter [YES], [RUN] for Simulation, [TEST] for Test Cases\n";
      std::cout << "Enter [YES]/[RUN]/[TEST]: ";
      std::cin >> update_menu;
      std::cout << "\n";      
      std::transform(update_menu.begin(), update_menu.end(),update_menu.begin(), tolower);
      while(update_menu != "yes" && update_menu != "run" && update_menu != "test"){

        std::cout << "ERROR! INVALID ENTRY ---> "<< update_menu <<"\n";
        std::cout << "PLEASE enter [YES] to update Test configuration(s) or [RUN] for Simulation [TEST] for Test Cases" << "\n";
        std::cout << "Enter [YES]/[RUN]/[TEST]: ";
        std::cin >> update_menu;
	      std::cout << "\n";	
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

    if (update_menu == "test") {
      run_tests = true;
      NS_LOG_INFO("Running tests...");
      return;
    }
    
  }
}

void display_log_file_option(){


  std::string log_file;

  std::cout << "\n";
  std::cout << "***The program allows users to print Test Results onto an Ascii Trace file*** \n";
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

void display_debug_info() {
  debug = false;
  std::string full_logging;
  std::cout << "Please enter [Y] for full packet info in terminal or [n] for just results\n";
  std::cout << "Full Logging in Shell Environment [Y]/[n]: ";
  std::cin >> full_logging;
  std::transform(full_logging.begin(), full_logging.end(),full_logging.begin(), tolower);

  while(full_logging != "y" && full_logging != "n"){
    std::cout << "ERROR! INVALID INPUT ---> "<< full_logging << "\n";
    std::cout << "Please enter [Y] for full packet info in terminal or [n] for just results\n";
    std::cout << "Full Logging in Shell Environment [Y]/[n]: ";
    std::cin >> full_logging;
    std::transform(full_logging.begin(), full_logging.end(),full_logging.begin(), tolower);
  }
  if(full_logging == "y"){
    debug = true;
  }
  std::cout << "\n";
}


void print_menu(std::map<std::string, std::string> &testing_map){

  std::cout <<"********************************************************************\n";
  std::cout << "\t\tNetwork Compression Detection Portal\n";
  std::cout <<"********************************************************************\n";
  display_testing_file_option(testing_map);
  display_log_file_option();
  display_debug_info();
  display_update_test_config(testing_map);

}

void run_simulator(std::map<std::string, std::string> &testingMap, bool compression, bool long_distance) {
  using namespace ns3;
  std::string distance_val;
  std::string short_distance_str = "5ms";
  std::string long_distance_str = "200ms";

  if ((compression == false) && (long_distance == false)) {
    NS_LOG_INFO("Running No Compression and Short Distance...");
    distance_val = short_distance_str;
  }
  if ((compression == false) && (long_distance == true)) {
    NS_LOG_INFO("Running No Compression and Long Distance...");
    distance_val = long_distance_str;
  }
  if ((compression == true) && (long_distance == false)) {
    NS_LOG_INFO("Running With Compression and Short Distance...");
    distance_val = short_distance_str;
  }
  if ((compression == true) && (long_distance == true)) {
    NS_LOG_INFO("Running With Compression and Long Distance...");
    distance_val = long_distance_str;
  }

   AsciiTraceHelper ascii;
   int dstPort = std::stoi(testingMap.at("dst_port_udp"), nullptr, 10);

   int payloadSize = std::stoi(testingMap.at("payload_sz"), nullptr, 10);

   int inter_measurement_time = std::stoi(testingMap.at("inter_measurement_time"), nullptr, 10);

    uint32_t nPackets = std::stoi(testingMap.at("num_udp_packets")) * 2;

    LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

     NS_LOG_INFO ("Creating nodes...");
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
    pointToPoint2.SetChannelAttribute ("Delay", StringValue (distance_val));
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

    Ipv4Address serverIP = Ipv4Address(testingMap.at("server_ip").c_str());

    Ipv4AddressHelper address;

    address.SetBase ("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces0 = address.Assign (devices);

    address.SetBase ("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces1 = address.Assign (devices1);

   
    address.SetBase (serverIP, "255.255.255.0");
    Ipv4InterfaceContainer interfaces2 = address.Assign (devices2);

    UdpEchoServerHelper echoServer (dstPort);
    echoServer.SetAttribute ("MaxPackets", UintegerValue (nPackets));
    echoServer.SetAttribute("full_logging", UintegerValue(debug));

    ApplicationContainer serverApps = echoServer.Install (nodes.Get(3));
    serverApps.Start (Seconds (1.0));
    serverApps.Stop (Seconds (300));
    

    UdpEchoClientHelper echoClient (interfaces2.GetAddress (1), dstPort);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.0)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (payloadSize));
    echoClient.SetAttribute("inter_measurement_time", UintegerValue(inter_measurement_time));
    echoClient.SetAttribute("full_logging", UintegerValue(debug));
    echoClient.SetAttribute("comp_link", UintegerValue(compression));

    ApplicationContainer clientApps = echoClient.Install (nodes.Get(0));
    clientApps.Start(Seconds (2.0));
    clientApps.Stop(Seconds (55.0));
   
//____________________________end_____________________________________________
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds (320));

    NS_LOG_INFO ("Starting Simulation...");

    NS_LOG_INFO("Sending Low-Entropy Packet Train...");

    Simulator::Run ();


    Simulator::Destroy ();

    NS_LOG_INFO ("Simulation Finished.\n");
}

bool rerun_sim() {
  std::cin.clear();
  std::cin.ignore(INT_MAX, '\n');
  fflush(stdin);
  bool rerun = false;
  std::string rerun_sim;
  std::cout << "Please enter [Y] to run another simulation or [n] to exit\n";
  std::cout << "Run another simulation [Y]/[n]: ";
  getline(std::cin, rerun_sim);
  std::transform(rerun_sim.begin(), rerun_sim.end(),rerun_sim.begin(), tolower);

  while(rerun_sim != "y" && rerun_sim != "n"){
    std::cout << "ERROR! INVALID INPUT ---> "<< rerun_sim << "\n";
    std::cout << "Please enter [Y] to run another simulation or [n] to exit\n";
    std::cout << "Run another simulation [Y]/[n]: ";
    getline(std::cin, rerun_sim);
    std::transform(rerun_sim.begin(), rerun_sim.end(),rerun_sim.begin(), tolower);
  }
  if(rerun_sim == "y"){
    rerun = true;
  } else {
    rerun = false;
  }
  std::cout << "\n";
  return rerun;
}



using namespace ns3;

int
main (int argc, char *argv[])
{
  LogComponentEnable ("FirstScriptExample", LOG_LEVEL_INFO);

  std::map<std::string, std::string> testingMap;

  Time::SetResolution (Time::NS);

  bool rerun = true;
  while (rerun) {
    print_menu(testingMap);
  
    if((run_sim == true) && (run_tests == false)){
      run_simulator(testingMap, false, false);
    }

    // Four test cases
    if ((run_sim == false) && (run_tests == true)) {
      run_simulator(testingMap, false, false);
      run_simulator(testingMap, false, true);
      run_simulator(testingMap, true, false);
      run_simulator(testingMap, true, true);
    }
    rerun = rerun_sim();
    run_sim = false;
    run_tests = false;
  }
  return 0;
}
