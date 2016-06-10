#include "Q4SSocket.h"

#pragma comment(lib, "Ws2_32.lib")

Q4SSocket::Q4SSocket( )
{
    clear();
}

Q4SSocket::~Q4SSocket( )
{
    done();
}

bool Q4SSocket::init( )
{
    // Prevention done call
    done();

    bool ok = true;
    
    return ok;
}

void Q4SSocket::done( )
{
}

void Q4SSocket::clear( )
{
    mSocket = INVALID_SOCKET;
    mSocketType = 0;
    addrReceiverLen = 0;
}

void Q4SSocket::setSocket( SOCKET socket, int socketType )
{
    mSocket = socket;
    mSocketType = socketType;
}

bool Q4SSocket::sendData( char* sendBuffer )
{
    //Bind the socket.
    int     iResult;
    bool    ok = true;

    // Send the buffer
    if( mSocketType == SOCK_STREAM )
    {
        iResult = send( mSocket, sendBuffer, (int)strlen( sendBuffer ), 0 );
    }
    else if( mSocketType == SOCK_DGRAM )
    {
        iResult = sendto( mSocket, sendBuffer, (int)strlen( sendBuffer ), 0, ( SOCKADDR* )&addrReceiver, addrReceiverLen );
    }
    else
    {
        ok &= false;
    }

    if( iResult == SOCKET_ERROR )
    {
        printf( "send failed with error: %d\n", WSAGetLastError( ) );
        disconnect( );
        ok &= false;
    }

    printf( "Bytes Sent: %ld\n", iResult );

    return ok;
}

bool Q4SSocket::receiveData( char* receiveBuffer, int receiveBufferSize )
{
    //Listen on the socket for a client.
    bool    ok = true;
    int     iResult;

    if( mSocketType == SOCK_STREAM )
    {
    }
    else if( mSocketType == SOCK_DGRAM )
    {
    }
    else
    {
        ok &= false;
    }
    if( addrReceiverLen == 0 )
    {
        addrReceiverLen = sizeof( addrReceiver );
    }
    iResult = recvfrom( mSocket, receiveBuffer, receiveBufferSize, 0, ( SOCKADDR* )&addrReceiver, &addrReceiverLen );
    if( iResult > 0 )
    {
        printf( "Bytes received: %d\n", iResult );
        receiveBuffer[ iResult ] = '\0';
    }
    else if( iResult == 0 )
    {
        printf( "Connection closed\n" );
    }
    else
    {
        printf( "recv failed with error: %d\n", WSAGetLastError( ) );
    }

    return ok;
}

bool Q4SSocket::shutDown( )
{
    int     iResult;
    bool    ok = true;

    // shutdown the connection since no more data will be sent
    iResult = shutdown( mSocket, SD_SEND );
    if( iResult == SOCKET_ERROR )
    {
        printf( "shutdown failed with error: %d\n", WSAGetLastError( ) );
        disconnect( );
        ok &= false;
    }

    return ok;
}

bool Q4SSocket::disconnect( )
{
    bool    ok = true;

    // cleanup
    closesocket( mSocket );
    WSACleanup( );

    return ok;
}