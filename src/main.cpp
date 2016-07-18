#include <boost/program_options.hpp>

#include <iostream>
#include <boost/filesystem.hpp>

#include "server.hpp"
#include "daemonize.h"

using namespace boost::asio;
using namespace boost::program_options;
using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
   try 
   {
       int port = 0;
       options_description desc("Allowed options");
       desc.add_options()
	   ("help", "produce help message")
           ("h", value<std::string>(), "IP address of the server")
           ("p", value<int>(&port)->default_value(80), "Port of the server")
           ("d", value<std::string>(), "Home directory for the server");

       variables_map vm;
       store(command_line_parser(argc, argv).options(desc).run(), vm);
       notify(vm);
   
       if (vm.count("help")) 
       {
           cout << "Usage: options_description [options]" << endl << desc;
           return 0;
       }

       if (!vm.count("h"))
       {
           cout << "Please specify IP address." << endl << desc;
           return 1;
       }

       if (!vm.count("p"))
       {
           cout << "Please specify port." << endl << desc;
           return 1;
       }

       if (!vm.count("d"))
       {
           cout << "Please specify home directory." << endl << desc;
           return 1;
       }

       if (port < 0 || port > 0xFFFF)
       {
           cout << "Please specify correct port." << endl << desc;
           return 1;
       }

       ip::address IP = ip::address::from_string(vm["h"].as< string >());

       if (!IP.is_v4())
       {
           cout << "Please specify correct IP address v4." << endl << desc;
           return 1;
       }

       std::string homeDir = vm["d"].as< string >();
       if (!is_directory(homeDir))
       {
           cout << "Home directory for the server do not exists." << endl << desc;
           return 1;
       }

       //if (daemonize())
           startServer(IP, port, homeDir);
   }                                                                    
   catch(std::exception& e)
   {
       cout << e.what() << endl;
       return 1;
   }
   return 0;
}

