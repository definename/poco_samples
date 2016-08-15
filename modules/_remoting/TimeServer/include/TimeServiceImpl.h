#ifndef TimeServiceImpl_INCLUDED
#define TimeServiceImpl_INCLUDED

#include "TimeService.h"

namespace Services
{

class TimeServiceImpl : public TimeService
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	TimeServiceImpl() = default;
	//! Destructor.
	~TimeServiceImpl() = default;
	
	//
	// Public interface.
	//
public:
	//! Time event handler.
	void TimeEvent(const TEvent& timeEvent) override;

public:
	//! Time event.
	Poco::BasicEvent<const TEvent> timeEvent_;
	//! Reset time event.
	Poco::BasicEvent<const bool> resetTimeEvent_;
};

} // namespace Services


#endif // TimeServiceImpl_INCLUDED
