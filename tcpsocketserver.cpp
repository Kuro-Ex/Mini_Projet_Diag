#include "tcpsocketserver.h"
#include <cstring>

TCPSocketServer::TCPSocketServer(unsigned short port) : port_(port) {
    WSADATA wsa{};
    wsaOk_ = (WSAStartup(MAKEWORD(2,2), &wsa) == 0);
}

TCPSocketServer::~TCPSocketServer() {
    stop();
    if (wsaOk_) WSACleanup();
}

void TCPSocketServer::setNonBlocking(SOCKET s) {
    u_long mode = 1;
    ioctlsocket(s, FIONBIO, &mode);
}

bool TCPSocketServer::start() {
    if (!wsaOk_) return false;

    listen_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_ == INVALID_SOCKET) return false;

    int opt = 1;
    setsockopt(listen_, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port_);

    if (bind(listen_, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(listen_);
        listen_ = INVALID_SOCKET;
        return false;
    }

    if (listen(listen_, 1) == SOCKET_ERROR) {
        closesocket(listen_);
        listen_ = INVALID_SOCKET;
        return false;
    }

    setNonBlocking(listen_);
    return true;
}

bool TCPSocketServer::acceptClientNonBlocking() {
    if (listen_ == INVALID_SOCKET) return false;
    if (client_ != INVALID_SOCKET) return true; // déjà connecté

    SOCKET s = accept(listen_, nullptr, nullptr);
    if (s == INVALID_SOCKET) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) return false; // rien à accepter
        return false; // vraie erreur
    }

    client_ = s;
    setNonBlocking(client_);
    return true;
}

int TCPSocketServer::readNonBlocking(void* buf, int len) {
    if (client_ == INVALID_SOCKET || !buf || len <= 0) return -1;

    int r = recv(client_, (char*)buf, len, 0);
    if (r == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) return 0; // rien à lire
        // erreur réelle => on ferme
        closesocket(client_);
        client_ = INVALID_SOCKET;
        return -1;
    }

    if (r == 0) { // client fermé
        closesocket(client_);
        client_ = INVALID_SOCKET;
        return -1;
    }
    return r;
}

int TCPSocketServer::write(const void* buf, int len) {
    if (client_ == INVALID_SOCKET || !buf || len <= 0) return -1;
    int s = send(client_, (const char*)buf, len, 0);
    return (s == SOCKET_ERROR) ? -1 : s;
}

void TCPSocketServer::stop() {
    if (client_ != INVALID_SOCKET) {
        closesocket(client_);
        client_ = INVALID_SOCKET;
    }
    if (listen_ != INVALID_SOCKET) {
        closesocket(listen_);
        listen_ = INVALID_SOCKET;
    }
}
