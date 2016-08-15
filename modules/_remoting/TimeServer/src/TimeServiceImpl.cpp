#include "pch.h"
#include "TimeServiceImpl.h"

namespace Services
{

void TimeServiceImpl::TimeEvent(const TEvent& timeEvent)
{
	timeEvent_(timeEvent);
}

} // namespace Services
