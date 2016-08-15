//
// TEventDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeDeserializer_Services_TEvent_INCLUDED
#define TypeDeserializer_Services_TEvent_INCLUDED


#include "Poco/RemotingNG/TypeDeserializer.h"
#include "TimeService.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Services::TEvent>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Services::TEvent& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Services::TEvent& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"timeEvent","timeStatus"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.timeEvent_);
		int gentimeStatus_;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, deser, gentimeStatus_);
		if (ret) value.timeStatus_ = static_cast<Services::TStatus>(gentimeStatus_);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Services_TEvent_INCLUDED

