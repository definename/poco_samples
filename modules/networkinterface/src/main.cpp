#include "pch.h"

int main(int argc, TCHAR* argv[])
{
	try
	{
		Poco::Net::NetworkInterface::Map map = Poco::Net::NetworkInterface::map();
		for (const Poco::Net::NetworkInterface::Map::value_type& val : map)
		{
			std::cout << "***" << std::endl;
			std::cout << "Adapter index: " << val.first << std::endl;

			const Poco::Net::NetworkInterface& interface = val.second;
			std::cout << interface.adapterName() << std::endl;
			std::cout << interface.address().toString() << std::endl;
			std::cout << interface.displayName() << std::endl;
			std::cout << interface.broadcastAddress().toString() << std::endl;
			//std::cout << interface.destAddress().toString() << std::endl;
			std::cout << "Index: " << interface.index() << std::endl;
			std::cout << "Is loopback: " << interface.isLoopback() << std::endl;
			std::cout << "Is point-to-point: " << interface.isPointToPoint() << std::endl;
			std::cout << "Is running: " << interface.isRunning() << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;

		std::wstringstream error;
		error << L"Error: " << e.what();
		::MessageBox(NULL, error.str().c_str(), L"Error corrupted", MB_ICONERROR);
	}

	return 0;
}