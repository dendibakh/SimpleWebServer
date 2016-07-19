#include "server.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

#include "http_parser.h"

using namespace boost::asio;
using namespace boost::filesystem;

class HttpServer
{
public:
	HttpServer(const ip::tcp::endpoint& ep, std::string homeDir);
	void start();
	void doAsyncAccept();

	HttpServer(const HttpServer& rhs) = delete;
	HttpServer& operator=(const HttpServer& rhs) = delete;
private:
	boost::asio::io_service io;
	ip::tcp::acceptor acceptor;
	ip::tcp::socket socket;
	const std::string homeDir;
};

HttpServer::HttpServer(const ip::tcp::endpoint& ep, std::string homeDir) :
		acceptor(io, ep),
		socket(io),
		homeDir(std::move(homeDir))
{
	doAsyncAccept();
}

void HttpServer::start()
{
	io.run();
}

void HttpServer::doAsyncAccept()
{
	acceptor.async_accept(socket,
		   [&](boost::system::error_code ec)
		   {
			 // Check whether the server was stopped by a signal before this
			 // completion handler had a chance to run.
			 if (!acceptor.is_open())
			 {
			   return;
			 }

			 if (!ec)
			 {
				 std::cout << "New connection established.\n";
				 ip::tcp::socket newSock = std::move(socket);
				 //connection_manager_.start(std::make_shared<connection>(
				   //std::move(socket), connection_manager_, request_handler_));
			 }

			 // spawn a new async acception
			 doAsyncAccept();
		   });
}

void startServer(const boost::asio::ip::address addr, int port, const std::string& homeDir)
{
	try 
	{
	    std::cout << "Starting server...\n";
	    HttpServer server(ip::tcp::endpoint(addr, port), homeDir);
	    server.start();
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}
