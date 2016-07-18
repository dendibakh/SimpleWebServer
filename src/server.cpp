#include "server.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

#include "http_parser.h"

using namespace boost::asio;
using namespace boost::filesystem;

void startServer(const boost::asio::ip::address addr, int port, const std::string& homeDir)
{
	try 
	{
	      std::cout << "Starting server...\n";
	      boost::asio::io_service io;
	      ip::tcp::acceptor acceptor (io, ip::tcp::endpoint(addr, port));

	      ip::tcp::socket socket (io);
	      acceptor.accept(socket);

	      std::cout << "Connection established.\n";

	      while (true) 
	      {
		 boost::asio::streambuf buffer;
		 size_t len = read_until(socket, buffer, '\0');

		 if (len)
		 {
			std::cout << "Received message:\n";
		 }
	      }
	    }
	    catch (std::exception & e) 
	    {
	      std::cerr << e.what() << std::endl;
	}
}
