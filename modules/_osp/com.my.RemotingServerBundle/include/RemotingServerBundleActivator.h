#pragma once

class RemotingServerBundleActivator : public Poco::OSP::BundleActivator
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	RemotingServerBundleActivator() = default;
	//! Destructor.
	~RemotingServerBundleActivator() = default;

	//
	// Public interface.
	//
public: 
	//! Called during the "starting" phase of a bundle, after all dependencies have been resolved.
	void start(Poco::OSP::BundleContext::Ptr context) override;
	//! Called during the "stopping" phase of the bundle.
	void stop(Poco::OSP::BundleContext::Ptr context) override;

	//
	// Private interface.
	//
private:
	//! OSP system event hander.
	void OnSystemEvent(Poco::OSP::SystemEvents::EventKind& event);

	//
	// Private data members.
	//
private:
	//! Bundle context pointer.
	Poco::OSP::BundleContext::Ptr context_;
};

POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(RemotingServerBundleActivator)
POCO_END_MANIFEST