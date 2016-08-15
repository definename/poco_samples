#pragma once

class RedirectHandlerFactory
	: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	//! Constructor.
	RedirectHandlerFactory();
	//! Creates request handler.
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};
