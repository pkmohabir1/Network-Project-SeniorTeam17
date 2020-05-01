# Network Compression Detector Using NS3 Framework

## Introduction
This project aims to increase the security measures between network endpoints to ensure no tampering with the data occurs within the network topology. It does this by providing a tool to detect compression of user data using the C++ library Network-Simulator 3 (NS3). The end product allows information to be sent and received between two nodes and alerts the user of any compression that occurred within the network links. The program simulates a variety of different network conditions to ensure robustness when used in real world situations.

## Requirements
* **OS:** Standard Linux distribution (developed/tested on Ubuntu 18.04 LTS)
* **Build System:** GCC configured for C++ and a clean installation of ns-3.30.1 which can be [downloaded from here](https://www.nsnam.org/releases/ns-allinone-3.30.1.tar.bz2)

## To Build
1. [Download and install NS3 according to the guide found here](https://www.nsnam.org/docs/release/3.30/tutorial/html/getting-started.html)
2. Clone the Git repository into the ````ns-3.30.1```` directory
3. Run ````./install.sh```` located in the top-level repo directory
4. Rebuild NS3 by going bck to the ````ns-3.30.1```` directory and running ````./waf````

## To Run
1. Run ````./waf --run scratch/networkComp0```` from the ````ns-3.30.1```` directory


## To Configure
### Using Configuration File
The initial simulation parameters are configured via an INI file pointed to by the user specifying the path (relative to the top-level NS3 directory) on startup. Each line in the file specifies a single parameter in the format ```param_name=value```. All of the possible parameters are listed below:
 * ```server_ip```: Server IP address where packet trains will be sent
 * ```src_port_udp```: Source port for UDP packet trains
 * ```dst_port_udp```: Destination port for UDP packet trains
 * ```dst_port_tcp_head```: Destination port for head TCP SYN packet 
 * ```dst_port_tcp_tail```: Destination port for tail TCP SYN packet 
 * ```tcp_probing_port```: Port to use for pre/post-probing TCP connection
 * ```payload_sz```: Payload size for each UDP packet (defaults to 1000 bytes if not specified)
 * ```inter_measurement_time```: Time to wait between sending high and low-entropy UDP packet trains (defaults to 15 seconds if not specified)
 * ```num_udp_packets```: Number of UDP packets in each train (defaults to 6000 packets if not specified)
 * ```udp_ttl```: TTL value for each UDP packet (defaults to 255 if not specified)
  
   **NOTE:** If you are modifying the ````testing.ini```` file you must either make sure you are editing the version in the top-level NS3 directory or running ```install.sh``` after modifying the version in the ```team17``` directory.

### Using Program Menu
Individual parameters can be changed via the menu interface within the program before running the simulation. The parameters and values work the same way as the INI file method.

### Output and Logging
The user is given the option to enable or disable console and trace file logging before running the simulation. If console logging is enabled the logfile locations will be given in the terminal after the simulation finishes running.


### Maintainers
* Graham Hendry (gphendry) - gphendry@dons.usfca.edu
* Ghufran Latif (glatif1) - glatif@dons.usfca.edu
* Porfirio Mohabir (pkmohabir) - pkmohabir@dons.usfca.edu