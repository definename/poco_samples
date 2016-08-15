#include "pch.h"
#include "CmdApplication.h"

CmdApplication::CmdApplication()
	: helpRequested_(false)
	, companyId_(Poco::UUID::null())
	, sessionType_("CSS")
	, deviceId_(Poco::UUID::null())
	, userId_(Poco::UUID::null())
	, httpPort_(21032)
	, serverIp_("127.0.0.1")
	, serverPort_(21031)
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
		.required(false)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("deviceId", "d", "Device id to connect to")
		.required(true)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("userId", "n", "Remote user id")
		.required(true)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("sessionType", "t", "Remote session type CSS/RDP")
		.required(false)
		.repeatable(false)
		.argument("value")
		.callback(Poco::Util::OptionCallback<CmdApplication>(this, &CmdApplication::OptionHandler)));

	options.addOption(
		Poco::Util::Option("binPath", "b", "Binary path")
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
	else if (name == "deviceId") {
		deviceId_.parse(value);
	}
	else if (name == "userId") {
		userId_.parse(value);
	}
	else if (name == "sessionType") {
		sessionType_ = value;
	}
	else if (name == "binPath") {
		viewerPath_.assign(value, Poco::Path::Style::PATH_WINDOWS);
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
		const std::string sessionId = GetSessionId(httpsSession, authToken);

		Launch(sessionId);
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

std::string CmdApplication::GetSessionId(
	libpocoemulator::types::HttpsSessionPtr httpsSession, const std::string& authToken)
{
	Poco::URI uri;
	uri.setPath("remoteSession");
	uri.addQueryParameter("auth", authToken);
	std::cout << uri.toString() << std::endl;

	Poco::JSON::Object::Ptr body(new Poco::JSON::Object());
	body->set("companyId", companyId_.toString());
	body->set("deviceId", deviceId_.toString());
	body->set("userId", userId_.toString());
	body->set("sessionType", sessionType_);

	Poco::JSON::Object::Ptr resp = httpsSession->PostAndJson(uri, body);
	if (!resp) {
		throw std::runtime_error("Session request failed");
	}
	if (!resp->has("sessionId")) {
		throw std::runtime_error("Session id is missed");
	}
	std::string sessionId = resp->getValue<std::string>("sessionId");
	std::cout << "Remote session id: " << sessionId << std::endl;

	return sessionId;
}

void CmdApplication::Launch(const std::string& sessionId)
{
	logger().information("Viewer path: " + viewerPath_.toString());

	if (!Poco::File(viewerPath_.toString()).exists())
	{
		logger().error("Unable to find binary by given path");
		return;
	}

	std::string params;
	Poco::format(
		params,
		"quicktech://connect?serverIP=%s&port=%i&sessionID=%s",
		serverIp_,
		serverPort_,
		sessionId);

	Poco::Process::Args args;
	args.push_back(params);
	logger().information("Viewer params: " + params);
	Poco::ProcessHandle handler = Poco::Process::launch(viewerPath_.toString(), args);
	logger().information("Exit code: " + handler.wait());
}