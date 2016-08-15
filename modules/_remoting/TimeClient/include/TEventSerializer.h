//
// TEventSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Services_TEvent_INCLUDED
#define TypeSerializer_Services_TEvent_INCLUDED


#include "Poco/RemotingNG/TypeSerializer.h"
#include "TimeService.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Services::TEvent>
{
public:
	static void serialize(const std::string& name, const Services::TEvent& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Services::TEvent& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"timeEvent","timeStatus",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.timeEvent_, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[1], value.timeStatus_, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Services_TEvent_INCLUDED

