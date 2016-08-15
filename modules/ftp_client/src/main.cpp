#include "pch.h"
#include "FTPClient.h"

void _tmain(int argc, TCHAR* argv[])
{
	try
	{
		const std::string ftpServer("178.150.81.242");
		Poco::Net::IPAddress ip(ftpServer, Poco::Net::IPAddress::Family::IPv4);
		Poco::Net::SocketAddress ftpAddress(ip, Poco::Net::FTPClientSession::FTP_PORT);

		Poco::AutoPtr<ftp::FTPClient> ftpClient = new ftp::FTPClient(
			ftpAddress, "definename", "definepassword");

		ftpClient->Connect();
		//ftpClient->List();
		//ftpClient->Download();
		//ftpClient->Upload();

		MSG msg;
		while (!GetMessage(&msg, NULL, NULL, NULL))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	catch (const Poco::Exception& e)
	{
		std::wstring message;
		Poco::UnicodeConverter::toUTF32(e.displayText(), message);

		_tcerr << "POCO Error occurred: " << message << std::endl;

		_tostringstream error;
		error << _T("Error: ") << message;
		::MessageBox(NULL, error.str().c_str(), _T("POCO Error occurred"), MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		std::wstring message;
		Poco::UnicodeConverter::toUTF32(e.what(), message);

		_tcerr << "Error occurred: " << message << std::endl;

		_tostringstream error;
		error << _T("Error: ") << message;
		::MessageBox(NULL, error.str().c_str(), _T("Error occurred"), MB_ICONERROR);
	}
}