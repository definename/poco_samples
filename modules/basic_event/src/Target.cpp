#include "pch.h"
#include "Target.h"

Target::Target(Poco::Logger& logger)
	: logger_(logger)
{

}

void Target::OnEvent(const void* pSender, int& arg)
{
	logger_.information("Event has been fired: %d", arg);
}