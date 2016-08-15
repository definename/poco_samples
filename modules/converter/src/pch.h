#pragma once

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <iostream>
#include <tchar.h>
#include <sstream>

#ifdef _UNICODE
#define _tcout std::wcout
#define _tcin std::wcin
#define _tstring std::wstring
#define _tcerr std::wcerr
#define _tostream std::wostream
#define _tistream std::wistream
#define _tstringstream std::wstringstream
#define _tifstream std::wifstream
#define _tofstream std::wofstream
#define _tfstream std::wfstream
#define _tostringstream std::wostringstream
#define _tistringstream std::wistringstream
#define _tstringstream std::wstringstream
#else
#define _tcin std::cin
#define _tcout std::cout
#define _tstring std::string
#define _tcerr std::cerr
#define _tostream std::ostream
#define _tistream std::istream
#define _tstringstream std::stringstream
#define _tifstream std::ifstream
#define _tofstream std::ofstream
#define _tfstream std::fstream
#define _tostringstream std::ostringstream
#define _tistringstream std::istringstream
#define _tstringstream std::stringstream
#endif

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions.
//

#include "Poco/TextConverter.h"
#include "Poco/Foundation.h"
#include "Poco/Latin1Encoding.h"
#include "Poco/Windows1250Encoding.h"
#include "Poco/Windows1251Encoding.h"
#include "Poco/Windows1252Encoding.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/StreamConverter.h"

//////////////////////////////////////////////////////////////////////////
// Platform specific includes and definitions.
//

#include <windows.h>