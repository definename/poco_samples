#include "pch.h"
#include "RedirectHandlerFactory.h"
#include "RedirectRequestHandler.h"

RedirectHandlerFactory::RedirectHandlerFactory()
{ }

Poco::Net::HTTPRequestHandler* RedirectHandlerFactory::createRequestHandler(
	const Poco::Net::HTTPServerRequest& request)
{
	return new RedirectRequestHandler();
}