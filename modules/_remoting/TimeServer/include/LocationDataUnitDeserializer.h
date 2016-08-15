//
// LocationDataUnitDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeDeserializer_Services_LocationDataUnit_INCLUDED
#define TypeDeserializer_Services_LocationDataUnit_INCLUDED


#include "InternalDeserializer.h"
#include "InternalSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "TimeService.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Services::LocationDataUnit>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Services::LocationDataUnit& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Services::LocationDataUnit& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"accuracy","buf","data","internal","speed","velocity"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<float >::deserialize(REMOTING__NAMES[0], true, deser, value.accuracy_);
		TypeDeserializer<std::vector < int > >::deserialize(REMOTING__NAMES[1], true, deser, value.buf_);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.data_);
		TypeDeserializer<Services::Internal >::deserialize(REMOTING__NAMES[3], true, deser, value.internal_);
		TypeDeserializer<float >::deserialize(REMOTING__NAMES[4], true, deser, value.speed_);
		TypeDeserializer<unsigned int >::deserialize(REMOTING__NAMES[5], true, deser, value.velocity_);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Services_LocationDataUnit_INCLUDED

