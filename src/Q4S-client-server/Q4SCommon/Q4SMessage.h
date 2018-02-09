#ifndef _Q4SMESSAGE_H_
#define _Q4SMESSAGE_H_

#include <string>
#include "Q4SSDP.h"
#include "Q4SStructs.h"

enum Q4SMRequestOrResponse
{ Q4SMREQUESTORRESPOND_INVALID
, Q4SMREQUESTORRESPOND_REQUEST
, Q4SMREQUESTORRESPOND_RESPONSE
};

enum Q4SMType
{ Q4SMTYPE_INVALID
, Q4SMTYPE_BEGIN
, Q4SMTYPE_READY
, Q4SMTYPE_PING
, Q4SMTYPE_BWIDTH
, Q4SMTYPE_CANCEL
, Q4SMTYPE_Q4SALERT
};

enum Q4SResponseCode
{ Q4SRESPONSECODE_INVALID
, Q4SRESPONSECODE_200
, Q4SRESPONSECODE_3XX
, Q4SRESPONSECODE_400
, Q4SRESPONSECODE_404
, Q4SRESPONSECODE_405
, Q4SRESPONSECODE_406
, Q4SRESPONSECODE_408
, Q4SRESPONSECODE_413
, Q4SRESPONSECODE_414
, Q4SRESPONSECODE_415
, Q4SRESPONSECODE_416
, Q4SRESPONSECODE_500
, Q4SRESPONSECODE_501
, Q4SRESPONSECODE_503
, Q4SRESPONSECODE_504
, Q4SRESPONSECODE_505
, Q4SRESPONSECODE_513
, Q4SRESPONSECODE_600
, Q4SRESPONSECODE_601
, Q4SRESPONSECODE_603
, Q4SRESPONSECODE_604
};

std::string Q4SMessage_createPing(std::string host, std::string port, unsigned long sequenceNumber, unsigned long timeStamp);
std::string Q4SMessage_createPing(std::string host, std::string port, unsigned long sequenceNumber, unsigned long timeStamp, Q4SMeasurementValues &results);
std::string Q4SMessage_createBWidth(std::string host, std::string port, unsigned long sequenceNumber);
std::string Q4SMessage_createBegin(std::string host, std::string port);
std::string Q4SMessage_createReady(std::string host, std::string port, unsigned long stage);
std::string Q4SMessage_create200OKBeginResponse();
std::string Q4SMessage_create200OKBeginResponse(unsigned long sequenceNumber);
std::string Q4SMessage_create200OKBeginResponse(Q4SSDPParams q4SSDPParams);
std::string Q4SMessage_createResponse(Q4SResponseCode q4SResponseCode, std::string reasonPhrase);
std::string Q4SMessage_createRequest(Q4SMType q4SMType, 
						std::string host, 
						std::string port,
						bool isSequenceNumber=false,
						unsigned long sequenceNumber=0,
						bool isTimeStamp=false,
						unsigned long timeStamp=0,
						bool isStage=false,
						unsigned long stage=0,
						bool isMeaurements=false,
						Q4SMeasurementValues *values=NULL);
std::string Q4SMessage_createRequest_withSDP(Q4SMType q4SMType, 
						std::string host, 
						std::string port,
						bool isSequenceNumber,
						unsigned long sequenceNumber,
						bool isTimeStamp,
						unsigned long timeStamp,
						bool isStage,
						unsigned long stage,
						Q4SSDPParams q4SSDPParams);
std::string Q4SMessage_createRequest_withSDP(Q4SMType q4SMType, 
						std::string host, 
						std::string port, 
						Q4SSDPParams q4SSDPParams);
#endif  // _Q4SMESSAGE_H_
