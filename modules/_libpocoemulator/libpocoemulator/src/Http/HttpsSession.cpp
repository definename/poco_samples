#include "pch.h"
#include "libpocoemulator/Http/HttpsSession.h"
#include "libpocoemulator/Http/HttpClient.h"

namespace libpocoemulator
{

HttpsSession::HttpsSession(const std::string& hostAddress, Poco::UInt16 portNumber)
{
	Poco::Net::initializeSSL();

	Poco::Net::Context::Ptr contextPtr = new Poco::Net::Context(
		Poco::Net::Context::CLIENT_USE, "", Poco::Net::Context::VerificationMode::VERIFY_NONE);

	httpsSession_ = new Poco::Net::HTTPSClientSession(hostAddress, portNumber, contextPtr);
}

HttpsSession::~HttpsSession()
{
	Poco::Net::uninitializeSSL();
}

std::string HttpsSession::GetHost() const
{
	return httpsSession_->getHost();
}

Poco::UInt16 HttpsSession::GetPort() const
{
	return httpsSession_->getPort();
}

Poco::JSON::Object::Ptr HttpsSession::GetAndJson(Poco::URI& uri)
{
	uri.setScheme("https");
	uri.setHost(GetHost());
	uri.setPort(GetPort());
	std::cout << Poco::Net::HTTPRequest::HTTP_GET << ": ";
	std::cout << uri.toString() << std::endl;
	return libpocoemulator::HttpClient::GetAndJson(httpsSession_, uri);
}

std::streamsize HttpsSession::PostAndDownload(
	Poco::URI& uri, Poco::JSON::Object::Ptr bodyJson, const Poco::Path& dest)
{
	uri.setScheme("https");
	uri.setHost(GetHost());
	uri.setPort(GetPort());
	std::cout << Poco::Net::HTTPRequest::HTTP_POST << ": ";
	std::cout << uri.toString() << std::endl;
	return libpocoemulator::HttpClient::PostAndDownload(httpsSession_, uri, bodyJson, dest);
}

Poco::JSON::Object::Ptr HttpsSession::PostAndJson(Poco::URI& uri, Poco::JSON::Object::Ptr bodyJson)
{
	uri.setScheme("https");
	uri.setHost(GetHost());
	uri.setPort(GetPort());
	std::cout << Poco::Net::HTTPRequest::HTTP_POST << ": ";
	std::cout << uri.toString() << std::endl;
	return libpocoemulator::HttpClient::PostAndJson(httpsSession_, uri, bodyJson);
}

} // namespace libpocoemulator