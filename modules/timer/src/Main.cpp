#include "pch.h"

class UtilTask : public Poco::Util::TimerTask
{
public:
	UtilTask(Poco::Logger& logger)
		: logger_(logger)
		, counter_(0)
	{ }
public:
	void run() override
	{
		++counter_;
		if (counter_ > 5)
		{
			logger_.information("UTimer has just stopped");
			cancel();
			return;
		}
		logger_.information("UTask has been invoked");
	}
private:
	Poco::Logger& logger_;
	Poco::AtomicCounter counter_;
};

class App : public Poco::Util::ServerApplication
{
public:
	App()
		: counter_(0)
	{ }

protected:
	int main(const ArgVec& args)
	{
		// Initializes console logger.
		Poco::AutoPtr<Poco::FormattingChannel> channel(new Poco::FormattingChannel);
		channel->setChannel(new Poco::ConsoleChannel());
		channel->setFormatter(new Poco::PatternFormatter("%d/%m/%Y %H:%M:%S,%i [%p] %t"));
		logger().setChannel(channel);

		Poco::Timer regularTimer(1000, 1000);
		regularTimer.start(Poco::TimerCallback<App>(*this, &App::OnTimer));

		Poco::Util::Timer utilTimer;
		utilTimer.schedule(new UtilTask(logger()), 1000, 1000);

		waitForTerminationRequest();

		regularTimer.stop();
		utilTimer.cancel();

		return Application::EXIT_OK;
	}

	void OnTimer(Poco::Timer& timer)
	{
		++counter_;
		if (counter_.value() > 5)
		{
			timer.restart(0);
			logger().information("OnTimer has just stopped");
			return;
		}
		logger().information("OnTimer has been invoked");
	}

private:
	Poco::AtomicCounter counter_;
};

POCO_SERVER_MAIN(App);