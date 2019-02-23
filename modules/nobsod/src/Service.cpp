#include "pch.h"
#include "PnpUtilService.h"
#include "ServiceNotification.h"

namespace nobsod
{

Service::Service(Poco::Logger& logger, const std::string& name)
	: logger_(logger)
	, name_(name)
{

}

Service::~Service()
{
	try
	{
		if (thread_.isRunning()) {
			thread_.join();
		}

		logger_.information("%s has been stopped", Name());
	}
	catch (const std::exception& e)
	{
		logger_.error("%s destruction error: %s", Name(), e.what());
	}
}

void Service::Start()
{
	thread_.start(*this);
}

void Service::Stop()
{
	queue_.enqueueNotification(new ServiceNotification(ServiceNotification::Type::StopService));
}

std::string Service::Name() const
{
	return name_;
}

} // namespace nobsod