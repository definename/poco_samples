#pragma once

class RemotingClientBundleService : public Poco::OSP::Service
{
	//
	// Public types.
	//
public:
	//! Pointer type.
	using Ptr = Poco::AutoPtr<RemotingClientBundleService>;

	//
	// Public interface.
	//
public:
	//! Does something.
	virtual void DoSomething() = 0;

	//
	// Public date members.
	//
public:
	//! Service name.
	static constexpr const char serviceName_[] = "com.my.RemotingClientBundleService";
};