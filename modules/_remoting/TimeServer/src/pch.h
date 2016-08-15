#pragma once

#include "targetver.h"

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <sstream>

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions
//

#include "Poco/Delegate.h"
#include "Poco/BasicEvent.h"
#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/Timer.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/SOAP/Listener.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/RemotingNG/TCP/TransportFactory.h"
#include "Poco/RemotingNG/TCP/Connection.h"