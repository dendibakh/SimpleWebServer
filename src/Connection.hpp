#pragma once

#include <boost/asio.hpp>
#include <array>
#include "reply.hpp"

class Connection
{
public:
	Connection(boost::asio::ip::tcp::socket&& socket);

	void doAsyncRead();
	void doAsyncReply();
private:
	boost::asio::ip::tcp::socket socket;
	std::array<char, 8192> buffer;
	reply rep;
};
