#pragma once

namespace libpocoemulator
{

class HttpClient
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	HttpClient() = default;
	//! Destructor.
	~HttpClient() = default;

	//
	// Public types
	//
public:
	//! Http session pointer type.
	using HttpSessionPtr = Poco::SharedPtr<Poco::Net::HTTPClientSession>;

	//
	// Public interface.
	//
public:
	//! Sends request to given session.
	static std::istream& Get(
		HttpSessionPtr httpSession,
		const Poco::URI& uri,
		Poco::Net::HTTPResponse& response);
	//! Sends Get request to the given session.
	static Poco::JSON::Object::Ptr GetAndJson(HttpSessionPtr httpSession, const Poco::URI& uri);

	//! Sends request to given session.
	static std::istream& Post(
		HttpSessionPtr httpSession,
		const Poco::URI& uri,
		Poco::JSON::Object::Ptr bodyJson,
		Poco::Net::HTTPResponse& response);
	//! Sends post request and downloads data to file.
	static std::streamsize PostAndDownload(
		HttpSessionPtr session,
		const Poco::URI& uri,
		Poco::JSON::Object::Ptr bodyJson,
		const Poco::Path& dest);
	//! Sends post request and returns json response.
	static Poco::JSON::Object::Ptr PostAndJson(
		HttpSessionPtr session,
		Poco::URI& uri,
		Poco::JSON::Object::Ptr bodyJson);

private:
	//! Downloads data to the given destination path.
	static std::streamsize Download(std::istream& src, const Poco::Path& dest);
};

} // namespace libpocoemulator