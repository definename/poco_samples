#pragma once

namespace libpocoemulator
{

class HttpsSession
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	HttpsSession(const std::string& hostAddress, Poco::UInt16 portNumber);
	//! Destructor.
	virtual ~HttpsSession();

	//
	// Public interface.
	//
public:
	//! Sends post request and downloads content.
	std::streamsize PostAndDownload(Poco::URI& uri, Poco::JSON::Object::Ptr bodyJson, const Poco::Path& dest);
	//! Sends post request and returns json response.
	Poco::JSON::Object::Ptr PostAndJson(Poco::URI& uri, Poco::JSON::Object::Ptr bodyJson);
	//! Sends get reqeust and returns json response.
	Poco::JSON::Object::Ptr GetAndJson(Poco::URI& uri);


	//
	// Public interface.
	//
public:
	//! Returns host address.
	std::string GetHost() const;
	//! Returns port.
	Poco::UInt16 GetPort() const;

	//
	// Protected types.
	//
protected:
	//! Https client session smart pointer type.
	using HttpsClientSessionPtr = Poco::SharedPtr<Poco::Net::HTTPSClientSession>;

	//
	// Protected data members.
	//
protected:
	//! HTTPS session.
	HttpsClientSessionPtr httpsSession_;
};

} // namespace libpocoemulator
