#include "pch.h"
#include "NoBSoD.h"
#include "PnpUtilService.h"

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

void NoBSoD::uninitialize()
{
	for (auto& service : serviceList_)
	{
		service->Stop();
	}

	ServerApplication::uninitialize();
}

int NoBSoD::main(const Application::ArgVec& args)
{
	if (!helpRequested_)
	{
		logger().information("Wait for termination request");

		serviceList_.push_back(new PnpUtilService(logger()));

		for (auto& service : serviceList_)
		{
			service->Start();
		}

		waitForTerminationRequest();
	}

	return Application::EXIT_OK;
}

} // namespace nobsod