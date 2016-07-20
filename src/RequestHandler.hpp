#pragma once

#include <string>
#include <http_parser.h>

class RequestHandler
{
	struct parsedData
	{
		std::string path;
	};
public:
	RequestHandler();
	bool parse(const std::string& request);
private:
	parsedData data;
	http_parser parser;
	http_parser_settings settings;
};
