#include "pch.h"

void _tmain(int argc, TCHAR* argv[])
{
	try
	{
		HKEY root = HKEY_LOCAL_MACHINE;
		std::string sid("S-1-5-21-1917061056-2319448781-3348045073-1000");
		std::string subKey(/*sid + */"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\");
		Poco::Util::WinRegistryKey key(root, subKey, true, KEY_WOW64_32KEY/*KEY_WOW64_64KEY*/);

		Poco::Util::WinRegistryKey::Keys keys;
		if (key.exists())
		{
			key.subKeys(keys);
		}
	}
	catch (const std::exception& e)
	{
		_tcout << _T("Error occurred: ") << e.what() << std::endl;
		
		_tostringstream error;
		error << L"Error: " << e.what();
		::MessageBox(NULL, error.str().c_str(), L"Error occurred", MB_ICONERROR);
	}
}