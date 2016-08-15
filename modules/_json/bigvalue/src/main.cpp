#include "pch.h"

int main(int argc, char* argv[], char* env[])
{
	try
	{
		{
			std::string json = "{ \"bigvalue\": 17170489344 }";

			Poco::JSON::Parser parser;
			Poco::JSON::Object::Ptr obj = parser.parse(json).extract<Poco::JSON::Object::Ptr>();

			Poco::Dynamic::Var var = obj->get("bigvalue");
			Poco::Int64 big = Poco::NumberParser::parse64(var.toString());
			std::cout << big << std::endl;
		}

		{
			std::string strNum("17170489344");
			Poco::Int64 realNum = Poco::NumberParser::parse64(strNum);
			std::cout << realNum + 1 << std::endl;
		}

	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}

	return 0;
}