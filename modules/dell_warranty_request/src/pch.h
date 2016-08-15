#pragma once

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include "iostream"

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions.
//

#include "Poco/Net/HTTPSClientSession.h"
//#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

using Poco::Net::HTTPSClientSession;
//using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

//////////////////////////////////////////////////////////////////////////
// Boost includes and definitions.
//

#include "boost/exception/all.hpp"
#include "boost/format.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/time_parsing.hpp"