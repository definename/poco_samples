//
// TimeServiceProxy.h
//
// Package: Generated
// Module:  TimeServiceProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TimeServiceProxy_INCLUDED
#define TimeServiceProxy_INCLUDED


#include "ITimeService.h"
#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"


namespace Services {


class TimeServiceProxy: public Services::ITimeService, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<TimeServiceProxy> Ptr;

	TimeServiceProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a TimeServiceProxy.

	virtual ~TimeServiceProxy();
		/// Destroys the TimeServiceProxy.

	Services::LocationDataUnit GetLocation();

	virtual void TimeEvent(const Services::TEvent& timeEvent);

	void WakeUp(const Poco::DateTime& time, const std::string& message);

	Poco::DateTime currentTime() const;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	static const std::string DEFAULT_NS;
	mutable Services::LocationDataUnit _GetLocationRet;
	mutable Poco::DateTime _currentTimeRet;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& TimeServiceProxy::remoting__typeId() const
{
	return ITimeService::remoting__typeId();
}


} // namespace Services


#endif // TimeServiceProxy_INCLUDED

