#include "datagramsocketserver.h"
#include <cstring>

DatagramSocketServer::DatagramSocketServer(unsigned short port) {
    WSADATA wsa{};
    wsaOk_ = (WSAStartup(MAKEWORD(2,2), &wsa) == 0);
    if (!wsaOk_) return;

    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_ == INVALID_SOCKET) return;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(sock_, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(sock_);
        sock_ = INVALID_SOCKET;
        return;
    }

    setNonBlocking(sock_);
}

DatagramSocketServer::~DatagramSocketServer() {
    close();
    if (wsaOk_) WSACleanup();
}

void DatagramSocketServer::setNonBlocking(SOCKET s) {
    u_long mode = 1;
    ioctlsocket(s, FIONBIO, &mode);
}

int DatagramSocketServer::read(void* buf, int len) {
    if (sock_ == INVALID_SOCKET || !buf || len <= 0) return -1;

    sockaddr_in from{};
    int fromLen = sizeof(from);

    int r = recvfrom(sock_, (char*)buf, len, 0, (sockaddr*)&from, &fromLen);
    if (r == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) return 0; // rien reçu
        return -1;
    }

    lastSender_ = from;
    lastSenderLen_ = fromLen;
    hasSender_ = true;
    return r;
}

int DatagramSocketServer::replyLast(const void* buf, int len) {
    if (!hasSender_ || sock_ == INVALID_SOCKET || !buf || len <= 0) return -1;

    int s = sendto(sock_, (const char*)buf, len, 0, (sockaddr*)&lastSender_, lastSenderLen_);
    return (s == SOCKET_ERROR) ? -1 : s;
}

void DatagramSocketServer::close() {
    if (sock_ != INVALID_SOCKET) {
        closesocket(sock_);
        sock_ = INVALID_SOCKET;
    }
    hasSender_ = false;
}
