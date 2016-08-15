#pragma once

class RequestHandler
	: public Poco::Net::HTTPRequestHandler
{
public:
	//! Constructor.
	RequestHandler(const std::string& format);
	//! Handles request.
	void handleRequest(
		Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	//! Time format string.
	std::string format_;
};
