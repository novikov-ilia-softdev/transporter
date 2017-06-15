#ifndef TEST_H
#define TEST_H

class Test : public ::testing::Test
{
};

TEST_F( Test, 1)
{
	EXPECT_TRUE( 1 == 1);
}

#endif TEST_H
