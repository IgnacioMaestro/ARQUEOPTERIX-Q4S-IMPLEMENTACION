#include "gtest/gtest.h"

#include "..\Q4SCommon\Q4SStructs.h"

TEST(Q4SStructs_test_case, testQ4SMeasurementResultAsignation)
{
	Q4SMeasurementResult resultsInitial;
	resultsInitial.latencyAlert = true;
	resultsInitial.jitterAlert = true;
	resultsInitial.bandwidthAlert = true;
	resultsInitial.packetLossAlert = true;
	resultsInitial.values.latency = 1.f;
	resultsInitial.values.jitter = 1.f;
	resultsInitial.values.bandwidth = 1.f;
	resultsInitial.values.packetLoss = 1.f;
	Q4SMeasurementResult resultsCopy;

	resultsCopy = resultsInitial;

	EXPECT_EQ(resultsInitial, resultsCopy);
}

TEST(Q4SStructs_test_case, testQ4SMeasurementValuesAsignation)
{
	Q4SMeasurementValues valuesInitial;
	valuesInitial.latency = true;
	valuesInitial.jitter = true;
	valuesInitial.bandwidth = true;
	valuesInitial.packetLoss = true;
	Q4SMeasurementValues valuesCopy;

	valuesCopy = valuesInitial;

	EXPECT_EQ(valuesInitial, valuesCopy);
}

TEST(Q4SMessage_test_case, testQ4SMeasurementResult_createAndQ4SMeasurementResult_parse)
{
	Q4SMeasurementValues results;
	results.latency = 5;
	results.jitter = 4;
	results.bandwidth = 40;
	results.packetLoss = 0.3f;

	std::string sdpMessage = Q4SMeasurementValues_create(results);

	std::string compare;
	compare.append(MEASUREMENTS_PATTERN);
	compare.append("5");
	compare.append(MEASUREMENTS_JITTER_PATTERN);
	compare.append("4");
	compare.append(MEASUREMENTS_PACKETLOSS_PATTERN);
	compare.append("0.3");
	compare.append(MEASUREMENTS_BANDWIDTH_PATTERN);
	compare.append("40");
	compare.append("\n");
	EXPECT_EQ(compare, sdpMessage);

	Q4SMeasurementValues resultsReaded;
	bool ok = Q4SMeasurementValues_parse(sdpMessage, resultsReaded);
	EXPECT_EQ(ok, true);
	EXPECT_EQ(resultsReaded, results);
}