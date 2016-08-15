#include "pch.h"
#include "RemotingClientBundleServiceImpl.h"

RemotingClientBundleServiceImpl::RemotingClientBundleServiceImpl(
	const Poco::OSP::BundleContext::Ptr& context)
	: context_(context)
{
}

void RemotingClientBundleServiceImpl::DoSomething()
{
	context_->logger().information(">> DoSomething on client side");
}