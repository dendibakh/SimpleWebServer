#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "server.hpp"
#include "http_parser.h"
#include "Connection.hpp"

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
	std::vector<std::unique_ptr<Connection>> connections;
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
	std::cout << "Accepting new connection.\n";
	acceptor.async_accept(socket,
		   [this](boost::system::error_code ec)
		   {
			 // Check whether the server was stopped by a signal before this
			 // completion handler had a chance to run.
			 if (!acceptor.is_open())
			   return;

			 if (!ec)
			 {
				 std::cout << "New connection established.\n";
				 connections.push_back(std::make_unique<Connection>(std::move(socket), homeDir));
				 connections.back()->doAsyncRead();
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
