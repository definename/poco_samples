#include "pch.h"
#include "PnpUtilService.h"

namespace nobsod
{

PnpUtilService::PnpUtilService(Poco::Logger& logger)
	: logger_(logger)
{

}

void PnpUtilService::run()
{
	logger_.information("Running...");
}

} // namespace nobsod