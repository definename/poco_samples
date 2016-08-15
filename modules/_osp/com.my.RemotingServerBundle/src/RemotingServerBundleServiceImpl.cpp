#include "pch.h"
#include "RemotingServerBundleServiceImpl.h"

RemotingServerBundleServiceImpl::RemotingServerBundleServiceImpl(
	const Poco::OSP::BundleContext::Ptr& context)
	: context_(context)
{
}

void RemotingServerBundleServiceImpl::DoSomething()
{
	context_->logger().information(">> DoSomething on server side");
}