#include "pch.h"

//! Iterate json array.
void IterateArray(const Poco::JSON::Array::Ptr& arr);
//! Iterate json object.
void IterateObject(const Poco::JSON::Object::Ptr& obj);
//! Processes dynamic value.
void Process(const Poco::Dynamic::Var& var);

int main(int argc, char* argv[], char* env[])
{
	try
	{
		Poco::JSON::Object::Ptr obj = new Poco::JSON::Object();
		{
			// Array.
			Poco::JSON::Array::Ptr arr = new Poco::JSON::Array();
			for (int i = 0; i != 3; ++i)
			{
				arr->add(i);
			}
			obj->set("arr", arr);

			// Key/val array.
			Poco::JSON::Array::Ptr keyArr = new Poco::JSON::Array();
			for (int i = 0; i != 3; ++i)
			{
				Poco::JSON::Object::Ptr obj = new Poco::JSON::Object();
				obj->set("key", "value");
				keyArr->add(obj);
			}
			obj->set("keyval", keyArr);

			// Sub object.
			Poco::JSON::Object::Ptr subobj = new Poco::JSON::Object();
			subobj->set("subkey", "subval");
			obj->set("subobj", subobj);
		}
		obj->stringify(std::cout, 1, 1);

		std::cout << std::endl;

		{
			IterateObject(obj);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}

	return 0;
}

void Process(const Poco::Dynamic::Var& var)
{
	if (var.isInteger())
	{
		std::cout << var.extract<int>() << std::endl;
	}
	else if (var.isString())
	{
		std::cout << var.extract<std::string>() << std::endl;
	}
	else
	{
		std::cout << "Unsupported type" << std::endl;
	}
}

void IterateObject(const Poco::JSON::Object::Ptr& obj)
{
	std::vector<std::string> names;
	obj->getNames(names);
	for (const auto& name : names)
	{
		if (obj->isArray(name))
		{
			std::cout << "\t" << name << "[]:" << std::endl;
			IterateArray(obj->getArray(name));
		}
		else if (obj->isObject(name))
		{
			std::cout << "\t" << name << ":" << std::endl;
			IterateObject(obj->getObject(name));
		}
		else if (obj->isNull(name))
		{
			std::cout << name << " : null" << std::endl;
		}
		else
		{
			std::cout << name << " : ";
			Process(obj->get(name));
		}
	}
}

void IterateArray(const Poco::JSON::Array::Ptr& arr)
{
	for (int i = 0; i != arr->size(); ++i)
	{
		if (arr->isObject(i))
		{
			IterateObject(arr->getObject(i));
		}
		else if (arr->isArray(i))
		{
			IterateArray(arr->getArray(i));
		}
		else if (arr->isNull(i))
		{
			std::cout << i << " : null" << std::endl;
		}
		else
		{
			Process(arr->get(i));
		}
	}
}