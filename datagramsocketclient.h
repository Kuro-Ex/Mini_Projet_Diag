#ifndef DATAGRAMSOCKETCLIENT_H
#define DATAGRAMSOCKETCLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>

class DatagramSocketClient
{
public:
    explicit DatagramSocketClient(unsigned short port);
    ~DatagramSocketClient();

    long writeDatagram(const void* data, long size, const char* host, unsigned short port);
    long readDatagram(void* data, long size);

private:
    int sock;
    unsigned short port;
    sockaddr_in source;
};

#endif // DATAGRAMSOCKETCLIENT_H
