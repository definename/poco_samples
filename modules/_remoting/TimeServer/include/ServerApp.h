#pragma once

#include "TimeServiceImpl.h"

// Forward declaration.
class ConnectionHandler;

class ServerApp : public Poco::Util::ServerApplication
{
	//
	// Protected interface.
	//
protected:
	//! The application's main logic.
	int main(const ArgVec& args)
	{
		try
		{
			//StartSoapTransport();

			{
				// Initialize TCP service.
				Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
				orb.objectRegistered += Poco::delegate(this, &ServerApp::OnObjectRegistered);

				const std::string listenerId = orb.registerListener(
					new Poco::RemotingNG::TCP::Listener("localhost:9090"));

				// To be able to support remoting events(server to client)
				Poco::RemotingNG::TCP::TransportFactory::registerFactory();

				InitTcpService(listenerId, "TheClock");
			}

			waitForTerminationRequest();
		}
		catch (const Poco::Exception& e)
		{
			logger().error("Error occurred: %s", e.displayText());
		}
		Poco::RemotingNG::ORB::instance().shutdown();

		return ServerApplication::EXIT_OK;
	}

	//
	// Private interface.
	//
private:
	//! Starts Tcp transport.
	void InitTcpService(
		const std::string& listenerId,
		const std::string& objectId);
	//! Starts Soap transport.
	void StartSoapTransport();
	//! Time event handler.
	void OnTimeEvent(const Services::TEvent& timeEvent);
	//! New client acceptance handler.
	void OnConnectionAccepted(Poco::RemotingNG::TCP::Connection::Ptr& connection);
	//! Object registration handler.
	void OnObjectRegistered(const Poco::RemotingNG::ORB::ObjectRegistration& obj);

	//
	// Private data members.
	//
private:
	//! Connection list.
	std::vector<Poco::SharedPtr<ConnectionHandler>> connectionList_;
};

POCO_SERVER_MAIN(ServerApp);