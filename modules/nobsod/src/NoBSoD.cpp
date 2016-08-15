#include "pch.h"
#include "NoBSoD.h"

namespace nobsod
{

NoBSoD::NoBSoD()
	: helpRequested_(false)
{ }

void NoBSoD::initialize(Poco::Util::Application& self)
{
	loadConfiguration();

	Poco::Util::ServerApplication::initialize(self);
}

int NoBSoD::main(const Application::ArgVec& args)
{
	if (!helpRequested_)
	{
		logger().information("Wait for termination request");
		while (true)
		{
			logger().information("Here is message!!!");
			Poco::Thread::sleep(1000);
		}

		waitForTerminationRequest();
	}

	return Application::EXIT_OK;
}

} // namespace nobsod