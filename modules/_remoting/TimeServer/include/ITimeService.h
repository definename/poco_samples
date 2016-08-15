//
// ITimeService.h
//
// Package: Generated
// Module:  ITimeService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef ITimeService_INCLUDED
#define ITimeService_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "TimeService.h"


namespace Services {


class ITimeService: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<ITimeService> Ptr;

	ITimeService();
		/// Creates a ITimeService.

	virtual ~ITimeService();
		/// Destroys the ITimeService.

	virtual Services::LocationDataUnit GetLocation() = 0;

	virtual void TimeEvent(const Services::TEvent& timeEvent) = 0;

	virtual void WakeUp(const Poco::DateTime& time, const std::string& message) = 0;

	virtual Poco::DateTime currentTime() const = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	Poco::BasicEvent < const std::string > wakeUp_;
};


} // namespace Services


#endif // ITimeService_INCLUDED

