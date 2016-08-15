#pragma once

class HTTPSServer: public Poco::Util::ServerApplication
	/// The main application class.
	///
	/// This class handles command-line arguments and
	/// configuration files.
	/// Start the HTTPTimeServer executable with the help
	/// option (/help on Windows, --help on Unix) for
	/// the available command line options.
	///
	/// To use the sample configuration file (HTTPTimeServer.properties),
	/// copy the file to the directory where the HTTPTimeServer executable
	/// resides. If you start the debug version of the HTTPTimeServer
	/// (HTTPTimeServerd[.exe]), you must also create a copy of the configuration
	/// file named HTTPTimeServerd.properties. In the configuration file, you
	/// can specify the port on which the server is listening (default
	/// 9443) and the format of the date/time string sent back to the client.
	///
	/// To test the TimeServer you can use any web browser (https://localhost:9443/).
{
public:
	//! Constructor.
	HTTPSServer();
	//! Destructor.
	~HTTPSServer();

protected:
	//! Initializes server.
	void initialize(Poco::Util::Application& self);
	//! Unitializes server.
	void uninitialize();
	//! Defines options.
	void defineOptions(Poco::Util::OptionSet& options);
	//! Handles option.
	void handleOption(const std::string& name, const std::string& value);
	//! Displays help.
	void displayHelp();
	//! Server main function.
	int main(const std::vector<std::string>& args);

private:
	//! Is help request.
	bool helpRequested_;
	//! Contains the name of the private key file used for encryption.
	const std::string privateKeyName_;
	//! Contains the name of the certificate file (in PEM format).
	const std::string certificateName_;
};