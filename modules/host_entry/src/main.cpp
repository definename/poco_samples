#include "pch.h"

void HostByAddress(const Poco::Net::IPAddress& ip);
void HostByName(const std::string& name);
void ThisHost();

int main(int argc, char* argv[])
{
	try
	{
// 		if (argc < 2)
// 			throw(std::runtime_error("Unknown ip address"));

//		Poco::Net::IPAddress ip(argv[1]);
		Poco::Net::IPAddress ip("192.168.25.1");
		HostByAddress(ip);
		HostByName("google.com");
		ThisHost();
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

void HostByAddress(const Poco::Net::IPAddress& ip)
{
	std::cout << "*** Some address: " << ip.toString() << std::endl;
	Poco::Net::HostEntry& entry = Poco::Net::DNS::hostByAddress(ip);
	std::cout << "Canonical name: " << entry.name() << std::endl;

	const Poco::Net::HostEntry::AliasList& aliases = entry.aliases();
	Poco::Net::HostEntry::AliasList::const_iterator itAlias = aliases.begin();
	for (itAlias; itAlias != aliases.end(); ++itAlias)
		std::cout << "Alias: " << *itAlias << std::endl;

	const Poco::Net::HostEntry::AddressList& address = entry.addresses();
	Poco::Net::HostEntry::AddressList::const_iterator itAddress = address.begin();
	for (itAddress; itAddress != address.end(); ++itAddress)
	{
		std::cout << "Address: " << itAddress->toString() << std::endl;
	}
}

void HostByName(const std::string& name)
{
	std::cout << "*** Some host: " << name << std::endl;

	Poco::Net::HostEntry& entry = Poco::Net::DNS::hostByName(name);
	std::cout << "Canonical name: " << entry.name() << std::endl;

	const Poco::Net::HostEntry::AliasList& aliases = entry.aliases();
	Poco::Net::HostEntry::AliasList::const_iterator itAlias = aliases.begin();
	for (itAlias; itAlias != aliases.end(); ++itAlias)
		std::cout << "Alias: " << *itAlias << std::endl;

	const Poco::Net::HostEntry::AddressList& address = entry.addresses();
	Poco::Net::HostEntry::AddressList::const_iterator itAddress = address.begin();
	for (itAddress; itAddress != address.end(); ++itAddress)
		std::cout << "Address: " << itAddress->toString() << std::endl;
}

void ThisHost()
{
	std::cout << "*** This host: " << Poco::Net::DNS::hostName() << std::endl;
	Poco::Net::HostEntry& entry = Poco::Net::DNS::thisHost();
	std::cout << "Canonical name: " << entry.name() << std::endl;

	const Poco::Net::HostEntry::AddressList& address = entry.addresses();
	Poco::Net::HostEntry::AddressList::const_iterator it = address.begin();
	for (it; it != address.end(); ++it)
		std::cout << "Address: " << it->toString() << std::endl;
}