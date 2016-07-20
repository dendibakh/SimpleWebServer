#pragma once

#include <boost/asio.hpp>
#include <array>
#include "reply.hpp"
#include "RequestParser.hpp"
#include "RequestHandler.hpp"
#include "request.hpp"

class Connection
{
public:
	Connection(boost::asio::ip::tcp::socket&& socket, const std::string& homeDir);

	void doAsyncRead();
	void doAsyncReply(reply rep);
private:
	boost::asio::ip::tcp::socket socket;
	std::string homeDir;
	std::array<char, 8192> buffer;
	request_parser parser;
	request_handler req_handler;
	request req;
};
