#include "tcpsocketclient.h"
#include <cstring>

TCPSocketClient::TCPSocketClient()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    socketClient = INVALID_SOCKET;
    connected = false;

    hostName   = (char*)"172.16.230.208";
    portNumber = 1600;

    memset(&addrSockServer, 0, sizeof(addrSockServer));
    addrSockServer.sin_family      = AF_INET;
    addrSockServer.sin_port        = htons(portNumber);
    addrSockServer.sin_addr.s_addr = inet_addr(hostName);
}

TCPSocketClient::~TCPSocketClient()
{
    if (socketClient != INVALID_SOCKET) {
        closesocket(socketClient);
    }
    WSACleanup();
}

bool TCPSocketClient::connecter()
{
    // Si déjà connecté, on ne refait pas un connect()
    if (connected) {
        return true;
    }

    // Si un ancien socket traîne, on le ferme
    if (socketClient != INVALID_SOCKET) {
        closesocket(socketClient);
    }

    socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketClient == INVALID_SOCKET) {
        connected = false;
        return false;
    }

    int res = connect(socketClient,
                      (SOCKADDR*)&addrSockServer,
                      sizeof(addrSockServer));

    if (res == SOCKET_ERROR) {
        closesocket(socketClient);
        socketClient = INVALID_SOCKET;
        connected = false;
        return false;
    }

    connected = true;
    return true;
}

long TCPSocketClient::readData(void *data, long size)
{
    if (!connected || socketClient == INVALID_SOCKET)
        return -1;

    long bytes = recv(socketClient, (char*)data, size, 0);

    if (bytes <= 0) {
        // le serveur a probablement fermé
        connected = false;
    }

    return bytes;
}

long TCPSocketClient::writeData(void *data, long size)
{
    if (!connected || socketClient == INVALID_SOCKET)
        return -1;

    long sent = send(socketClient, (char*)data, size, 0);

    if (sent == SOCKET_ERROR) {
        connected = false;
    }

    return sent;
}
