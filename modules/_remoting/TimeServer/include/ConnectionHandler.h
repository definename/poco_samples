#pragma once

#include "ScopedLog.h"

class ConnectionHandler
{
public:
	ConnectionHandler(Poco::Logger& logger, const std::string& uri)
		: uri_(uri)
		, logger_(logger)
	{ }

public:
	void OnConnectionEstablished(Poco::RemotingNG::TCP::Connection::Ptr& connection) {
		ScopedLog log(logger_, "OnConnectionEstablished " + uri_);
		logger_.information("IdleTimeout: %d", connection->getIdleTimeout().milliseconds());
	}

	void OnConnectionClossing(Poco::RemotingNG::TCP::Connection::Ptr& connection) {
		ScopedLog log(logger_, "OnConnectionClossing " + uri_);
		logger_.information("IdleTimeout: %d", connection->getIdleTimeout().milliseconds());
	}

	void OnConnectionClossed(Poco::RemotingNG::TCP::Connection::Ptr& connection) {
		ScopedLog log(logger_, "OnConnectionClossed " + uri_);
		logger_.information("IdleTimeout: %d", connection->getIdleTimeout().milliseconds());
	}

	void OnConnectionAborted(Poco::RemotingNG::TCP::Connection::Ptr& connection) {
		ScopedLog log(logger_, "OnConnectionAborted " + uri_);
		logger_.information("IdleTimeout: %d", connection->getIdleTimeout().milliseconds());
	}

	void OnConnectionAccepted(Poco::RemotingNG::TCP::Connection::Ptr& connection)
	{
		ScopedLog log(logger_, "OnConnectionAccepted " + uri_);
		logger_.information("IdleTimeout: %d", connection->getIdleTimeout().milliseconds());

		logger_.information("id: %s", std::to_string(connection->id()));
		const std::string mode(connection->mode() == Poco::RemotingNG::TCP::Connection::MODE_CLIENT ? "MODE_CLIENT" : "MODE_SERVER");
		logger_.information("mode: %s", mode);
		logger_.information("Local address: %s", connection->localAddress().toString());
		logger_.information("Remote address: %s", connection->localAddress().toString());

		connection->connectionEstablished += Poco::delegate(
			this, &ConnectionHandler::OnConnectionEstablished);
		connection->connectionClosing += Poco::delegate(
			this, &ConnectionHandler::OnConnectionClossing);
		connection->connectionClosed += Poco::delegate(
			this, &ConnectionHandler::OnConnectionClossed);
		connection->connectionAborted += Poco::delegate(
			this, &ConnectionHandler::OnConnectionAborted);
	}

private:
	const std::string uri_;
	Poco::Logger& logger_;
};