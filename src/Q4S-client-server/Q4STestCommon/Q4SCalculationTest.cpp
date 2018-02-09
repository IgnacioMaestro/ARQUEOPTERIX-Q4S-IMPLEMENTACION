#include "gtest/gtest.h"

#include "..\Q4SCommon\Q4SMessage.h"
#include "..\Q4SCommon\Q4SMessageManager.h"
#include "..\Q4SCommon\Q4SCalculation.h"

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityTwoMessagesWithoutJitter)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 1, 0) , 2);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 2, packetLoss, false);

    EXPECT_EQ(jitter, 0.f);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityTwoMessagesWithJitter1)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 1, 0) , 3);

	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 2, packetLoss, false);

    EXPECT_EQ(jitter, 1.f);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityTwoMessagesWithJitter2)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 1, 0) , 4);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 2, packetLoss, false);

    EXPECT_EQ(jitter, 2.f);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityThreeMessagesWithoutJitter)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 1, 0) , 2);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 2, 0) , 4);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 3, packetLoss, false);

    EXPECT_EQ(jitter, 0.f);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityThreeMessagesWithPacketLoss)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 2, 0) , 4);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 3, packetLoss, false);

    EXPECT_EQ(jitter, 2.f);
    EXPECT_EQ(packetLoss, 100.f/3.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityFourMessagesWithPacketLossTwoGaps)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 3, 0) , 6);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 4, packetLoss, false);

    EXPECT_EQ(jitter, 8.f/3.f);
    EXPECT_EQ(packetLoss, 2.f * 100.f/4.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityFourMessagesWithPacketLossTwoSpaces)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 2, 0) , 4);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 4, 0) , 8);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 5, packetLoss, false);

    EXPECT_EQ(jitter, 8.f/4.f);
    EXPECT_EQ(packetLoss, 2.f * 100.f/5.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityThreeMessagesWithJitter1)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 1, 0) , 3);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 2, 0) , 6);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 3, packetLoss, false);

    EXPECT_EQ(jitter, 1.f);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculateJitterAndPacketLossContinuityThreeMessagesWithJitter2)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 0, 0) , 0);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 1, 0) , 4);
	q4SMessageManager.addMessage(Q4SMessage_createPing("", "", 2, 0) , 4);
	
	float jitter = 0.f;
	float packetLoss = 0.f;

	Calculation_calculateJitterAndPacketLossContinuity(q4SMessageManager, jitter, 2, 3, packetLoss, false);

    EXPECT_EQ(jitter, 2.f);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCalculateLatencyThreeMessages)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 4);
	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 6);
	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 8);

	arrSentPingTimestamps.push_back(0);
	arrSentPingTimestamps.push_back(4);
	arrSentPingTimestamps.push_back(6);

	float latency = 0.f;

	Calculation_calculateLatency(q4SMessageManager, arrSentPingTimestamps, latency, 3, false);

    EXPECT_EQ(latency, 1.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCalculateLatencyTwoMessages)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;
	
	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 4);
	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 6);

	arrSentPingTimestamps.push_back(0);
	arrSentPingTimestamps.push_back(4);

	float latency = 0.f;

	Calculation_calculateLatency(q4SMessageManager, arrSentPingTimestamps, latency, 2, false);

    EXPECT_EQ(latency, 1.5f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCalculateLatencyOneMessage)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 4);

	arrSentPingTimestamps.push_back(0);

	float latency = 0.f;

	Calculation_calculateLatency(q4SMessageManager, arrSentPingTimestamps, latency, 1, false);

    EXPECT_EQ(latency, 2.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCalculateLatencyOneMessageLost)
{
	Q4SMessageManager q4SMessageManager;
	std::vector<unsigned long> arrSentPingTimestamps;

	q4SMessageManager.addMessage(Q4SMessage_create200OKBeginResponse(), 4);

	arrSentPingTimestamps.push_back(0);
	arrSentPingTimestamps.push_back(4);

	float latency = 0.f;

	Calculation_calculateLatency(q4SMessageManager, arrSentPingTimestamps, latency, 2, false);

    EXPECT_EQ(latency, 2.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1OneMessageBegin)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBegin("", ""));

	float packetLoss = 0.f;
	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1OneMessageBWidth)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1TwoMessageBWidthWithoutPacketLoss)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 1));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 0.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1TwoMessageBWidthWithPacketLoss)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 2));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 100.f/3.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1TwoMessageBWidthWithPacketLossTwoGaps)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 3));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 2.f/4.f*100.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1ThreeMessageBWidthWithPacketLoss)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 2));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 3));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 1.f/4.f*100.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1FourMessageBWidthWithPacketLoss)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 2));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 3));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 4));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 1.f/5.f*100.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationcalculatePacketLossStage1ThreeMessageBWidthWithPacketLossTwoSpaces)
{
	Q4SMessageManager q4SMessageManager;
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 0));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 2));
	q4SMessageManager.addMessage(Q4SMessage_createBWidth("", "", 4));

	float packetLoss = 0.f;

	Calculation_calculatePacketLossStage1(q4SMessageManager, packetLoss);
    EXPECT_EQ(packetLoss, 2.f/5.f * 100.f);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage0BothAlert)
{
	Q4SMeasurementResult results;
	results.values.latency = 3;
	results.values.jitter = 3;

	bool ok = Calculation_checkStage0(2, 2, results);
    EXPECT_EQ(ok, false);
	EXPECT_EQ(results.latencyAlert, true);
    EXPECT_EQ(results.jitterAlert, true);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage0LatencyAlert)
{
	Q4SMeasurementResult results;
	results.values.latency = 3;
	results.values.jitter = 1;

	bool ok = Calculation_checkStage0(2, 2, results);
    EXPECT_EQ(ok, false);
	EXPECT_EQ(results.latencyAlert, true);
    EXPECT_EQ(results.jitterAlert, false);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage0JitterAlert)
{
	Q4SMeasurementResult results;
	results.values.latency = 1;
	results.values.jitter = 3;

	bool ok = Calculation_checkStage0(2, 2, results);
    EXPECT_EQ(ok, false);
	EXPECT_EQ(results.latencyAlert, false);
    EXPECT_EQ(results.jitterAlert, true);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage0NoAlert)
{
	Q4SMeasurementResult results;
	results.values.latency = 1;
	results.values.jitter = 1;

	bool ok = Calculation_checkStage0(2, 2, results);
    EXPECT_EQ(ok, true);
	EXPECT_EQ(results.latencyAlert, false);
    EXPECT_EQ(results.jitterAlert, false);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage1BothAlert)
{
	Q4SMeasurementResult results;
	results.values.bandwidth = 1.f;
	results.values.packetLoss = 3.f;

	bool ok = Calculation_checkStage1(2, 2.f, results);
    EXPECT_EQ(ok, false);
	EXPECT_EQ(results.bandwidthAlert, true);
    EXPECT_EQ(results.packetLossAlert, true);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage1BandwidthAlert)
{
	Q4SMeasurementResult results;
	results.values.bandwidth = 1.f;
	results.values.packetLoss = 1.f;

	bool ok = Calculation_checkStage1(2, 2.f, results);
    EXPECT_EQ(ok, false);
	EXPECT_EQ(results.bandwidthAlert, true);
    EXPECT_EQ(results.packetLossAlert, false);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage1PacketLossAlert)
{
	Q4SMeasurementResult results;
	results.values.bandwidth = 3.f;
	results.values.packetLoss = 3.f;

	bool ok = Calculation_checkStage1(2, 2.f, results);
    EXPECT_EQ(ok, false);
	EXPECT_EQ(results.bandwidthAlert, false);
    EXPECT_EQ(results.packetLossAlert, true);
}

TEST(Q4SCalculation_test_case, testQ4SCalculationCheckStage1NoAlert)
{
	Q4SMeasurementResult results;
	results.values.bandwidth = 3.f;
	results.values.packetLoss = 1.f;

	bool ok = Calculation_checkStage1(2, 2.f, results);
    EXPECT_EQ(ok, true);
	EXPECT_EQ(results.bandwidthAlert, false);
    EXPECT_EQ(results.packetLossAlert, false);
}
