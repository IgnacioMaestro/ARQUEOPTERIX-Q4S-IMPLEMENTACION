#include "gtest/gtest.h"

#include "..\Q4SCommon\Q4SMessage.h"
#include "..\Q4SCommon\Q4SMessageTools.h"

TEST(Q4SMessageTools_test_case, testQ4SMessageTools_is200OKMessageCorrect)
{
	bool check = Q4SMessageTools_is200OKMessage(Q4SMessage_create200OKBeginResponse(3));

	EXPECT_EQ(check, true);
}

TEST(Q4SMessageTools_test_case, testQ4SMessageTools_is200OKMessageNotCorrect)
{
	bool check = Q4SMessageTools_is200OKMessage(Q4SMessage_createResponse(Q4SRESPONSECODE_3XX, "OK 3"));

	EXPECT_EQ(check, false);
}

TEST(Q4SMessageTools_test_case, testQ4SMessageTools_isPingMessageCorrect)
{
	int pingNumber;
	unsigned long timeStamp;
	bool check = Q4SMessageTools_isPingMessage(Q4SMessage_createRequest(Q4SMTYPE_PING, "host", "1234"), &pingNumber, &timeStamp);

	EXPECT_EQ(check, true);
}

TEST(Q4SMessageTools_test_case, testQ4SMessageTools_isPingMessageNotCorrect)
{
	int pingNumber;
	unsigned long timeStamp;
	bool check = Q4SMessageTools_isPingMessage(Q4SMessage_createBegin("host", "1234"), &pingNumber, &timeStamp);

	EXPECT_EQ(check, false);
}

TEST(Q4SMessageTools_test_case, testQ4SMessageTools_isBandWidthMessageCorrect)
{
	int pingNumber;
	bool check = Q4SMessageTools_isBandWidthMessage(Q4SMessage_createRequest(Q4SMTYPE_BWIDTH, "host", "1234"), &pingNumber);

	EXPECT_EQ(check, true);
}

TEST(Q4SMessageTools_test_case, testQ4SMessageTools_isBandWidthMessageNotCorrect)
{
	int pingNumber;
	bool check = Q4SMessageTools_isBandWidthMessage(Q4SMessage_createBegin("host", "1234"), &pingNumber);

	EXPECT_EQ(check, false);
}

