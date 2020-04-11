#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
//#include <algorithm.h>
//#include <iterator.h>

int main (){

	std::map<std::string, std::string> testing_map;

	std::ifstream inifile("testing.ini");

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


