#include "pch.h"
#include "ConnectionHandler.h"
#include "ServerApp.h"
#include "TimeServiceServerHelper.h"

void ServerApp::OnTimeEvent(const Services::TEvent& timeEvent)
{
	ScopedLog log(logger(), "OnTimeEvent");

	logger().information("Time event has been fired: %s", timeEvent.timeEvent_);

	if (timeEvent.timeStatus_ == Services::TStatus::GOOD) {
		logger().information("Services::TStatus::GOOD");
	}
	else if (timeEvent.timeStatus_ == Services::TStatus::BETTER) {
		logger().information("Services::TStatus::BETTER");
	}
	else if (timeEvent.timeStatus_ == Services::TStatus::THEBEST) {
		logger().information("Services::TStatus::THEBEST");
	}
}

void ServerApp::OnObjectRegistered(const Poco::RemotingNG::ORB::ObjectRegistration& obj)
{
	ScopedLog log(logger(), "OnObjectRegistered");

	logger().information("Uri: %s", obj.uri);
	logger().information("Alias: %s ", obj.alias);

	Poco::SharedPtr<ConnectionHandler> handler(new ConnectionHandler(logger(), obj.uri));
	auto listener = obj.pListener.cast<Poco::RemotingNG::TCP::Listener>();
	if (listener.isNull())
	{
		logger().information("Failed to cast to Tcp listener");
		return;
	}

	listener->connectionAccepted += Poco::delegate(handler.get(), &ConnectionHandler::OnConnectionAccepted);
	logger().information("Listener endpoint: %s ", listener->endPoint());
	logger().information("Acceptance handler has been set for: %s", obj.uri);
	connectionList_.push_back(handler);
}

void ServerApp::InitTcpService(
	const std::string& listenerId,
	const std::string& objectId)
{
	logger().information("Tcp listener id: %s", listenerId);
	logger().information("Tcp object id: %s", objectId);

	Poco::SharedPtr<Services::TimeService> tcpService(new Services::TimeServiceImpl());
	auto tcpServiceImpl = tcpService.cast<Services::TimeServiceImpl>();
	if (tcpServiceImpl.isNull())
	{
		logger().error("Failed to create Tcp object with id");
		return;
	}

	// Register object.
	tcpServiceImpl->timeEvent_ += Poco::delegate(this, &ServerApp::OnTimeEvent);
	const std::string tcpUri = Services::TimeServiceServerHelper::registerObject(
		tcpServiceImpl, objectId, listenerId);
	logger().information("Tcp Uri: %s", tcpUri);

	// Enables remoting events (server to client) for given URI.
	Services::TimeServiceServerHelper::enableEvents(tcpUri, "tcp");
}

void ServerApp::StartSoapTransport()
{
	// Initialize SOAP
// 	auto soapListener = Poco::RemotingNG::ORB::instance().registerListener(
// 		new Poco::RemotingNG::SOAP::Listener("0.0.0.0:8080", "wsdl"));
// 	logger().information("SOAP listener: %s", soapListener);
// 
// 	Poco::SharedPtr<Services::TimeService> soapService(new Services::TimeServiceImpl);
// 
// 	// Check functionality to cast base class to derived one.
// 	{
// 		Poco::SharedPtr<Services::TimeServiceImpl> isoapServiceImpl;
// 		isoapServiceImpl = soapService.cast<Services::TimeServiceImpl>();
// 		isoapServiceImpl->timeEvent_ += Poco::delegate(this, &SrvApplication::OnTimeEvent);
// 	}
// 
// 	auto soapUri = Services::TimeServiceServerHelper::registerObject(soapService, "TheClock", soapListener);
// 	logger().information("SOAP transport URI: %s", soapUri);
}