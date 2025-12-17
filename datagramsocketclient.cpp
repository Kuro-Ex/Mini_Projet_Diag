#include "datagramsocketclient.h"
#include <cstdio>
#include <cstring>

DatagramSocketClient::DatagramSocketClient(unsigned short port)
{
    this->port = port;

    // WinSock init
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::perror("WSAStartup");
    }

    // source (destination) setup
    std::memset(&source, 0, sizeof(source));
    source.sin_family = AF_INET;
    source.sin_port   = htons((u_short)port);

    // socket UDP
    sock = (int)socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0 || sock == (int)INVALID_SOCKET) {
        std::perror("error socket");
    }
}

DatagramSocketClient::~DatagramSocketClient()
{
    if (sock != (int)INVALID_SOCKET) {
        closesocket((SOCKET)sock);
        sock = (int)INVALID_SOCKET;
    }
    WSACleanup();
}

// --- ecriture des msg en UDP ---
long DatagramSocketClient::writeDatagram(const void* data, long size, const char* host, unsigned short port)
{
    struct hostent* hostentp = gethostbyname(host);
    if (!hostentp) {
        perror("gethostbyname");
        return -1;
    }

    source.sin_family = AF_INET;
    source.sin_port   = htons((u_short)port);   // port dynamique
    memcpy(&source.sin_addr, hostentp->h_addr, hostentp->h_length);

    long val = (long)sendto((SOCKET)sock, (const char*)data, (int)size, 0,
                             (struct sockaddr*)&source, (int)sizeof(source));

    if (val < 0) {
        perror("erreur sendto");
        return -1;
    }
    return val;
}


// --- lecture pour des msg ---
long DatagramSocketClient::readDatagram(void* data, long size)
{
    if (sock == (int)INVALID_SOCKET)
        return -1;

    sockaddr_in source{};
    int sourcelen = sizeof(source);

    long received = (long)recvfrom((SOCKET)sock,(char*)data,(int)size,0,(struct sockaddr*)&source,&sourcelen);

    if (received < 0) {
        std::perror("recvfrom");
        return -1;
    }

    return received;
}
