#include "Q4SMessage.h"

#include "Q4SMessageTools.h"

std::string Q4SMessage_makeFirstLineRequestMethod(Q4SMType q4SMType, std::string host, std::string port)
{
	std::string stringType = "NOT_DEFINED_TYPE";
    switch (q4SMType)
    {
        case Q4SMTYPE_BEGIN:
        {
            stringType = "BEGIN";
        }
        break;

        case Q4SMTYPE_READY:
        {
            stringType = "READY";
        }
        break;

        case Q4SMTYPE_PING:
        {
            stringType = "PING";
        }
        break;

        case Q4SMTYPE_BWIDTH:
        {
            stringType = "BWIDTH";
        }
        break;

        case Q4SMTYPE_CANCEL:
        {
            stringType = "CANCEL";
        }
        break;

        case Q4SMTYPE_Q4SALERT:
        {
            stringType = "Q4S-ALERT";
        }
        break;
    }

	return stringType;
}

std::string Q4SMessage_makeFirstLineRequestURI(std::string host, std::string port)
{
    std::string stringUri = "q4s:";
    stringUri.append("//");
    stringUri.append(host);
    stringUri.append(":");
    stringUri.append(port);

    return stringUri;
}

std::string Q4SMessage_makeFirstLineRequestVersion()
{
	std::string version = "Q4S/1.0";
	return version;
}

std::string Q4SMessage_makeFirstLineRequest(Q4SMType q4SMType, std::string host, std::string port)
{
	std::string message;

	// Method
	message = Q4SMessage_makeFirstLineRequestMethod(q4SMType, host, port);
    message.append(" ");

    // Request-URI
	message.append(Q4SMessage_makeFirstLineRequestURI(host, port));
    message.append(" ");

	// Q4S-Version
	message.append(Q4SMessage_makeFirstLineRequestVersion());
	message.append("\n");

	return message;
}

std::string Q4SMessage_makeHeaders(
	bool isSequenceNumber=false, unsigned long sequenceNumber=0,
	bool isTimeStamp=false, unsigned long timeStamp=0,
	bool isStage=false, unsigned long stage=0,
	bool isMeaurements=false,
	Q4SMeasurementValues *values=NULL)
{
	std::string message;

    // TODO
    // Session-Id

    //Sequence-Number
	if (isSequenceNumber)
	{
		message.append("Sequence-Number:");
		message.append(std::to_string((_ULonglong)sequenceNumber));
		message.append("\n");
	}

    //Timestamp
	if (isTimeStamp)
	{
		message.append("Timestamp:");
		message.append(std::to_string((_ULonglong)timeStamp));
		message.append("\n");
	}

    //Stage
	if (isStage)
	{
		message.append("Stage:");
		message.append(std::to_string((_ULonglong)stage));
		message.append("\n");
	}

    // Measurements
	if (isMeaurements)
	{
		
		message.append(Q4SMeasurementValues_create(*values));
	}

	return message;
}

std::string Q4SMessage_createPing(std::string host, std::string port, unsigned long sequenceNumber, unsigned long timeStamp)
{
	std::string message;

    // FirstLine
	message = Q4SMessage_makeFirstLineRequest(Q4SMTYPE_PING, host, port);

	// Headers
	message.append(Q4SMessage_makeHeaders(true, sequenceNumber, true, timeStamp));

    //CRLF
    message.append("\n");

    // Body Empty

	return message;
}

std::string Q4SMessage_createPing(std::string host, std::string port, unsigned long sequenceNumber, unsigned long timeStamp, Q4SMeasurementValues &results)
{
	std::string message;

    // FirstLine
	message = Q4SMessage_makeFirstLineRequest(Q4SMTYPE_PING, host, port);

	// Headers
	message.append(Q4SMessage_makeHeaders(true, sequenceNumber, true, timeStamp, false, 0, true, &results));

    //CRLF
    message.append("\n");

    // Body Empty

	return message;
}

std::string Q4SMessage_createBWidth(std::string host, std::string port, unsigned long sequenceNumber)
{
	std::string message;

    // FirstLine
	message = Q4SMessage_makeFirstLineRequest(Q4SMTYPE_BWIDTH, host, port);

	// Headers
	message.append(Q4SMessage_makeHeaders(true, sequenceNumber));

    //CRLF
    message.append("\n");

    // Body
	Q4SMessageTools_fillBodyToASize(message, 1024);

	return message;
}

std::string Q4SMessage_makeFirstLineResponseStatusCode(Q4SResponseCode q4SResponseCode)
{
	std::string message;

    switch (q4SResponseCode)
    {
        case Q4SRESPONSECODE_200:
        {
			message = "200";
        }
        break;

        default:
        {
			// TODO
        }
        break;
    }

	return message;
}

std::string Q4SMessage_makeFirstLineResponse(Q4SResponseCode q4SResponseCode, std::string reasonPhrase)
{
	std::string message;

    // Q4S-Version
    message = Q4SMessage_makeFirstLineRequestVersion();

	// SP
    message.append(" ");

	// Status-Code
	message.append(Q4SMessage_makeFirstLineResponseStatusCode(q4SResponseCode));

	// SP
    message.append(" ");

    // Reason-Phrase
	message.append(reasonPhrase);

	// CRLF
	message.append("\n");

	return message;
}

std::string Q4SMessage_createBegin(std::string host, std::string port)
{
	std::string message;

    // FirstLine
	message = Q4SMessage_makeFirstLineRequest(Q4SMTYPE_BEGIN, host, port);

	// Headers
	message.append(Q4SMessage_makeHeaders());

    //CRLF
    message.append("\n");

    // Body Empty

	return message;
}

std::string Q4SMessage_createReady(std::string host, std::string port, unsigned long stage)
{
	std::string message;

    // FirstLine
	message = Q4SMessage_makeFirstLineRequest(Q4SMTYPE_READY, host, port);

	// Headers
	message.append(Q4SMessage_makeHeaders(false, 0, false, 0, true, stage));

    //CRLF
    message.append("\n");

    // Body Empty

	return message;
}

std::string Q4SMessage_create200OKBeginResponse()
{
	std::string message;

	message = Q4SMessage_createResponse(Q4SRESPONSECODE_200, "OK");

	return message;
}

std::string Q4SMessage_create200OKBeginResponse(unsigned long sequenceNumber)
{
	std::string message;
	std::string reasonPhrase = "OK " + std::to_string((_ULonglong)sequenceNumber);
	message = Q4SMessage_createResponse(Q4SRESPONSECODE_200, reasonPhrase);

	return message;
}

std::string Q4SMessage_create200OKBeginResponse(Q4SSDPParams q4SSDPParams)
{
	std::string message;

	message = Q4SMessage_create200OKBeginResponse();

    // SDP
	message.append(Q4SSDP_create(q4SSDPParams));

	return message;
}

std::string Q4SMessage_createResponse(Q4SResponseCode q4SResponseCode, std::string reasonPhrase)
{
	std::string message;

    // FirstLine
    message = Q4SMessage_makeFirstLineResponse(q4SResponseCode, reasonPhrase);

	// Headers
	//makeHeaders(isSequenceNumber, sequenceNumber, isTimeStamp, timeStamp, isStage, stage);

    //CRLF
	message.append("\n");

    // Body
    //makeBody(q4SMType);

	return message;
}

std::string Q4SMessage_createRequest(Q4SMType q4SMType, 
						std::string host, 
						std::string port,
						bool isSequenceNumber,
						unsigned long sequenceNumber,
						bool isTimeStamp,
						unsigned long timeStamp,
						bool isStage,
						unsigned long stage,
						bool isMeaurements,
						Q4SMeasurementValues *values)
{
	std::string message;

    // FirstLine
	message = Q4SMessage_makeFirstLineRequest(q4SMType, host, port);

    // Headers
	message.append(Q4SMessage_makeHeaders(isSequenceNumber, sequenceNumber, isTimeStamp, timeStamp, isStage, stage, isMeaurements, values));

    //CRLF
    message.append("\n");

    // Body Empty

	return message;
}

std::string Q4SMessage_createRequest_withSDP(Q4SMType q4SMType, 
						std::string host, 
						std::string port,
						bool isSequenceNumber,
						unsigned long sequenceNumber,
						bool isTimeStamp,
						unsigned long timeStamp,
						bool isStage,
						unsigned long stage,
						Q4SSDPParams q4SSDPParams)
{
	std::string message;

	message = Q4SMessage_createRequest(q4SMType, host, port, isSequenceNumber, sequenceNumber, isTimeStamp, timeStamp, isStage, stage);

	message.append(Q4SSDP_create(q4SSDPParams));

	return message;
}

std::string Q4SMessage_createRequest_withSDP(Q4SMType q4SMType, 
						std::string host, 
						std::string port, 
						Q4SSDPParams q4SSDPParams)
{
	std::string message;

	message = Q4SMessage_createRequest(q4SMType, host, port);

    // SDP
	message.append(Q4SSDP_create(q4SSDPParams));

	return message;
}

