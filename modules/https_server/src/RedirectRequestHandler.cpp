#include "pch.h"
#include "RedirectRequestHandler.h"

RedirectRequestHandler::RedirectRequestHandler()
	: url_("https://127.0.0.1:9443")
{ }

void RedirectRequestHandler::handleRequest(
	Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
	resp.redirect(url_, Poco::Net::HTTPResponse::HTTP_FOUND);
}
