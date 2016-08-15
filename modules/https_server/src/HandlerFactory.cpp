#include "pch.h"
#include "HandlerFactory.h"
#include "RequestHandler.h"

HandlerFactory::HandlerFactory(const std::string& format)
	: format_(format)
{ }

Poco::Net::HTTPRequestHandler* HandlerFactory::createRequestHandler(
	const Poco::Net::HTTPServerRequest& request)
{
	return new RequestHandler(format_);
}