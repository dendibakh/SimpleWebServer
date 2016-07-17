#pragma once

#include <boost/asio.hpp>
#include <string>

void startServer(const boost::asio::ip::address addr, int port, const std::string& homeDir);
