#ifndef TimeService_INCLUDED
#define TimeService_INCLUDED

#include "Poco/Foundation.h"
#include "Poco/DateTime.h"
#include "Poco/BasicEvent.h"
#include "Poco/Util/Timer.h"
#include "Types.h"

#include <vector>

namespace Services
{

typedef unsigned int uint32_t;

enum TStatus
{
	GOOD = 0,
	BETTER = 1,
	THEBEST = 2
};

//@ serialize
struct TEvent
{
	std::string timeEvent_;
	TStatus timeStatus_;
};

//@ serialize
struct LocationDataUnit
{
	float speed_;
	float accuracy_;
	//int comment[64];
	std::vector<int> buf_;
	uint32_t velocity_;
	std::string data_;
	Internal internal_;
};


//@ remote, namespace="http://www.appinf.com/webservices/TimeService/"
class TimeService
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	TimeService();
	//! Destructor.
	virtual ~TimeService();
	
	//
	// Public interface.
	//
public:
	//! Returns current timer.
	Poco::DateTime currentTime() const;
	//! Returns location.
	LocationDataUnit GetLocation();
	//! Schedules a wakeup call.
	void WakeUp(const Poco::DateTime& time, const std::string& message);
	//! Time event handler.
	virtual void TimeEvent(const TEvent& timeEvent) = 0;

	//
	// Public data members.
	//
public:
	//! Wake up event.
	Poco::BasicEvent<const std::string> wakeUp_;

	//
	// Private data members.
	//
private:
	//! Wake up timer.
	Poco::Util::Timer timer_;
};


} // namespace Services


#endif // TimeService_INCLUDED
