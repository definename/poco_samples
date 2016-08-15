#include "pch.h"

class Main : public Poco::Util::Application
{
	int main(const ArgVec& args)
	{
		Poco::Timestamp ts;
		{
			std::string origin("2099-01-01T12:01:01");
			logger().information("%s", origin);

			Poco::DateTime dt;
			int tzd;
			if (!Poco::DateTimeParser::tryParse(Poco::DateTimeFormat::ISO8601_FORMAT, origin, dt, tzd))
			{
				logger().information("Failed to parse!!");
				return Application::EXIT_IOERR;
			}
			ts = dt.timestamp();
		}

		Poco::Timestamp::UtcTimeVal val = ts.utcTime();
		logger().information("%?d", val);

		{
			Poco::DateTime dt(Poco::Timestamp::fromUtcTime(val));

			std::string msg;
			Poco::format(msg, "%d-%02d-%02dT%02d:%02d:%02d",
				dt.year(),
				dt.month(),
				dt.day(),
				dt.hour(),
				dt.minute(),
				dt.second());

			logger().information("%s", msg);
		}

		return Application::EXIT_OK;
	}
};

POCO_APP_MAIN(Main)
