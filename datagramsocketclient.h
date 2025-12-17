#ifndef DATAGRAMSOCKETCLIENT_H
#define DATAGRAMSOCKETCLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>

class DatagramSocketClient
{
public:
    explicit DatagramSocketClient(unsigned short port);
    ~DatagramSocketClient();

    bool setTarget(const char* host, unsigned short port);
    long writeDatagram(const void* data, long size);
    long readDatagram(void* data, long size);

private:
    SOCKET sock = INVALID_SOCKET;
    sockaddr_in dest{};     // cible (IP/port)
    bool destReady = false;
    static long s_wsaRef;
    unsigned short port = 0;
    sockaddr_in source{};
};


#endif // DATAGRAMSOCKETCLIENT_H
