//
// TimeServiceRemoteObject.cpp
//
// Package: Generated
// Module:  TimeServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#include "TimeServiceRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "TimeServiceEventDispatcher.h"


namespace Services {


TimeServiceRemoteObject::TimeServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Services::TimeService> pServiceObject):
	Services::ITimeService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->wakeUp_ += Poco::delegate(this, &TimeServiceRemoteObject::event__wakeUp_);
}


TimeServiceRemoteObject::~TimeServiceRemoteObject()
{
	try
	{
		_pServiceObject->wakeUp_ -= Poco::delegate(this, &TimeServiceRemoteObject::event__wakeUp_);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TimeServiceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void TimeServiceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TimeServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TimeServiceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void TimeServiceRemoteObject::event__wakeUp_(const std::string& data)
{
	wakeUp_(this, data);
}


} // namespace Services

