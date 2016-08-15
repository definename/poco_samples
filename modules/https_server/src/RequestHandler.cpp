#include "pch.h"
#include "RequestHandler.h"

RequestHandler::RequestHandler(const std::string& format)
	: format_(format)
{ }

void RequestHandler::handleRequest(
	Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
	std::cout << "Request from " + req.clientAddress().toString() << std::endl;

	Poco::Net::SecureStreamSocket socket = static_cast<Poco::Net::HTTPServerRequestImpl&>(req).socket();
	if (socket.havePeerCertificate())
	{
		Poco::Net::X509Certificate cert = socket.peerCertificate();
		std::cout << "Client certificate: " + cert.subjectName() << std::endl;
	}
	else
	{
		std::cout << "No client certificate available" << std::endl;
	}

	Poco::Timestamp now;
	std::string dt(Poco::DateTimeFormatter::format(now, format_));

	resp.setChunkedTransferEncoding(true);
	resp.setContentType("text/html");

	std::ostream& ostr = resp.send();
	ostr << "<html><head><title>HTTPTimeServer powered by POCO C++ Libraries</title>";
	ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
	ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
	ostr << dt;
	ostr << "</p></body></html>";

	//! Checks request body.
	std::string res;
	std::istream& rs = req.stream();
	std::stringbuf buf;
	rs >> &buf;
	if (buf.str().empty())
		std::cout << "Empty request body" << std::endl;
	else
		std::cout << buf.str() << std::endl;
}
