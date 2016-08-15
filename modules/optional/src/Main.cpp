#include "pch.h"

class Main : public Poco::Util::Application
{
	int main(const ArgVec& args)
	{
		Poco::Optional<std::string> var;
		if (!var.isSpecified()) {
			logger().information("var was not specified");
		}

		try {
			var.value();
		}
		catch (Poco::NullValueException& e) {
			logger().error("var access error display text: %s", e.displayText());
		}

		logger().information("default var: %s", var.value("default"));
		logger().information("assign var: %s", var.assign("assigned").value());

		return Application::EXIT_OK;
	}
};

POCO_APP_MAIN(Main);