#include "pch.h"
#include "HTTPSServer.h"
#include "HandlerFactory.h"
#include "RedirectHandlerFactory.h"


HTTPSServer::HTTPSServer()
	: helpRequested_(false)
	, privateKeyName_("server.key")
	, certificateName_("server.crt")
{
	Poco::Net::initializeSSL();
}

HTTPSServer::~HTTPSServer()
{
	Poco::Net::uninitializeSSL();
}

void HTTPSServer::initialize(Application& self)
{
	Poco::Util::ServerApplication::initialize(self);
}

void HTTPSServer::uninitialize()
{
	Poco::Util::ServerApplication::uninitialize();
}

void HTTPSServer::defineOptions(Poco::Util::OptionSet& options)
{
	Poco::Util::ServerApplication::defineOptions(options);

	options.addOption(
		Poco::Util::Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false));
}

void HTTPSServer::handleOption(const std::string& name, const std::string& value)
{
	Poco::Util::ServerApplication::handleOption(name, value);

	if (name == "help")
		helpRequested_ = true;
}

void HTTPSServer::displayHelp()
{
	Poco::Util::HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A web server that serves the current date and time.");
	helpFormatter.format(std::cout);
}

int HTTPSServer::main(const std::vector<std::string>& args)
{
	if (helpRequested_)
	{
		displayHelp();
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		// Starts HTTPS server.
		//

		//! Context initialization #1
		Poco::FileInputStream fCert(
			Poco::Path(Application::commandPath()).parent().append(certificateName_).toString());
		if (!fCert)
			return Application::EXIT_IOERR;
		Poco::Crypto::X509Certificate cert(fCert);

		Poco::FileInputStream fPrivate(
			Poco::Path(Application::commandPath()).parent().append(privateKeyName_).toString());
		if (!fPrivate)
			return Application::EXIT_IOERR;
		Poco::Crypto::RSAKey pKey(nullptr, &fPrivate, "");

		Poco::Net::Context::Ptr context = new Poco::Net::Context(
			Poco::Net::Context::SERVER_USE,
			"",
			Poco::Net::Context::VERIFY_RELAXED,
			true);

		context->useCertificate(cert);
		context->usePrivateKey(pKey);

		//! Context initialization #2
// 		Poco::Net::Context::Ptr context = new Poco::Net::Context(
// 			Poco::Net::Context::SERVER_USE,
// 			Poco::Path(Application::commandPath()).parent().append(privateKeyName_).toString(),
// 			Poco::Path(Application::commandPath()).parent().append(certificateName_).toString(),
// 			"",
// 			Poco::Net::Context::VERIFY_RELAXED,
// 			true);

		context->enableExtendedCertificateVerification(true);
		context->enableSessionCache(true, "Application's unique session ID context");
		context->setSessionCacheSize(100);

		Poco::Net::SecureServerSocket socket(context);
		Poco::Net::SocketAddress address("localhost", 9443);
		socket.bind(address, true);
		socket.listen();

		Poco::Net::HTTPServer httpsServer(new HandlerFactory(
			Poco::DateTimeFormat::SORTABLE_FORMAT), socket, new Poco::Net::HTTPServerParams());
		httpsServer.start();

		std::cout << "HTTPS server: " << address.host().toString() << ":" << address.port();
		std::cout << " has been started"<< std::endl;

		//////////////////////////////////////////////////////////////////////////
		// Starts HTTP redirection server.
		//

		Poco::Net::SocketAddress httpAddress("localhost", 8080);
		Poco::Net::ServerSocket httpSocket;
		httpSocket.bind(httpAddress, true);
		httpSocket.listen();

		Poco::Net::HTTPServer httpServer(
			new RedirectHandlerFactory(), httpSocket, new Poco::Net::HTTPServerParams());
		httpServer.start();

		std::cout << "HTTP server: " << httpAddress.host().toString() << ":" << httpAddress.port();
		std::cout << " has been started" << std::endl;

		waitForTerminationRequest();
		httpServer.stop();
		httpsServer.stop();
	}
	return Application::EXIT_OK;
}