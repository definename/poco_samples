#include "pch.h"
#include "CustomBundleProviderActivator.h"
#include "CustomBundleServiceImpl.h"

void CustomBundleProviderActivator::start(Poco::OSP::BundleContext::Ptr context)
{
	std::string msg;
	Poco::format(msg, ">> Bundle %s started", context->thisBundle()->name());
	context->logger().information(msg);

	// Register new service.
	CustomBundleServiceImpl::Ptr customServicePtr = new CustomBundleServiceImpl(context);
	customServicePtr_ = context->registry().registerService(
		"com.my.CustomBundleService",
		customServicePtr,
		Poco::OSP::Properties());
}

void CustomBundleProviderActivator::stop(Poco::OSP::BundleContext::Ptr context)
{
	std::string msg;
	Poco::format(msg, "<< Bundle %s stopped", context->thisBundle()->name());
	context->logger().information(msg);

	// Unregister service.
	context->registry().unregisterService(customServicePtr_);
}