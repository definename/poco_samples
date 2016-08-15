#pragma once

#include "targetver.h"

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <iostream>
#include <vector>
#include <thread>

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions
//

#include "Poco/Delegate.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/RemotingNG/SOAP/TransportFactory.h"
#include "Poco/RemotingNG/TCP/TransportFactory.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/Util/ServerApplication.h"