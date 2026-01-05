#ifndef TCPSOCKETSERVER_H
#define TCPSOCKETSERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

class TCPSocketServer {
public:
    explicit TCPSocketServer(unsigned short port);
    ~TCPSocketServer();

    bool start();
    bool acceptClientNonBlocking();  // accepte si un client est en attente
    int  readNonBlocking(void* buf, int len); // lit si data dispo
    int  write(const void* buf, int len);

    bool hasClient() const { return client_ != INVALID_SOCKET; }
    void stop();

private:
    unsigned short port_;
    SOCKET listen_ = INVALID_SOCKET;
    SOCKET client_ = INVALID_SOCKET;
    bool wsaOk_ = false;

    void setNonBlocking(SOCKET s);
};

#endif // TCPSOCKETSERVER_H
