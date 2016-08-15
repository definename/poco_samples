#include "pch.h"
#include "NullServer.h"

namespace libpocoemulator
{

NullServer::NullServer()
	: helpRequested_(false)
{ }

void NullServer::initialize(Poco::Util::Application& self)
{
	loadConfiguration();

	Poco::AutoPtr<Poco::Channel> rootChannel(new Poco::ConsoleChannel());
	if (config().getBool("application.runAsService", false))
		rootChannel = new Poco::FileChannel(Poco::Path(config().getString(
			"application.path")).setExtension("txt").toString());

	Poco::Logger::root().setChannel(rootChannel);

	Poco::AutoPtr<Poco::PatternFormatter> formatter =
		new Poco::PatternFormatter("%L%Y-%m-%d %H:%M:%S.%i [%p] %t");
	Poco::AutoPtr<Poco::FormattingChannel> chanel =
		new Poco::FormattingChannel(formatter, rootChannel);

	setLogger(Poco::Logger::create("Application", chanel, Poco::Message::PRIO_INFORMATION));

	logger().information("Application is being initialized");
	// TODO: Initialize your stuff here.

	ServerApplication::initialize(self);
}

void NullServer::uninitialize()
{
	logger().information("Application is being uninitialized");
	// TODO: Uninitialize your stuff here.

	ServerApplication::uninitialize();
}

void NullServer::defineOptions(Poco::Util::OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
		Poco::Util::Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(Poco::Util::OptionCallback<NullServer>(this, &NullServer::HandleHelp)));
}

void NullServer::HandleHelp(const std::string& name, const std::string& value)
{
	Poco::Util::HelpFormatter helpFormatter(options());
	helpFormatter.setUnixStyle(false);
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("[options]");
	helpFormatter.format(std::cout);

	helpRequested_ = true;

	stopOptionsProcessing();
}

void NullServer::handleOption(const std::string& name, const std::string& value)
{
	Poco::Util::ServerApplication::handleOption(name, value);
}

int NullServer::main(const ArgVec& args)
{
	if (!helpRequested_)
	{
		// TODO: Initialize your stuff here.
		logger().information("Wait for termination request");
		waitForTerminationRequest();
	}

	return Application::EXIT_OK;
}

} // namespace libpocoemulator