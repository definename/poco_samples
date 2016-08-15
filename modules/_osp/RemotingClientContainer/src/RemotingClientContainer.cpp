#include "pch.h"

class RemotingContainerClient : public Poco::Util::ServerApplication
{
	//
	// Public interface.
	//
public:
	//! Constructor.
	RemotingContainerClient()
		: pOsp_(new Poco::OSP::OSPSubsystem)
	{
		addSubsystem(pOsp_);
	}

	//! Initializes the application and all registered subsystems.
	void initialize(Poco::Util::Application& self)
	{
		loadConfiguration();

		Application::initialize(self);
	}
	//! The application's main logic.
	int main(const ArgVec& args)
	{
		try
		{
			waitForTerminationRequest();
		}
		catch (const Poco::Exception& e)
		{
			logger().information("%s", e.displayText());
		}

		return ServerApplication::EXIT_OK;
	}
	//! OSP sub system pointer.
	Poco::OSP::OSPSubsystem* pOsp_;
};

POCO_SERVER_MAIN(RemotingContainerClient);