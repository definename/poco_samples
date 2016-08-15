#include "TimeService.h"
#include "WakeUpTask.h"

namespace Services
{


TimeService::TimeService()
{
}


TimeService::~TimeService()
{
}


Poco::DateTime TimeService::currentTime() const
{
	Poco::DateTime now;
	return now;
}

LocationDataUnit TimeService::GetLocation()
{
	LocationDataUnit loc;
	loc.accuracy_ = 99;
	loc.speed_ = 65;
	loc.buf_ = { 10, 20, 30, 40 };
	loc.velocity_ = 120;
	loc.data_ = "my data";

	loc.internal_.core_ = 100;

// 	for (int i = 0; i != 10; ++i) {
// 		loc.comment[i] = i * 2;
// 	}
	return loc;
}

void TimeService::WakeUp(const Poco::DateTime& time, const std::string& message)
{
	timer_.schedule(new WakeUpTask(*this, message), time.timestamp());
}

} // namespace Services
