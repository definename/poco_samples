#pragma once

class HandlerFactory
	: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	//! Constructor.
	HandlerFactory(const std::string& format);
	//! Creates request handler.
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
	//! Time format.
	std::string format_;
};
