#include "pch.h"
#include "HTTPSServer.h"

int main(int argc, char** argv)
{
	HTTPSServer server;
	return server.run(argc, argv);
}