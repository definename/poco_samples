#include "pch.h"

int main(int argc, char** argv)
{
	try
	{
		Poco::Util::WinRegistryKey rdpPort(
			HKEY_LOCAL_MACHINE,
			"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
			true);

		if (!rdpPort.exists())
			throw(std::runtime_error("Unable to locate current branch"));
		if (!rdpPort.exists("InstallDate"))
			throw(std::runtime_error("Unable to locate InstallDate key"));

		//! Will return value: 1459527521
		//int installDate = rdpPort.getInt("InstallDate");

		//! But we will use hard code by reason of there is no way to get this reg key.
		int installDate(1459527521);

		boost::posix_time::ptime pt(boost::posix_time::not_a_date_time);
		std::time_t t;
		t = 1459527521;
		pt = boost::posix_time::from_time_t(t);
		std::cout << boost::posix_time::to_simple_string(pt) << std::endl;
		std::cout << boost::posix_time::to_iso_string(pt) << std::endl;


		{
			std::string notISO("20160401");
			//! Todo. How to conver this value to ptime?
		}

		{
			std::string iso("20160401T161841");
			boost::posix_time::ptime ptISO(boost::posix_time::from_iso_string(iso));
			std::cout << ptISO << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;

		std::wstringstream error;
		error << L"Error occurred: " << e.what();
		::MessageBox(NULL, error.str().c_str(), L"Error", MB_ICONERROR);
	}

	return 0;
}
