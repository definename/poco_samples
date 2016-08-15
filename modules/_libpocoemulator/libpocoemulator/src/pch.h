#pragma once

#include "targetver.h"

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <iostream>

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions
//

#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/File.h"
#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Path.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/StreamCopier.h"

#include "Poco/FileStream.h"
#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Parser.h"