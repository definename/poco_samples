#include "pch.h"
#include "libpocoemulator/Http/HttpSession.h"

namespace libpocoemulator
{

HttpSession::HttpSession(const std::string& hostAddress, Poco::UInt16 portNumber)
	: address_(hostAddress, portNumber)
	, httpSession_(new Poco::Net::HTTPClientSession(address_.host().toString(), address_.port()))
{
}

} // namespace libpocoemulator
