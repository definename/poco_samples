#include "pch.h"
#include "libpocoemulator/Http/HttpClient.h"

//scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]

namespace libpocoemulator
{

std::istream& HttpClient::Post(
	HttpSessionPtr httpSession,
	const Poco::URI& uri,
	Poco::JSON::Object::Ptr bodyJson,
	Poco::Net::HTTPResponse& response)
{
	if (!httpSession) {
		throw(std::runtime_error("Invalid http session pointer"));
	}

	std::string path(uri.getPathAndQuery());
	if (path.empty()) {
		path.append("/");
	}

	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPRequest::HTTP_1_1);

	std::ostringstream bodyStream;
	bodyJson->stringify(bodyStream);
	std::string bodyStr = bodyStream.str();
	req.setContentLength(bodyStr.size());
	req.setContentType("application/json");
	httpSession->sendRequest(req) << bodyStr;

	return httpSession->receiveResponse(response);
}

std::streamsize HttpClient::PostAndDownload(
	HttpSessionPtr session,
	const Poco::URI& uri,
	Poco::JSON::Object::Ptr bodyJson,
	const Poco::Path& dest)
{
	Poco::Net::HTTPResponse response;
	std::istream& rs = HttpClient::Post(session, uri, bodyJson, response);
	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
	if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK) {
		return HttpClient::Download(rs, dest);
	}
	return std::streamsize(0);
}

Poco::JSON::Object::Ptr HttpClient::PostAndJson(
	HttpSessionPtr session, Poco::URI& uri, Poco::JSON::Object::Ptr bodyJson)
{
	Poco::Net::HTTPResponse response;
	std::istream& rs = HttpClient::Post(session, uri, bodyJson, response);
	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
	if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
	{
		std::string json;
		Poco::StreamCopier::copyToString(rs, json);
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var var = parser.parse(json);

		return var.extract<Poco::JSON::Object::Ptr>();
	}
	return Poco::JSON::Object::Ptr();
}

std::istream& HttpClient::Get(
	HttpSessionPtr httpSession,
	const Poco::URI& uri,
	Poco::Net::HTTPResponse& response)
{
	if (!httpSession) {
		throw(std::runtime_error("Invalid http session pointer"));
	}

	std::string path(uri.getPathAndQuery());
	if (path.empty()) {
		path.append("/");
	}

	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPRequest::HTTP_1_1);
	httpSession->sendRequest(req);
	return httpSession->receiveResponse(response);
}

Poco::JSON::Object::Ptr HttpClient::GetAndJson(HttpSessionPtr session, const Poco::URI& uri)
{
	Poco::Net::HTTPResponse response;
	std::istream& rs = HttpClient::Get(session, uri, response);
	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
	if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
	{
		std::string json;
		Poco::StreamCopier::copyToString(rs, json);
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var var = parser.parse(json);

		return var.extract<Poco::JSON::Object::Ptr>();
	}
	return Poco::JSON::Object::Ptr();
}

std::streamsize HttpClient::Download(std::istream& src, const Poco::Path& dest)
{
	Poco::FileOutputStream fileStream(dest.toString(Poco::Path::PATH_WINDOWS), std::ios::binary);
	return Poco::StreamCopier::copyStreamUnbuffered(src, fileStream);
}

} // namespace libpocoemulator