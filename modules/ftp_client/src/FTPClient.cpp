#include "pch.h"
#include "FTPClient.h"

namespace ftp
{

FTPClient::FTPClient(
	const Poco::Net::SocketAddress& address,
	const std::string& username,
	const std::string& password)
	: address_(address)
	, ftpSession_(new Poco::Net::FTPClientSession())
	, password_(password)
	, username_(username)
{ }

FTPClient::~FTPClient()
{
	try
	{
		if (ftpSession_->isLoggedIn())
		{
			ftpSession_->logout();
			_tcout << _T("Logged out...") << std::endl;
		}
		if (ftpSession_->isOpen())
		{
			ftpSession_->close();
			_tcout << _T("Session has been closed") << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		_tcout << _T("Session destruction error: ") << e.what();
	}
}

FTPClient::Directory::DirList FTPClient::GetDirList() const
{
	return workDir_.list_;
}

void FTPClient::ChangeWorkDir(const std::string& path)
{
	ftpSession_->setWorkingDirectory(path);
	List();
}

void FTPClient::Connect()
{
	ftpSession_->setPassive(true);
	ftpSession_->open(address_.host().toString(), address_.port());
	_tcout << "Connection has been opened" << std::endl;

	ftpSession_->login(username_, password_);
	_tcout << "Logged in..." << std::endl;

	ftpSession_->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
}

void FTPClient::Download()
{
	std::string source("/ITOY_METKA/ftp/user.png");
	std::string dest("d:/user.png");

	//! First way.
	// 	std::istream& data = ftpSession_->beginDownload(source);
	// 	Poco::FileOutputStream fstream(dest, std::ios::out | std::ios::trunc | std::ios::binary);
	// 	for (char byte = data.get(); !data.eof(); byte = data.get())
	// 	{
	// 		fstream << byte;
	// 	}
	// 	ftpSession_->endDownload();

	//! Second way.
	
	std::ofstream ofstr;
	ofstr.open(dest, std::ofstream::out | std::ofstream::binary);
	if (!ofstr.is_open())
		throw std::runtime_error("Unable to open destination file");

	std::istream& istr = ftpSession_->beginDownload(source);
	Poco::StreamCopier::copyStreamUnbuffered(istr, ofstr);
	ftpSession_->endDownload();
}

void FTPClient::Upload()
{
	std::string source("d:/user.png");
	std::string dest("/ITOY_METKA/ftp/user.png");

	std::ifstream ifstr;
	ifstr.open(source, std::ofstream::in | std::ofstream::binary);
	if (!ifstr.is_open())
		throw std::runtime_error("Unable to open source file");

	std::ostream& ostr = ftpSession_->beginUpload(dest);
	Poco::StreamCopier::copyStreamUnbuffered(ifstr, ostr);
	ftpSession_->endUpload();
}

void FTPClient::List()
{
	workDir_.root_ = ftpSession_->getWorkingDirectory();
	std::cout << workDir_.root_ << std::endl;

	std::istream& is = ftpSession_->beginList(workDir_.root_, false);

	if (!workDir_.list_.empty())
		workDir_.list_.clear();

	std::string path;
	while (std::getline(is, path))
	{
		std::cout << path << std::endl;
		workDir_.list_.push_back(path);
	}

	ftpSession_->endList();
}

}