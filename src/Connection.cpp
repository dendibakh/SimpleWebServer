#include "Connection.hpp"
#include "RequestHandler.hpp"
#include <iostream>

Connection::Connection(boost::asio::ip::tcp::socket&& socket, const std::string& homeDir)
	: socket(std::move(socket)), homeDir(homeDir), req_handler(homeDir)
{

}

void Connection::doAsyncRead()
{
	socket.async_read_some(boost::asio::buffer(buffer),
	      [this](boost::system::error_code ec, std::size_t bytes_transferred)
	      {
	        if (!ec)
	        {
	          request_parser::result_type result;
	          std::tie(result, std::ignore) = parser.parse(req, buffer.data(), buffer.data() + bytes_transferred);

	          if (result == request_parser::good)
	          {
	        	reply rep;
	        	req_handler.handle_request(req, rep);
	            doAsyncReply(rep);
	          }
	          else if (result == request_parser::bad)
	          {
	            doAsyncReply(reply::stock_reply(reply::not_found));
	          }
	          else
	          {
	        	  doAsyncRead();
	          }
	        }
	        else if (ec != boost::asio::error::operation_aborted)
	        {
	          //connection_manager_.stop(shared_from_this());
	        }
	      });
}

void Connection::doAsyncReply(reply rep)
{
  boost::asio::async_write(socket, rep.to_buffers(),
      [this](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
        	std::cout << "Http request was processed.\n";
        }

        if (ec != boost::asio::error::operation_aborted)
        {
          //connection_manager_.stop(shared_from_this());
        }
      });
}
