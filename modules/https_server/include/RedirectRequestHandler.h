#pragma once

class RedirectRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	//! Constructor.
	RedirectRequestHandler();
	//! Handles request.
	void handleRequest(
		Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	//! Redirection URL.
	const std::string url_;
};
