#ifndef _Q4SSTRUCT_H_
#define _Q4SSTRUCT_H_

#include <string>

#define MEASUREMENTS_PATTERN "Measurements: l="
#define MEASUREMENTS_JITTER_PATTERN ", j="
#define MEASUREMENTS_PACKETLOSS_PATTERN ", pl="
#define MEASUREMENTS_BANDWIDTH_PATTERN ", bw="

struct Q4SMeasurementValues
{
    float latency;
    float jitter;
    float bandwidth;
    float packetLoss;
	bool operator ==(const Q4SMeasurementValues compare) const;
};

std::string Q4SMeasurementValues_create(Q4SMeasurementValues values);
bool Q4SMeasurementValues_parse(std::string message, Q4SMeasurementValues& values);

class Q4SMeasurementResult
{
public:
    Q4SMeasurementResult() {latencyAlert = false; jitterAlert = false; bandwidthAlert = false; packetLossAlert = false;}
    ~Q4SMeasurementResult() {}
    Q4SMeasurementValues values;
    bool latencyAlert;
    bool jitterAlert;
    bool bandwidthAlert;
    bool packetLossAlert;
	bool operator ==(const Q4SMeasurementResult compare) const;
};

#endif //_Q4SSTRUCT_H_