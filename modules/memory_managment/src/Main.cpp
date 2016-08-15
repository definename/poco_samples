#include "pch.h"
#include "RCO.h"
#include "InfoCenter.h"

class ScopedLog
{
public:
	ScopedLog(Poco::Logger& logger, const std::string& msg)
		: logger_(logger)
		, msg_(msg) {
		logger_.information("%s ->", msg_);
	}
	~ScopedLog() {
		logger_.information("%s <-", msg_);
	}

private:
	Poco::Logger& logger_;
	std::string msg_;
};

class Main : public Poco::Util::Application
{
	int main(const ArgVec& args)
	{
		// Initializes console logger.
		Poco::AutoPtr<Poco::FormattingChannel> channel(new Poco::FormattingChannel);
		channel->setChannel(new Poco::ConsoleChannel());
		channel->setFormatter(new Poco::PatternFormatter("%d/%m/%Y %H:%M:%S,%i [%p] %t"));
		logger().setChannel(channel);

		{
			Poco::AutoPtr<RCO> obj(new RCO(logger()));
			obj->Boom();
		}

		Poco::SharedPtr<std::string> str = new std::string("SharedPtr");
		logger().information("%s length: %s", *str, std::to_string(str->length()));

		// Casting test
		{
			ScopedLog log(logger(), "Poco::SharedPtr Cast");

			Poco::SharedPtr<B> b(new B);
			b->nameB_ = "BName";
			b->nameA_ = "AName";

			InfoCenter::GetInstance().aPtr_ = b;
			{
				Poco::SharedPtr<B> castB = InfoCenter::GetInstance().aPtr_.cast<B>();
				if (castB.isNull()) {
					logger().information("castB is null");
				}
				logger().information(castB->nameB_);
				castB->nameA_ = "(new)AName";
			}
			logger().information("%s", InfoCenter::GetInstance().aPtr_->nameA_);
		}

		return Application::EXIT_OK;
	}
};

POCO_APP_MAIN(Main);