#ifndef _Q4SCLIENTSTATE_H_
#define _Q4SCLIENTSTATE_H_

enum Q4SClientState
{   
    Q4SCLIENTSTATE_INVALID,
    Q4SCLIENTSTATE_INIT,
    Q4SCLIENTSTATE_HANDSHAKE,
    Q4SCLIENTSTATE_NEGOTIATION,
    Q4SCLIENTSTATE_CONTINUITY,
    Q4SCLIENTSTATE_TERMINATION,
};

#endif  // _Q4S-CLIENTSTATE_H_