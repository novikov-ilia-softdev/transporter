#ifndef TEST_H
#define TEST_H

#include <fstream>

class Test : public ::testing::Test
{
};

/*
TODO:
1) short path
2) system -> boost_process
3) create file
4) compare file
5) delete file
*/

TEST_F( Test, tcp)
{
	system( "~/workspace/transporter/build/src/transporter -s 12345 tcp &");
	sleep( 1);
	system( "~/workspace/transporter/build/src/transporter -c 127.0.0.1 12345 tcp ~/workspace/transporter/src/main.cpp");
	system( "killall -15 transporter");

	std::ifstream srcFile( "/home/ilia-novikov/workspace/transporter/src/main.cpp");
	std::string srcFileContent( (std::istreambuf_iterator<char>(srcFile)), (std::istreambuf_iterator<char>()));

	std::ifstream dstFile( "main.cpp");
	std::string dstFileContent( (std::istreambuf_iterator<char>(dstFile) ),(std::istreambuf_iterator<char>()    ) );

	EXPECT_TRUE( srcFileContent == dstFileContent);
	system( "rm main.cpp");
}

TEST_F( Test, udp)
{
	system( "~/workspace/transporter/build/src/transporter -s 12345 udp &");
	sleep( 1);
	system( "~/workspace/transporter/build/src/transporter -c 127.0.0.1 12345 udp ~/workspace/transporter/src/main.cpp");
	sleep( 1);
	system( "killall -15 transporter");

	std::ifstream srcFile( "/home/ilia-novikov/workspace/transporter/src/main.cpp");
	std::string srcFileContent( (std::istreambuf_iterator<char>(srcFile)), (std::istreambuf_iterator<char>()));

	std::ifstream dstFile( "main.cpp");
	std::string dstFileContent( (std::istreambuf_iterator<char>(dstFile) ),(std::istreambuf_iterator<char>()    ) );

	EXPECT_TRUE( srcFileContent == dstFileContent);
	system( "rm main.cpp");
}

#endif // TEST_H
