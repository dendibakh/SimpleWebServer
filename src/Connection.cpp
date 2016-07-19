#include "Connection.hpp"
#include <iostream>

Connection::Connection(boost::asio::ip::tcp::socket&& socket) : socket(std::move(socket))
{

}

void Connection::doAsyncRead()
{
	socket.async_read_some(boost::asio::buffer(buffer),
	      [this](boost::system::error_code ec, std::size_t bytes_transferred)
	      {
	        if (!ec)
	        {
	          std::cout << "Received http request: " << buffer.data() << "\n";
	          rep = reply::stock_reply(reply::ok);
	          doAsyncReply();
	          /*request_parser::result_type result;
	          std::tie(result, std::ignore) = request_parser_.parse(
	              request_, buffer_.data(), buffer_.data() + bytes_transferred);

	          if (result == request_parser::good)
	          {
	            request_handler_.handle_request(request_, reply_);
	            do_write();
	          }
	          else if (result == request_parser::bad)
	          {
	            reply_ = reply::stock_reply(reply::bad_request);
	            do_write();
	          }
	          else
	          {
	            do_read();
	          }*/
	        }
	        else if (ec != boost::asio::error::operation_aborted)
	        {
	          //connection_manager_.stop(shared_from_this());
	        }
	      });
}

void Connection::doAsyncReply()
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
