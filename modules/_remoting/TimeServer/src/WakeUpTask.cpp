#include "pch.h"
#include "WakeUpTask.h"
#include "TimeService.h"

namespace Services
{

WakeUpTask::WakeUpTask(TimeService& owner, const std::string& message)
	: owner_(owner)
	, message_(message)
{
}

void WakeUpTask::run()
{
	owner_.wakeUp_(this, message_);
}



} // namespace Services