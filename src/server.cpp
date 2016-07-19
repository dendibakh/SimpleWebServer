#include "server.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

#include "http_parser.h"

using namespace boost::asio;
using namespace boost::filesystem;

class HttpServer
{
public:
	HttpServer(const ip::tcp::endpoint& ep, std::string homeDir);
	void start();
	void doAsyncAccept();
	void doAsyncRead();

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
	std::cout << "Accepting new connection.\n";
	acceptor.async_accept(socket,
		   [this](boost::system::error_code ec)
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
				 std::thread th1([this](){doAsyncRead();});
				 th1.detach();
				 //connection_manager_.start(std::make_shared<connection>(
				   //std::move(socket), connection_manager_, request_handler_));
			 }

			 // spawn a new async acception
			 doAsyncAccept();
		   });
}

void HttpServer::doAsyncRead()
{
	std::cout << "    Start request handling.\n";
	std::this_thread::sleep_for (std::chrono::seconds(20));
	std::cout << "    Finished request handling.\n";
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
