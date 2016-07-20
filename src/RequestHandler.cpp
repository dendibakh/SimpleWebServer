#include "RequestHandler.hpp"
#include <iostream>

int header_field_callback(http_parser* parser, const char *at, size_t length)
{
	//std::cout << "header" << std::string(at, length) << "\n";
	return 0;
}

int url_callback(http_parser* parser, const char *at, size_t length)
{
	//std::cout << "url" << std::string(at, length) << "\n";
	return 0;
}

RequestHandler::RequestHandler()
{
	settings.on_url = url_callback;
	settings.on_header_field = header_field_callback;

	http_parser_init(&parser, HTTP_REQUEST);

	parser.data = &data;
}

bool RequestHandler::parse(const std::string& request)
{
	std::cout << "starting parsing\n";
	auto nparsed = http_parser_execute(&parser, &settings, request.data(), request.size());
	std::cout << "finished parsing\n";
	if (parser.upgrade)
	{
	  /* protocol upgrade is not supported*/
		return false;
	}
	else if (nparsed != request.size())
	{
		/* Handle error. Usually just close the connection. */
		return false;
	}

	return true;
}

