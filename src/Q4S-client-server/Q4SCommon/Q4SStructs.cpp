#include "Q4SStructs.h"

#include <sstream>

bool Q4SMeasurementValues::operator ==(const Q4SMeasurementValues compare) const
{
	bool equal = true;
	equal &= (this->latency == compare.latency);
	equal &= (this->jitter == compare.jitter);
	equal &= (this->bandwidth == compare.bandwidth);
	equal &= (this->packetLoss == compare.packetLoss);
	return equal;
}

bool Q4SMeasurementResult::operator ==(const Q4SMeasurementResult compare) const
{
	bool equal = true;
	equal &= (this->latencyAlert == compare.latencyAlert);
	equal &= (this->jitterAlert == compare.jitterAlert);
	equal &= (this->bandwidthAlert == compare.bandwidthAlert);
	equal &= (this->packetLossAlert == compare.packetLossAlert);
	equal &= (this->values.latency == compare.values.latency);
	equal &= (this->values.jitter == compare.values.jitter);
	equal &= (this->values.bandwidth == compare.values.bandwidth);
	equal &= (this->values.packetLoss == compare.values.packetLoss);
	return equal;
}

std::string Q4SMeasurementValues_create(Q4SMeasurementValues results)
{
	std::string message;

	message.append(MEASUREMENTS_PATTERN);
	std::ostringstream streamLatency;
	streamLatency << results.latency;
	message.append(streamLatency.str());
	message.append(MEASUREMENTS_JITTER_PATTERN);
	std::ostringstream streamJitter;
	streamJitter << results.jitter;
	message.append(streamJitter.str());
	message.append(MEASUREMENTS_PACKETLOSS_PATTERN);
	std::ostringstream streamPacketLoss;
	streamPacketLoss << results.packetLoss;
	message.append(streamPacketLoss.str());
	message.append(MEASUREMENTS_BANDWIDTH_PATTERN);
	std::ostringstream streamBandwidth;
	streamBandwidth << results.bandwidth;
	message.append(streamBandwidth.str());
    message.append("\n");
	
	return message;
}

bool Q4SMeasurementValues_parse(std::string message, Q4SMeasurementValues &results)
{
	bool ok = true;

	std::string::size_type latencyPosition;
	std::string::size_type jitterPosition;
	std::string::size_type packetLossPosition;
	std::string::size_type bandwidthPosition;

	if (ok)
	{	
		std::string pattern = MEASUREMENTS_PATTERN;
		latencyPosition = message.find(pattern) + pattern.length();
		if (latencyPosition == std::string::npos) ok = false;
	}

	if (ok)
	{	
		std::string pattern = MEASUREMENTS_JITTER_PATTERN;
		jitterPosition = message.find(pattern, latencyPosition) + pattern.length();
		if (jitterPosition == std::string::npos) ok = false;
	}

	if (ok)
	{	
		std::string pattern = MEASUREMENTS_PACKETLOSS_PATTERN;
		packetLossPosition = message.find(pattern, jitterPosition) + pattern.length();
		if (packetLossPosition == std::string::npos) ok = false;
	}

	if (ok)
	{	
		std::string pattern = MEASUREMENTS_BANDWIDTH_PATTERN;
		bandwidthPosition = message.find(pattern, packetLossPosition) + pattern.length();
		if (bandwidthPosition == std::string::npos) ok = false;
	}


	if (ok)
	{
		std::string latencyText = message.substr(latencyPosition, (jitterPosition - 4 ) - latencyPosition);
		std::string jitterText = message.substr(jitterPosition, (packetLossPosition - 4 ) - jitterPosition);
		std::string packetLossText = message.substr(packetLossPosition, (bandwidthPosition - 4 ) - packetLossPosition);
		std::string bandwidthText = message.substr(bandwidthPosition, message.length() - bandwidthPosition);

		results.latency = stof(latencyText);
		results.jitter = stof(jitterText);
		results.packetLoss = stof(packetLossText);
		results.bandwidth = stof(bandwidthText);
	}
	
	return ok;
}
