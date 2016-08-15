#include "pch.h"

void _tmain(int argc, TCHAR* argv[])
{
	try
	{
		Poco::Random random;
		random.seed();
		for (int i = 0; i != 10; ++i)
		{
			_tcout << random.next(10) << std::endl;
			//_tcout << (random.nextBool() ? _T("true") : _T("false")) << std::endl;
			//_tcout << random.nextChar() << std::endl;
			//_tcout << random.nextDouble() << std::endl;
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