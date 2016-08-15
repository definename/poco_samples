#pragma once

namespace nobsod
{

class PnpUtilService : public Poco::Runnable
{
public:
	//! Constructor.
	PnpUtilService(Poco::Logger& logger);
	//! Destructor.
	~PnpUtilService() = default;

public:
	// Do whatever the service needs to do.
	void run() override;

private:
	Poco::Logger& logger_;
};

} // namespace nobsod
