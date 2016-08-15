//
// LocationDataUnitSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Services_LocationDataUnit_INCLUDED
#define TypeSerializer_Services_LocationDataUnit_INCLUDED


#include "InternalDeserializer.h"
#include "InternalSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "TimeService.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Services::LocationDataUnit>
{
public:
	static void serialize(const std::string& name, const Services::LocationDataUnit& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Services::LocationDataUnit& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"accuracy","buf","data","internal","speed","velocity",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<float >::serialize(REMOTING__NAMES[0], value.accuracy_, ser);
		TypeSerializer<std::vector < int > >::serialize(REMOTING__NAMES[1], value.buf_, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.data_, ser);
		TypeSerializer<Services::Internal >::serialize(REMOTING__NAMES[3], value.internal_, ser);
		TypeSerializer<float >::serialize(REMOTING__NAMES[4], value.speed_, ser);
		TypeSerializer<unsigned int >::serialize(REMOTING__NAMES[5], value.velocity_, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Services_LocationDataUnit_INCLUDED

