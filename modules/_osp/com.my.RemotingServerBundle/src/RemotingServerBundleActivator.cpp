#include "pch.h"
#include "RemotingServerBundleActivator.h"
#include "RemotingServerBundleServiceImpl.h"

void RemotingServerBundleActivator::start(Poco::OSP::BundleContext::Ptr context)
{
	try
	{
		context_ = context;

		context_->systemEvents().systemStarted += Poco::delegate(
			this, &RemotingServerBundleActivator::OnSystemEvent);
		context_->systemEvents().systemShuttingDown += Poco::delegate(
			this, &RemotingServerBundleActivator::OnSystemEvent);

		context_->registry().registerService(
			RemotingServerBundleService::serviceName_,
			new RemotingServerBundleServiceImpl(context),
			Poco::OSP::Properties());
	}
	catch (const Poco::Exception& e)
	{
		context_->logger().information("Failed to start bundle %s with error: %s",
			context_->thisBundle()->name(),
			e.displayText());
	}
}

void RemotingServerBundleActivator::stop(Poco::OSP::BundleContext::Ptr context)
{
	try
	{
		context_->systemEvents().systemStarted -= Poco::delegate(
			this, &RemotingServerBundleActivator::OnSystemEvent);
		context_->systemEvents().systemShuttingDown -= Poco::delegate(
			this, &RemotingServerBundleActivator::OnSystemEvent);

		context_->registry().unregisterService(RemotingServerBundleService::serviceName_);
	}
	catch (const Poco::Exception& e)
	{
		context_->logger().information("Failed to stop bundle %s with error: %s",
			context_->thisBundle()->name(),
			e.displayText());
	}
}

void RemotingServerBundleActivator::OnSystemEvent(Poco::OSP::SystemEvents::EventKind& event)
{
	if (event == Poco::OSP::SystemEvents::EV_SYSTEM_STARTED)
	{
		context_->logger().information(">> EV_SYSTEM_STARTED");
	}
	else if (event == Poco::OSP::SystemEvents::EV_SYSTEM_SHUTTING_DOWN)
	{
		context_->logger().information(">> EV_SYSTEM_SHUTTING_DOWN");
	}
	else
	{
		context_->logger().error("Unknown system event");
	}
}