#pragma once

#include "Service.h"

namespace nobsod
{

class NoBSoD : public Poco::Util::ServerApplication
	// poco usage:
	// *.exe /registerService /displayName="NoBSoD" /description="Drop ELAN driver to prevent BSoD"
	// *.exe /unregisterService
	// *.exe /help
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	NoBSoD();
	//! Destructor.
	~NoBSoD() = default;

protected:
	//! Service container type.
	using ServiceList = std::vector<Service::Ptr>;

	//
	// Protected interface.
	//
protected:
	//! Initializes main application logic.
	void initialize(Poco::Util::Application& self) override;
	//! Uninitializes main application.
	void uninitialize() override;
	//! The application's main logic.
	int main(const Application::ArgVec& args) override;

	//
	// Private data members.
	//
protected:
	//! Help request flag.
	bool helpRequested_;
	//! Service list
	ServiceList serviceList_;
};

} // namespace nobsod

POCO_SERVER_MAIN(nobsod::NoBSoD)