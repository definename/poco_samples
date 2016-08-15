#include "pch.h"
#include "CustomBundleConsumerActivator.h"
#include "CustomBundleService.h"

CustomBundleConsumerActivator::CustomBundleConsumerActivator()
	: serviceName_("com.my.CustomBundleService")
{ }

void CustomBundleConsumerActivator::start(Poco::OSP::BundleContext::Ptr context)
{
	context_ = context;

	std::string msg;
	Poco::format(msg, ">> Bundle %s started", context_->thisBundle()->name());
	context_->logger().information(msg);

	if (true)
	{
		// This case does not depend on bundles order registration.
		listener_ = context_->registry().createListener(
			"name == \"" + serviceName_ + "\"",
			Poco::delegate(this, &CustomBundleConsumerActivator::HandleServiceRegistered),
			Poco::delegate(this, &CustomBundleConsumerActivator::HandleServiceUnregistered));
	}
	else
	{
		// This case depends on bundles order registration.
		CallCustomBundleService(context_->registry().findByName(serviceName_));
	}
}

void CustomBundleConsumerActivator::stop(Poco::OSP::BundleContext::Ptr context)
{
	std::string msg;
	Poco::format(msg, "<< Bundle %s stopped", context_->thisBundle()->name());
	context_->logger().information(msg);
}

void CustomBundleConsumerActivator::CallCustomBundleService(
	const Poco::OSP::ServiceRef::Ptr& serviceRef) const
{
	if (serviceRef)
	{
		try
		{
			CustomBundleService::Ptr customServicePtr = serviceRef->castedInstance<CustomBundleService>();

			std::string msg;
			Poco::format(msg, "==>> %s on consumer side", customServicePtr->GetSomething());
			context_->logger().information(msg);
		}
		catch (const Poco::Exception& e)
		{
			context_->logger().error("Error occurred: ", e.message());
		}
	}
}

void CustomBundleConsumerActivator::HandleServiceRegistered(
	const void* sender, const Poco::OSP::ServiceRef::Ptr& serviceRef)
{
	const std::string name = serviceRef->properties().get("name");
	context_->logger().information(">> Service registered %s", name);

	if (Poco::icompare(name, serviceName_) == 0) {
		CallCustomBundleService(serviceRef);
	}
}

void CustomBundleConsumerActivator::HandleServiceUnregistered(
	const void* sender, const Poco::OSP::ServiceRef::Ptr& serviceRef)
{
	const std::string name = serviceRef->properties().get("name");
	context_->logger().information("<< Service unregistered %s", name);
}