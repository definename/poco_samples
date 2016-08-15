#pragma once

namespace ftp
{

class FTPClient : public Poco::RefCountedObject
{
	//
	// Construction
	//
public:
	//! Constructor.
	FTPClient(
		const Poco::Net::SocketAddress& address,
		const std::string& username,
		const std::string& password);

	//
	// Destruction.
	//
private:
	//! Destructor.
	~FTPClient();

	//
	// Public types.
	//
public:
	//! FTP session pointer type.
	typedef Poco::SharedPtr<Poco::Net::FTPClientSession> FTPSessionPtr;
	//! Directory entry
	struct Directory
	{
		//! Directory list type.
		typedef std::list<std::string> DirList;
		//! Directory root.
		std::string root_;
		//! Directory list.
		DirList list_;
	};

	//
	// Public interface.
	//
public:
	//! Connects to the server.
	void Connect();
	//! Downloads a directory listing.
	void List();
	//! Changes working directory.
	void ChangeWorkDir(const std::string& path);
	//! Returns listing of current directory.
	Directory::DirList GetDirList() const;
	//! Downloads.
	void Download();
	//! Uploads file.
	void Upload();

	//
	// Private interface.
	//
private:
	//! Initializes.
	void Initialize();

	//
	// Private data members.
	//
private:
	//! FTP server address.
	const Poco::Net::SocketAddress address_;
	//! FTP session pointer.
	FTPSessionPtr ftpSession_;
	//! User password.
	const std::string password_;
	//! User name.
	const std::string username_;
	//! Working directory.
	Directory workDir_;
};

} // ftp