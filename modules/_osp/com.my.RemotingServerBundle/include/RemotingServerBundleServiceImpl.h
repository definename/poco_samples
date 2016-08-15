#pragma once

#include "RemotingServerBundleService.h"

class RemotingServerBundleServiceImpl : public RemotingServerBundleService
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	RemotingServerBundleServiceImpl(const Poco::OSP::BundleContext::Ptr& context);
	//! Destructor.
	~RemotingServerBundleServiceImpl() = default;

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