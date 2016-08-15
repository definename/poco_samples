#pragma once

namespace libpocoemulator
{

class HttpSession
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	HttpSession(const std::string& hostAddress, Poco::UInt16 portNumber);
	//! Destructor.
	~HttpSession() = default;

	//
	// Public types.
	//
public:
	//! Http session smart pointer type.
	using HTTPClientSessionPtr = Poco::SharedPtr<Poco::Net::HTTPClientSession>;

	//
	// Private interface.
	//
private:
	//! Remote endpoint.
	const Poco::Net::SocketAddress address_;
	//! HTTP session.
	HTTPClientSessionPtr httpSession_;
};

} // namespace libpocoemulator