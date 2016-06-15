#ifndef _Q4SCLIENTPROTOCOL_H_
#define _Q4SCLIENTPROTOCOL_H_

#include "Q4SClientSocket.h"
#include "Q4SMessageManager.h"

class Q4SClientProtocol
{
public:

    // Constructor-Destructor
    Q4SClientProtocol ();
    ~Q4SClientProtocol ();

    // Init-Done
    bool    init();
    void    done();

    // Q4S Methods
    bool    begin();
    void    ready();
    void    ping();
    void    bwidth();
    void    cancel();
    void    alert();

private:

    void    clear();

    bool    openConnections();
    void    closeConnections();

    Q4SClientSocket             mClientSocket;
    HANDLE                      marrthrHandle[ 2 ];
    bool                        manageTcpResponses( );
    bool                        manageUdpResponses( );
    static DWORD WINAPI         manageTcpResponsesFn( LPVOID lpData );
    static DWORD WINAPI         manageUdpResponsesFn( LPVOID lpData );

    Q4SMessageManager           mReceivedMessages;
};

#endif  // _Q4SCLIENTPROTOCOL_H_