#include "pch.h"
#include "CmdApplication.h"

CmdApplication::CmdApplication()
	: helpRequested_(false)
	, isOnetime_(false)
	, sessionId_(Poco::UUID::null())
	, groupId_(Poco::UUID::null())
	, serverPort_(21031)
	, companyId_(Poco::UUID::null())
	, httpPort_(21032)
{ }

void CmdApplication::initialize(Poco::Util::Application& self)
{
	loadConfiguration();

	Poco::AutoPtr<Poco::Channel> rootChannel(new Poco::ConsoleChannel());
	if (config().getBool("application.runAsService", false))
	{
		rootChannel = new Poco::FileChannel(
			Poco::Path(config().getString("application.path")).setExtension("txt").toString());
	}

	Poco::Logger::root().setChannel(rootChannel);

	Poco::AutoPtr<Poco::PatternFormatter> formatter =
		new Poco::PatternFormatter("%L%Y-%m-%d %H:%M:%S.%i [%p] %t");
	Poco::AutoPtr<Poco::FormattingChannel> chanel =
		new Poco::FormattingChannel(formatter, rootChannel);

	logger().information(logger().name());
	setLogger(Poco::Logger::create("Application", chanel, Poco::Message::PRIO_INFORMATION));

	logger().information("Application is being initialized");
	// TODO: Initialize your stuff here.

	Application::initialize(self);
}

void CmdApplication::uninitialize()
{
	logger().information("Application is being uninitialized");
	// TODO: Uninitialize your stuff here.

	Application::uninitialize();
}

void CmdApplication::defineOptions(Poco::Util::OptionSet& options)
{
	Application::defineOptions(options);

	options.addOption(
		Poco::Util::Option("help", "h", "Display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::HandleHelp)));

	options.addOption(
		Poco::Util::Option("serverIp", "i", "Server ip address to connect to")
		.required(true)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("serverPort", "p", "Server port to connect to")
		.required(false)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("companyId", "c", "Company id to connect to")
		.required(true)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("isOnetime", "o", "Creates onetime agent")
		.required(false)
		.repeatable(false)
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("sessionId", "s", "Onetime session id")
		.required(false)
		.repeatable(false)
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("endpoint", "e", "Endpoint, possible values: buildAgent, buildDownloader")
		.required(true)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("fileName", "e", "Destination file name")
		.required(true)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("httpPort", "t", "Http server port")
		.required(false)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("groupId", "g", "Device group id")
		.required(false)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));
}

void CmdApplication::HandleHelp(const std::string& name, const std::string& value)
{
	helpRequested_ = true;

	Poco::Util::HelpFormatter helpFormatter(options());
	helpFormatter.setUnixStyle(false);
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("[options]");
	helpFormatter.format(std::cout);

	stopOptionsProcessing();
}

void CmdApplication::OptionHandler(const std::string& name, const std::string& value)
{
	if (name == "serverIp") {
		serverIp_ = value;
	}
	else if (name == "serverPort") {
		serverPort_ = std::stoi(value);
	}
	else if (name == "companyId") {
		companyId_.parse(value);
	}
	else if (name == "isOnetime") {
		isOnetime_ = true;
	}
	else if (name == "sessionId") {
		sessionId_.parse(value);
	}
	else if (name == "endpoint") {
		endpoint_ = value;
	}
	else if (name == "fileName") {
		fileName_ = value;
	}
	else if (name == "httpPort") {
		httpPort_ = std::stoi(value);
	}
	else if (name == "groupId") {
		groupId_.parse(value);
	}
}

void CmdApplication::handleOption(const std::string& name, const std::string& value)
{
	Poco::Util::Application::handleOption(name, value);
}

int CmdApplication::main(const ArgVec& args)
{
	if (!helpRequested_)
	{
		libpocoemulator::types::HttpsSessionPtr httpsSession = 
			new libpocoemulator::HttpsSession(serverIp_, httpPort_);
		const std::string authToken = GetToken(httpsSession);
		Build(httpsSession, authToken);
	}

	return CmdApplication::EXIT_OK;
}

std::string CmdApplication::GetToken(libpocoemulator::types::HttpsSessionPtr httpsSession)
{
	Poco::URI uri;
	uri.setPath("get_auth_token");
	uri.addQueryParameter("login", "VasyMatros");
	uri.addQueryParameter("pass", "c5f30a7ade31034ceec15f90122414718794f11d");
	uri.addQueryParameter("t", "212121212");

	Poco::JSON::Object::Ptr resp = httpsSession->GetAndJson(uri);
	if (!resp) {
		throw std::runtime_error("Authentication request failed");
	}
	if (!resp->has("token")) {
		throw std::runtime_error("Authentication token is missed");
	}
	std::string authToken = resp->getValue<std::string>("token");
	logger().information("Auth token is: " + authToken);

	return authToken;
}

void CmdApplication::Build(
	libpocoemulator::types::HttpsSessionPtr httpsSession,
	const std::string& authToken)
{
	Poco::URI uri;
	Poco::Path dest(config().getString("application.dir"));
	dest.setFileName(fileName_);
	uri.setPath(endpoint_);
	uri.addQueryParameter("auth", authToken);

	Poco::JSON::Object::Ptr body(new Poco::JSON::Object());
	body->set("serverIP", httpsSession->GetHost());
	body->set("serverPort", std::to_string(serverPort_));
	body->set("companyId", companyId_.toString());
	body->set("isOneTime", isOnetime_);
	body->set("sessionId", sessionId_.toString());
	body->set("groupId", groupId_.toString());

	std::stringstream bytes;
	bytes << httpsSession->PostAndDownload(uri, body, dest);
	logger().information("Bytes received: " + bytes.str());
}