#ifndef _Q4SCALCULATION_H_
#define _Q4SCALCULATION_H_

#include "Q4SStructs.h"
#include <vector>
#include <set>
#include "gtest\gtest_prod.h"
#include "Q4SSDPParams.h"
#include "Q4SMessageManager.h"

void Calculation_calculateLatency(
	Q4SMessageManager &mReceivedMessages, 
	std::vector<unsigned long> &arrSentPingTimestamps, 
	float &latency, 
	unsigned long pingsSent, 
	bool showMeasureInfo=true);
void Calculation_calculateJitterStage0(
	Q4SMessageManager &mReceivedMessages,
	float &jitter,
	unsigned long timeBetweenPings,
	unsigned long pingsSent,
	bool showMeasureInfo=true);
void Calculation_calculateJitterAndPacketLossContinuity(
	Q4SMessageManager &mReceivedMessages,
	float &jitter,
	unsigned long timeBetweenPings,
	unsigned long pingsSent,
	float &packetLoss,
	bool showMeasureInfo=true);
void Calculation_calculateBandwidthStage1(unsigned long sequenceNumber, unsigned long bandwidthTime, float &bandwidth);
bool Calculation_calculatePacketLossStage1(Q4SMessageManager &mReceivedMessages, float &packetLoss);

bool Calculation_checkStage0(
	unsigned long maxLatencyUp, unsigned long maxJitterUp,
	unsigned long maxLatencyDown, unsigned long maxJitterDown,
	Q4SMeasurementResult &upResults,
	Q4SMeasurementResult &downResults);
bool Calculation_checkStage0(unsigned long maxLatency, unsigned long maxJitter, Q4SMeasurementResult &results);
bool Calculation_checkStage1(
	unsigned long bandwidthUp, float packetLossUp,
	unsigned long bandwidthDown, float packetLossDown,
	Q4SMeasurementResult &upResults,
	Q4SMeasurementResult &downResults);
bool Calculation_checkStage1(unsigned long bandwidth, float packetLoss, Q4SMeasurementResult &results);
bool Calculation_checkContinuity(
	unsigned long maxLatencyUp, unsigned long maxJitterUp, float maxPacketLossUp,
	unsigned long maxLatencyDown, unsigned long maxJitterDown, float maxPacketLossDown,
	Q4SMeasurementResult &upResults, Q4SMeasurementResult &downResults);

void Calculation_showCheckMessage(Q4SMeasurementResult &upResults, Q4SMeasurementResult &downResults);
std::string Calculation_generateAlertMessage(Q4SSDPParams params, Q4SMeasurementResult &results, Q4SMeasurementResult &upResults);
std::string Calculation_generateNotificationAlertMessage(Q4SSDPParams params, Q4SMeasurementResult &results, Q4SMeasurementResult &upResults);

#endif  // _Q4SCALCULATION_H_