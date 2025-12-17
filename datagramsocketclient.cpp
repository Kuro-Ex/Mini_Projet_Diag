#include "datagramsocketclient.h"
#include <cstdio>
#include <cstring>

long DatagramSocketClient::s_wsaRef = 0;

DatagramSocketClient::DatagramSocketClient(unsigned short localPort)
{
    // --- WinSock refcount (évite WSACleanup sauvage) ---
    if (s_wsaRef++ == 0) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            std::perror("WSAStartup");
        }
    }

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::perror("socket UDP");
        return;
    }

    // Optionnel : bind local (si tu veux écouter aussi, sinon tu peux enlever)
    if (localPort != 0) {
        sockaddr_in local{};
        std::memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = htonl(INADDR_ANY);
        local.sin_port = htons(localPort);

        if (bind(sock, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
            std::perror("bind UDP");
            // pas forcément fatal si tu n'as pas besoin de recevoir
        }
    }

    std::memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    destReady = false;
}

DatagramSocketClient::~DatagramSocketClient()
{
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }

    if (--s_wsaRef == 0) {
        WSACleanup();
    }
}

bool DatagramSocketClient::setTarget(const char* host, unsigned short port)
{
    if (!host || !*host) return false;

    sockaddr_in tmp{};
    std::memset(&tmp, 0, sizeof(tmp));
    tmp.sin_family = AF_INET;
    tmp.sin_port = htons(port);

    // IP directe ?
    if (inet_pton(AF_INET, host, &tmp.sin_addr) == 1) {
        dest = tmp;
        destReady = true;
        return true;
    }

    // Sinon résolution DNS (si jamais)
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(host, nullptr, &hints, &res) != 0 || !res) {
        std::perror("getaddrinfo");
        destReady = false;
        return false;
    }

    auto* addr = (sockaddr_in*)res->ai_addr;
    tmp.sin_addr = addr->sin_addr;
    freeaddrinfo(res);

    dest = tmp;
    destReady = true;
    return true;
}

long DatagramSocketClient::writeDatagram(const void* data, long size)
{
    if (sock == INVALID_SOCKET || !destReady || !data || size <= 0) return -1;

    int sent = sendto(sock, (const char*)data, (int)size, 0,
                      (sockaddr*)&dest, (int)sizeof(dest));

    if (sent == SOCKET_ERROR) {
        std::perror("sendto");
        return -1;
    }
    return (long)sent;
}

long DatagramSocketClient::readDatagram(void* data, long size)
{
    if (sock == INVALID_SOCKET || !data || size <= 0) return -1;

    sockaddr_in from{};
    int fromLen = sizeof(from);

    int received = recvfrom(sock, (char*)data, (int)size, 0,
                            (sockaddr*)&from, &fromLen);

    if (received == SOCKET_ERROR) {
        std::perror("recvfrom");
        return -1;
    }
    return (long)received;
}
