#ifndef DATAGRAMSOCKETCLIENT_H
#define DATAGRAMSOCKETCLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>

class DatagramSocketClient
{
public:
    explicit DatagramSocketClient(int port);
    ~DatagramSocketClient();

    long write_datagram(const void* data, long len, const char* host);

private:
    int sock;
    int port;
    sockaddr_in source;
};

#endif // DATAGRAMSOCKETCLIENT_H
