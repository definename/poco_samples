#pragma once

#include "CustomBundleService.h"

class CustomBundleServiceImpl : public CustomBundleService
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	CustomBundleServiceImpl(Poco::OSP::BundleContext::Ptr context);
	//! Destructor.
	~CustomBundleServiceImpl() = default;


	//
	// Public interface.
	//
public:
	//! Returns the type information for the object's class.
	const std::type_info& type() const;
	//! Returns true if the class is a subclass of the class.
	bool isA(const std::type_info& otherType) const;

	//
	// Public interface.
	//
public:
	//! Does something.
	std::string GetSomething() const override;

	//
	// Private data members.
	//
private:
	//! Bundle context pointer.
	Poco::OSP::BundleContext::Ptr context_;
};