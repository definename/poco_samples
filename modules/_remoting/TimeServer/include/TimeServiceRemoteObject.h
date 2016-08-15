//
// TimeServiceRemoteObject.h
//
// Package: Generated
// Module:  TimeServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TimeServiceRemoteObject_INCLUDED
#define TimeServiceRemoteObject_INCLUDED


#include "ITimeService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace Services {


class TimeServiceRemoteObject: public Services::ITimeService, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<TimeServiceRemoteObject> Ptr;

	TimeServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Services::TimeService> pServiceObject);
		/// Creates a TimeServiceRemoteObject.

	virtual ~TimeServiceRemoteObject();
		/// Destroys the TimeServiceRemoteObject.

	Services::LocationDataUnit GetLocation();

	virtual void TimeEvent(const Services::TEvent& timeEvent);

	void WakeUp(const Poco::DateTime& time, const std::string& message);

	Poco::DateTime currentTime() const;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

protected:
	void event__wakeUp_(const std::string& data);

private:
	Poco::SharedPtr<Services::TimeService> _pServiceObject;
};


inline Services::LocationDataUnit TimeServiceRemoteObject::GetLocation()
{
	return _pServiceObject->GetLocation();
}


inline void TimeServiceRemoteObject::TimeEvent(const Services::TEvent& timeEvent)
{
	_pServiceObject->TimeEvent(timeEvent);
}


inline void TimeServiceRemoteObject::WakeUp(const Poco::DateTime& time, const std::string& message)
{
	_pServiceObject->WakeUp(time, message);
}


inline Poco::DateTime TimeServiceRemoteObject::currentTime() const
{
	return _pServiceObject->currentTime();
}


inline const Poco::RemotingNG::Identifiable::TypeId& TimeServiceRemoteObject::remoting__typeId() const
{
	return ITimeService::remoting__typeId();
}


} // namespace Services


#endif // TimeServiceRemoteObject_INCLUDED

