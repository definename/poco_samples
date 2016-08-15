//
// InternalDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeDeserializer_Services_Internal_INCLUDED
#define TypeDeserializer_Services_Internal_INCLUDED


#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Types.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Services::Internal>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Services::Internal& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Services::Internal& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"core"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[0], true, deser, value.core_);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Services_Internal_INCLUDED

