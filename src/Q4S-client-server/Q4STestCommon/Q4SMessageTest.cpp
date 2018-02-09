#include "gtest/gtest.h"

#include "..\Q4SCommon\Q4SMessage.h"
#include "..\Q4SCommon\Q4SMessageTools.h"
#include "..\Q4SCommon\Q4SStructs.h"

TEST(Q4SMessage_test_case, testQ4SMessage200OKResponse)
{
	std::string message = Q4SMessage_create200OKBeginResponse();
	std::string compare = "Q4S/1.0 200 OK\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage200OKResponseWithPingNumber)
{
	std::string message = Q4SMessage_create200OKBeginResponse(3);

	std::string compare = "Q4S/1.0 200 OK 3\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createPing)
{
	std::string message = Q4SMessage_createPing("myIp", "12345", 0, 13);

	std::string compare = "PING q4s://myIp:12345 Q4S/1.0\nSequence-Number:0\nTimestamp:13\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createPingWithMeasurments)
{
	Q4SMeasurementValues values;
	values.latency = 1.1f;
	values.jitter= 2.2f;
	values.bandwidth = 3.3f;
	values.packetLoss = 4.4f;
	std::string message = Q4SMessage_createPing("myIp", "12345", 0, 13,	values);

	std::string compare = "PING q4s://myIp:12345 Q4S/1.0\nSequence-Number:0\nTimestamp:13\nMeasurements: l=1.1, j=2.2, pl=4.4, bw=3.3\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createBWidth)
{
	std::string message = Q4SMessage_createBWidth("myIp", "12345", 0);

	std::string compare = "BWIDTH q4s://myIp:12345 Q4S/1.0\nSequence-Number:0\n\n";
	Q4SMessageTools_fillBodyToASize(compare, 1024);

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createBegin)
{
	std::string message = Q4SMessage_createBegin("myIp", "12345");

	std::string compare = "BEGIN q4s://myIp:12345 Q4S/1.0\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, Q4SMessage_createReady)
{
	std::string message = Q4SMessage_createReady("myIp", "12345", 1);

	std::string compare = "READY q4s://myIp:12345 Q4S/1.0\nStage:1\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_create200OKBeginResponse)
{
	std::string message = Q4SMessage_create200OKBeginResponse();
	std::string compare = "Q4S/1.0 200 OK\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_create200OKBeginResponseWithSequenceNumber)
{
	std::string message = Q4SMessage_create200OKBeginResponse(3);

	std::string compare = "Q4S/1.0 200 OK 3\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_create200OKBeginResponseSDP)
{
	Q4SSDPParams params;
	params.qosLevelUp = 0;
	params.qosLevelDown = 1;
	params.q4SSDPAlertingMode = Q4SSDPALERTINGMODE_REACTIVE;
	params.alertPause = 2;
	params.recoveryPause = 3;
	std::string message = Q4SMessage_create200OKBeginResponse(params);

	std::string compare = "Q4S/1.0 200 OK\n\na=qos-level:0/1\na=alerting-mode:Reactive\na=alert-pause:2\na=recovery-pause:3\na=latency:3435973836\na=jitter:3435973836/3435973836\na=bandwidth:3435973836/3435973836\na=packetloss:-1.07374e+008/-1.07374e+008\na=measurement:procedure default(3435973836/3435973836,3435973836/3435973836,3435973836,3435973836/3435973836,3435973836/3435973836)\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createResponse)
{
	std::string message = Q4SMessage_createResponse(Q4SRESPONSECODE_200, "ReasonPhrase test");

	std::string compare = "Q4S/1.0 200 ReasonPhrase test\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createRequestWithoutMeasurements)
{
	std::string message = Q4SMessage_createRequest(Q4SMTYPE_BEGIN, "myIp", "12345", true, 0, true, 12, true, 1 , false);

	std::string compare = "BEGIN q4s://myIp:12345 Q4S/1.0\nSequence-Number:0\nTimestamp:12\nStage:1\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createRequest)
{
	Q4SMeasurementValues values;
	values.latency = 1.1f;
	values.jitter= 2.2f;
	values.bandwidth = 3.3f;
	values.packetLoss = 4.4f;
	std::string message = Q4SMessage_createRequest(Q4SMTYPE_BEGIN, "myIp", "12345", true, 0, true, 12, true, 1, true, &values);

	std::string compare = "BEGIN q4s://myIp:12345 Q4S/1.0\nSequence-Number:0\nTimestamp:12\nStage:1\nMeasurements: l=1.1, j=2.2, pl=4.4, bw=3.3\n\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createRequest_withSDP)
{
	Q4SSDPParams params;
	params.qosLevelUp = 0;
	params.qosLevelDown = 1;
	params.q4SSDPAlertingMode = Q4SSDPALERTINGMODE_REACTIVE;
	params.alertPause = 2;
	params.recoveryPause = 3;
	params.latency = 4;
	params.jitterUp = 5;
	params.jitterDown = 6;
	params.bandWidthUp = 7;
	params.bandWidthDown = 8;
	params.packetLossUp = 9.9f;
	params.packetLossDown = 1.1f;
	params.procedure.negotiationTimeBetweenPingsUplink = 2;
	params.procedure.negotiationTimeBetweenPingsDownlink = 3;
	params.procedure.continuityTimeBetweenPingsUplink = 4;
	params.procedure.continuityTimeBetweenPingsDownlink = 5;
	params.procedure.bandwidthTime = 6;
	params.procedure.windowSizeLatencyCalcUplink = 7;
	params.procedure.windowSizeLatencyCalcDownlink = 8;
	params.procedure.windowSizePacketLossCalcUplink = 9;
	params.procedure.windowSizePacketLossCalcDownlink = 1;
	std::string message = Q4SMessage_createRequest_withSDP(Q4SMTYPE_BEGIN, "myIp", "12345", true, 0, true, 12, true, 1, params);

	std::string compare = "BEGIN q4s://myIp:12345 Q4S/1.0\nSequence-Number:0\nTimestamp:12\nStage:1\n\na=qos-level:0/1\na=alerting-mode:Reactive\na=alert-pause:2\na=recovery-pause:3\na=latency:4\na=jitter:5/6\na=bandwidth:7/8\na=packetloss:9.9/1.1\na=measurement:procedure default(2/3,4/5,6,7/8,9/1)\n";

	EXPECT_EQ(compare, message);
}

TEST(Q4SMessage_test_case, testQ4SMessage_createRequest_withSDP_Without_headers)
{
	Q4SSDPParams params;
	params.qosLevelUp = 0;
	params.qosLevelDown = 1;
	params.q4SSDPAlertingMode = Q4SSDPALERTINGMODE_REACTIVE;
	params.alertPause = 2;
	params.recoveryPause = 3;
	params.latency = 4;
	params.jitterUp = 5;
	params.jitterDown = 6;
	params.bandWidthUp = 7;
	params.bandWidthDown = 8;
	params.packetLossUp = 9.9f;
	params.packetLossDown = 1.1f;
	params.procedure.negotiationTimeBetweenPingsUplink = 2;
	params.procedure.negotiationTimeBetweenPingsDownlink = 3;
	params.procedure.continuityTimeBetweenPingsUplink = 4;
	params.procedure.continuityTimeBetweenPingsDownlink = 5;
	params.procedure.bandwidthTime = 6;
	params.procedure.windowSizeLatencyCalcUplink = 7;
	params.procedure.windowSizeLatencyCalcDownlink = 8;
	params.procedure.windowSizePacketLossCalcUplink = 9;
	params.procedure.windowSizePacketLossCalcDownlink = 1;
	std::string message = Q4SMessage_createRequest_withSDP(Q4SMTYPE_BEGIN, "myIp", "12345", params);

	std::string compare = "BEGIN q4s://myIp:12345 Q4S/1.0\n\na=qos-level:0/1\na=alerting-mode:Reactive\na=alert-pause:2\na=recovery-pause:3\na=latency:4\na=jitter:5/6\na=bandwidth:7/8\na=packetloss:9.9/1.1\na=measurement:procedure default(2/3,4/5,6,7/8,9/1)\n";

	EXPECT_EQ(compare, message);
}