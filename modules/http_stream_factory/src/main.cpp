#include "pch.h"

int main(int argc, char** argv)
{
	try
	{
		Poco::Net::HTTPStreamFactory httpStream_;
		Poco::URI keyLink("http://files.aimprosoft.com/quicktech/server/server.pub");

		std::auto_ptr<std::istream> keyStream(httpStream_.open(keyLink));
		std::string key;
		Poco::StreamCopier::copyToString(*keyStream, key);
		std::cout << key << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Stream request error: " << e.what() << std::endl;
	}

	return 0;
}
