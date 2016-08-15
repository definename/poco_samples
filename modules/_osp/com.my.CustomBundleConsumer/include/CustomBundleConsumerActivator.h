#pragma once

class CustomBundleConsumerActivator : public Poco::OSP::BundleActivator
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	CustomBundleConsumerActivator();
	//! Destructor.
	~CustomBundleConsumerActivator() = default;

	//
	// Public interface.
	//
public: 
	//! Called during the "starting" phase of a bundle, after all dependencies have been resolved.
	void start(Poco::OSP::BundleContext::Ptr context) override;
	//! Called during the "stopping" phase of the bundle.
	void stop(Poco::OSP::BundleContext::Ptr context) override;

	//
	// Protected interface.
	//
protected:
	//! Handles service registration.
	void HandleServiceRegistered(const void* sender, const Poco::OSP::ServiceRef::Ptr& service);
	//! Handles service unregistration.
	void HandleServiceUnregistered(const void* sender, const Poco::OSP::ServiceRef::Ptr& service);

	//
	// Private interface.
	//
private:
	//! Calls custom service.
	void CallCustomBundleService(const Poco::OSP::ServiceRef::Ptr& serviceRef) const;

	//
	// Private data members.
	//
private:
	//! Bundle context pointer.
	Poco::OSP::BundleContext::Ptr context_;
	//! Service listener.
	Poco::OSP::ServiceListener::Ptr listener_;
	//! Service name we use in our tests.
	const std::string serviceName_;
};

POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(CustomBundleConsumerActivator)
POCO_END_MANIFEST