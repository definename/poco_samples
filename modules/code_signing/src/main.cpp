#include "pch.h"

// Signtool.exe usage example:
// signtool.exe sign /f cert.p12 /p password /d "description" targetfile.exe

int main(int argc, char** argv)
{
	try
	{
		Poco::Path certPath(argv[0], Poco::Path::PATH_WINDOWS);
		certPath.makeParent();
		certPath.setFileName("cert.p12");

		std::string a;
		std::string desc("description");
		std::string targetFile("D:/targetfile.exe");
		Poco::format(a, "sign /f %s /p allthetime /d \"%s\" \"%s\"", certPath.toString(), desc, targetFile);

		std::cout << certPath.toString() << std::endl;

		Poco::Process::Args args;
		args.push_back(a);
		Poco::ProcessHandle handler = Poco::Process::launch("signtool", args);
		std::cout << "Exit code: " << handler.wait() << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}

	return 0;
}
