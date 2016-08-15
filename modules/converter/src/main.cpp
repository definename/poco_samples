#include "pch.h"

std::wstring CUTOCW(const std::string& in)
{
	Poco::Windows1251Encoding decoder;
	Poco::UTF8Encoding encoder;

	Poco::TextConverter converter(decoder, encoder);

	std::string utf8;
	converter.convert(in, utf8);

	std::wstring out;
	Poco::UnicodeConverter::toUTF32(utf8, out);

	return out;
}

#define CU2CW(str)  CUTOCW(str).c_str()

void _tmain(int argc, TCHAR* argv[])
{
	try
	{
		setlocale(LC_CTYPE, "rus");
		std::cout << "русский текст" << std::endl;
		std::wcout << L"русский текст" << std::endl;
		throw std::runtime_error("русский текст");

		MSG msg;
		while (!GetMessage(&msg, NULL, NULL, NULL))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	catch (const std::exception& e)
	{
		std::wcerr << L"Error occurred: " << CU2CW(e.what()) << std::endl;
		
		std::wostringstream error;
		error << L"Error: " << CU2CW(e.what());
		::MessageBox(NULL, error.str().c_str(), L"Error occurred", MB_ICONERROR);
	}
}