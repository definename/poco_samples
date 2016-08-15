#pragma once

class CustomBundleService : public Poco::OSP::Service
{
	//
	// Public types.
	//
public:
	using Ptr = Poco::AutoPtr<CustomBundleService>;

	//
	// Public interface.
	//
public:
	//! Does something.
	virtual std::string GetSomething() const = 0;

};