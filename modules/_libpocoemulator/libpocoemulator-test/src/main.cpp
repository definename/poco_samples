#include "pch.h"

int main(int argc, char* argv[], char* env[])
{
	try
	{

	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}