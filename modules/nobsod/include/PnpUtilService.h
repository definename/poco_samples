#pragma once

#include "Service.h"

namespace nobsod
{

class PnpUtilService : public Service
{
public:
	//! Constructor.
	PnpUtilService(Poco::Logger& logger);
	//! Destructor.
	~PnpUtilService();

public:
	//! Do whatever the service needs to do.
	void run() override;
};

} // namespace nobsod
