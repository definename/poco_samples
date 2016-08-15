#pragma once

class CustomBundleProviderActivator : public Poco::OSP::BundleActivator
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	CustomBundleProviderActivator() = default;
	//! Destructor.
	~CustomBundleProviderActivator() = default;

	//
	// Public interface.
	//
public: 
	//! Called during the "starting" phase of a bundle, after all dependencies have been resolved.
	void start(Poco::OSP::BundleContext::Ptr context) override;
	//! Called during the "stopping" phase of the bundle.
	void stop(Poco::OSP::BundleContext::Ptr context) override;

	//
	// Private data members.
	//
private:
	//! Custom service reference pointer.
	Poco::OSP::ServiceRef::Ptr customServicePtr_;
};

POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(CustomBundleProviderActivator)
POCO_END_MANIFEST