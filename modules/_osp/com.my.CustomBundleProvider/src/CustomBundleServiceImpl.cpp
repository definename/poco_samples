#include "pch.h"
#include "CustomBundleServiceImpl.h"

CustomBundleServiceImpl::CustomBundleServiceImpl(Poco::OSP::BundleContext::Ptr context)
	: context_(context)
{ 
}

std::string CustomBundleServiceImpl::GetSomething() const
{
	context_->logger().information("==>> Something on provider side");
	return "Something";
}

const std::type_info& CustomBundleServiceImpl::type() const
{
	return typeid(CustomBundleService);
}

bool CustomBundleServiceImpl::isA(const std::type_info& otherType) const
{
	std::string name(typeid(CustomBundleService).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}