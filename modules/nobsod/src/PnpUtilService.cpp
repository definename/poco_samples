#include "pch.h"
#include "PnpUtilService.h"
#include "ServiceNotification.h"

namespace nobsod
{

PnpUtilService::PnpUtilService(Poco::Logger& logger)
	: Service(logger, "PnpUtilService")
{

}

PnpUtilService::~PnpUtilService()
{
	Stop();
}

void PnpUtilService::run()
{
	logger_.information("%s is running...", Name());

	Poco::Notification::Ptr nt = queue_.waitDequeueNotification();
	while (!nt.isNull())
	{
		ServiceNotification::Ptr pnpNt = nt.cast<ServiceNotification>();
		if (!pnpNt.isNull())
		{
			auto action = pnpNt->GetType();
			if (action == ServiceNotification::Type::StopService)
			{
				logger_.information("%s is being stopped", Name());
				break;
			}
			else
			{
				logger_.warning("%s unhandled notification triggered", Name());
			}

		}
		nt = queue_.waitDequeueNotification();
	}
}

} // namespace nobsod