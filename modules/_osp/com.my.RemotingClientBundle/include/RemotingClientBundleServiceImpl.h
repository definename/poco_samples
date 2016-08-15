#pragma once

#include "RemotingClientBundleService.h"

class RemotingClientBundleServiceImpl : public RemotingClientBundleService
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	RemotingClientBundleServiceImpl(const Poco::OSP::BundleContext::Ptr& context);
	//! Destructor.
	~RemotingClientBundleServiceImpl() = default;

	//
	// Public interface.
	//
public:
	//! Does something.
	virtual void DoSomething() override;

	//
	// Private data members.
	//
private:
	//! Bundle context pointer.
	Poco::OSP::BundleContext::Ptr context_;
};