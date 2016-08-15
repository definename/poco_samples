#pragma once

class ScopedLog
{
public:
	ScopedLog(Poco::Logger& logger, const std::string& msg)
		: logger_(logger)
		, msg_(msg) {
		logger_.information("==> %s", msg_);
	}
	~ScopedLog() {
		logger_.information("<== %s", msg_);
	}

private:
	Poco::Logger& logger_;
	std::string msg_;
};