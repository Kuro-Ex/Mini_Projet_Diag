#include "datagramsocketclient.h"
#include <cstdio>
#include <cstring>

DatagramSocketClient::DatagramSocketClient(int port)
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

long DatagramSocketClient::write_datagram(const void* data, long len, const char* host)
{
    struct hostent* hostentp;

    hostentp = gethostbyname(host);
    if (!hostentp) {
        std::perror("gethostbyname");
        return -1;
    }

    std::memcpy(&source.sin_addr,hostentp->h_addr,hostentp->h_length);

    long val = (long)sendto((SOCKET)sock,(const char*)data,(int)len,0,(struct sockaddr*)&source,(int)sizeof(source));

    if (val < 0) {
        std::perror("erreur sendto");
        return -1;
    }

    return val;
}
