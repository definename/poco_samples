#pragma once

namespace libpocoemulator
{

class NullServer : public Poco::Util::ServerApplication
	// poco usage:
	// *.exe /registerService /displayName="RmInstaller" /description="RmInstaller description
	// *.exe /unregisterService
	// *.exe /help
	// *.exe /install_id=3075631c-72dd-11e8-adc0-fa7ae01bbebc /master_id=394b8d36-72dd-11e8-adc0-fa7ae01bbebc /server_ip=192.168.88.221 /server_port=21043

	// sc.exe util usage:
	// sc start <servicename> /install_id=3075631c-72dd-11e8-adc0-fa7ae01bbebc /master_id=394b8d36-72dd-11e8-adc0-fa7ae01bbebc /server_ip=192.168.88.221 /server_port=21043
	// sc stop <servicename>
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	NullServer();
	//! Destructor.
	~NullServer() = default;

	//
	// Protected interface.
	//
protected:
	//! Initializes the application and all registered subsystems.
	void initialize(Poco::Util::Application& self) override;
	//! Uninitializes the application and all registered subsystems.
	void uninitialize() override;
	//! Defines options.
	void defineOptions(Poco::Util::OptionSet& options) override;
	//! The application's main logic.
	int main(const ArgVec& args) override;
	//! Called when the option with the given name is encountered
	void handleOption(const std::string& name, const std::string& value) override;

	//
	// Private data members.
	//
protected:
	//! Help request flag.
	bool helpRequested_;

	//
	// Private interface.
	//
private:
	//! Handles help option.
	void HandleHelp(const std::string& name, const std::string& value);
};

} // namespace libpocoemulator

POCO_SERVER_MAIN(libpocoemulator::NullServer)
