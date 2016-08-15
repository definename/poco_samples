#include "pch.h"

class Main : public Poco::Util::Application
{
	int main(const ArgVec& args)
	{
		logger().information("%s", Poco::Environment::osName());
		logger().information("%s", Poco::Environment::osArchitecture());

		return Application::EXIT_OK;
	}
};

POCO_APP_MAIN(Main);