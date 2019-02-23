#include "pch.h"

class BaseNotification : public Poco::Notification {

};

class SubNofication : public BaseNotification {

};

class Target
{
public:
	Target(Poco::Logger& logger)
		: logger_(logger)
	{ }

public:
	void handleBase(BaseNotification* baseNt) {
		logger_.information("base handler: %s", baseNt->name());
		baseNt->release();
	}
	void handleSub(const Poco::AutoPtr<SubNofication>& subNt) {
		logger_.information("sub handler: %s", subNt->name());
	}

private:
	Poco::Logger& logger_;
};

class Main : public Poco::Util::ServerApplication
{
protected:
	int main(const ArgVec& args)
	{
		// Initializes console logger.
		Poco::AutoPtr<Poco::FormattingChannel> channel(new Poco::FormattingChannel);
		channel->setChannel(new Poco::ConsoleChannel());
		channel->setFormatter(new Poco::PatternFormatter("%d/%m/%Y %H:%M:%S,%i [%p] %t"));
		logger().setChannel(channel);

		Poco::NotificationCenter nc;
		Target target(logger());

		nc.addObserver(Poco::Observer<Target, BaseNotification>(target, &Target::handleBase));
		nc.addObserver(Poco::NObserver<Target, SubNofication>(target, &Target::handleSub));

		nc.postNotification(new BaseNotification);
		nc.postNotification(new SubNofication);

		nc.removeObserver(Poco::Observer<Target, BaseNotification>(target, &Target::handleBase));
		nc.removeObserver(Poco::NObserver<Target, SubNofication>(target, &Target::handleSub));

		waitForTerminationRequest();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(Main);