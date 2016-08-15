#pragma once

class Target
{
public:
	//! Constructor.
	Target(Poco::Logger& logger);
	//! Destructor.
	~Target() = default;

	//
	// Public interface.
	//
public:
	//! Event handler.
	void OnEvent(const void* pSender, int& arg);

private:
	//! Logger reference.
	Poco::Logger& logger_;
};