#ifndef TEST_H
#define TEST_H

#include <fstream>

class Test : public ::testing::Test
{
public:
	static void runTCPServer()
	{
		system( "../../build/src/transporter -s 12345 tcp &");
		sleep( 1);
	}

	static void runTCPClient()
	{
		system( "../../build/src/transporter -c 127.0.0.1 12345 tcp ../../src/main.cpp");
	}

	static void runUDPServer()
	{
		system( "../../build/src/transporter -s 12345 udp &");
		sleep( 1);
	}

	static void runUDPClient()
	{
		system( "../../build/src/transporter -c 127.0.0.1 12345 udp ../../src/main.cpp");
		sleep( 1);
	}

	static void stopAll()
	{
		system( "killall -15 transporter");
	}

	static void compareFiles()
	{
		std::ifstream srcFile( "../../src/main.cpp");
		std::string srcFileContent( (std::istreambuf_iterator<char>(srcFile)), (std::istreambuf_iterator<char>()));

		std::ifstream dstFile( "main.cpp");
		std::string dstFileContent( (std::istreambuf_iterator<char>(dstFile) ),(std::istreambuf_iterator<char>()    ) );

		EXPECT_TRUE( srcFileContent == dstFileContent);
	}

	static void deleteDstFile()
	{
		system( "rm main.cpp");
	}
};

TEST_F( Test, tcp)
{
	Test::runTCPServer();
	Test::runTCPClient();
	Test::stopAll();
	Test::compareFiles();
	Test::deleteDstFile();

}

TEST_F( Test, udp)
{
	Test::runUDPServer();
	Test::runUDPClient();
	Test::stopAll();
	Test::compareFiles();
	Test::deleteDstFile();
}

#endif // TEST_H
