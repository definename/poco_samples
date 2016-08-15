#include "pch.h"

class Hello : public Poco::Runnable
{
public:
	Hello()
		: logger_(Poco::Logger::get("Application"))
	{ }
	~Hello() = default;

public:
	void run() override
	{
		logger_.information("I am running!!!");
	}

private:
	Poco::Logger& logger_;
};

class Main : public Poco::Util::ServerApplication
{
public:
	//! Constructor
	Main() = default;
	//! Destructor
	~Main() = default;

protected:
	//! The application's main logic.
	int main(const ArgVec& args)
	{
		// Initializes console logger.
		Poco::AutoPtr<Poco::FormattingChannel> channel(new Poco::FormattingChannel);
		channel->setChannel(new Poco::ConsoleChannel());
		channel->setFormatter(new Poco::PatternFormatter("%d/%m/%Y %H:%M:%S,%i [%p] %t"));
		logger().setChannel(channel);

		// Starts thread.
		Hello hello;
		Poco::Thread thread;
		thread.start(hello);
		thread.join();

		logger().information("Wait for termination request");
		waitForTerminationRequest();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(Main);