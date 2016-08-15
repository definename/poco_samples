#pragma once

class CmdApplication : public Poco::Util::Application
	// Usage:
	// *.exe /help
	// *.exe /serverIp=192.168.88.253 /endpoint=buildAgent /fileName=qt-agent.exe /groupId=01cf6bec-590c-11e8-9c2d-fa7ae01bbebc /companyId=1d8ebcd5-780d-49dc-bc2a-e8f19e8f8ac6
	// *.exe /serverIp=192.168.88.253 /endpoint=buildAgent /fileName=qt-agent.exe /companyId=1d8ebcd5-780d-49dc-bc2a-e8f19e8f8ac6
	// *.exe /serverIp=192.168.88.253 /endpoint=buildDownloader /fileName=qt-downloader.exe /groupId=01cf6bec-590c-11e8-9c2d-fa7ae01bbebc /companyId=1d8ebcd5-780d-49dc-bc2a-e8f19e8f8ac6
	// *.exe /serverIp=184.71.52.75 /endpoint=buildAgent /fileName=qt-agent-dev.exe /companyId=fdadb2df-ed3d-4e28-b41e-741617b7ffa6
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
	//! Builds installer.
	void Build(libpocoemulator::types::HttpsSessionPtr httpsSession, const std::string& authToken);
	//! Retrieves auth token.
	std::string GetToken(libpocoemulator::types::HttpsSessionPtr httpsSession);
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
	//! Server ip.
	std::string serverIp_;
	//! Server port.
	int serverPort_;
	//! Company id.
	Poco::UUID companyId_;
	//! Is onetime.
	bool isOnetime_;
	//! Onetime session id.
	Poco::UUID sessionId_;
	//! Endpoint.
	std::string endpoint_;
	//! Destination file name.
	std::string fileName_;
	//! Http server port.
	int httpPort_;
	//! Group id.
	Poco::UUID groupId_;

};

POCO_APP_MAIN(CmdApplication);