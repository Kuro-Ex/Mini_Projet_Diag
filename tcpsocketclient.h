#ifndef TCPSOCKETCLIENT_H
#define TCPSOCKETCLIENT_H

#include <winsock2.h>

class TCPSocketClient {
private:
    char *hostName;
    unsigned short portNumber;
    int socketClient;
    struct sockaddr_in addrSockServer;
    bool connected;

public:
    TCPSocketClient();
    ~TCPSocketClient();

    bool connecter();                   // ne prend plus de paramètres
    long readData(void *data, long size);
    long writeData(void *data, long size);

    bool isConnected() const { return connected; }   // optionnel, pratique
};

#endif
