#ifndef DATAGRAMSOCKETSERVER_H
#define DATAGRAMSOCKETSERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

class DatagramSocketServer {
public:
    explicit DatagramSocketServer(unsigned short port);
    ~DatagramSocketServer();

    bool isValid() const { return sock_ != INVALID_SOCKET; }
    int  read(void* buf, int len); // bloque pas (socket non-bloquant)
    int  replyLast(const void* buf, int len);

    bool hasLastSender() const { return hasSender_; }
    void close();

private:
    SOCKET sock_ = INVALID_SOCKET;
    sockaddr_in lastSender_{};
    int lastSenderLen_ = sizeof(sockaddr_in);
    bool hasSender_ = false;
    bool wsaOk_ = false;

    void setNonBlocking(SOCKET s);
};


#endif // DATAGRAMSOCKETSERVER_H
