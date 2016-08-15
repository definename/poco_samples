#pragma once

class CmdApplication : public Poco::Util::Application
	// Usage:
	// *.exe /help
	// *.exe /serverIp=192.168.88.253 /companyId=1d8ebcd5-780d-49dc-bc2a-e8f19e8f8ac6 /deviceId=b144ad8e-2c37-45e7-83ee-0c401d941849 /userId=e797c7ce-5a87-11e8-9c2d-fa7ae01bbebc /connectionType=CSS /binPath=<pathtothebinarytorun>
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	CmdApplication();
	//! Destructor.
	~CmdApplication() = default;

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
	// Private interface.
	//
private:
	//! Returns auth token.
	std::string GetToken(libpocoemulator::types::HttpsSessionPtr httpsSession);
	//! Returns remote session id.
	std::string GetSessionId(
		libpocoemulator::types::HttpsSessionPtr httpsSession, const std::string& authToken);
	//! Starts viewer.
	void CmdApplication::Launch(const std::string& sessionId);
	//! Help option handler.
	void HandleHelp(const std::string& name, const std::string& value);
	//! Ip address handler.
	void OptionHandler(const std::string& name, const std::string& value);

	//
	// Private data members.
	//
private:
	//! Help request.
	bool helpRequested_;
	//! Company id.
	Poco::UUID companyId_;
	//! Device id.
	Poco::UUID deviceId_;
	//! User id.
	Poco::UUID userId_;
	//! Session type.
	std::string sessionType_;
	//! Server ip.
	std::string serverIp_;
	//! Server port.
	int serverPort_;
	//! Http server port.
	int httpPort_;
	//! Viewer path.
	Poco::Path viewerPath_;
};

POCO_APP_MAIN(CmdApplication);