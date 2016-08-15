#include "pch.h"
#include "Target.h"
#include "Source.h"

class Main : public Poco::Util::Application
{
	int main(const ArgVec& args)
	{
		// Initializes console logger.
		Poco::AutoPtr<Poco::FormattingChannel> channel(new Poco::FormattingChannel);
		channel->setChannel(new Poco::ConsoleChannel());
		channel->setFormatter(new Poco::PatternFormatter("%d/%m/%Y %H:%M:%S,%i [%p] %t"));
		logger().setChannel(channel);

		Source source;
		Target target(logger());

		source.theEvent_ += Poco::Delegate<Target, int>(&target, &Target::OnEvent);

		source.FireEvent(123);

		source.theEvent_ -= Poco::Delegate<Target, int>(&target, &Target::OnEvent);

		return Application::EXIT_OK;
	}
};

POCO_APP_MAIN(Main);