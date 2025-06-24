#pragma once

#include <string>

class TcpServer {
public:
    explicit TcpServer(int port);
    ~TcpServer();

    bool start();
    int acceptClient();
    bool sendData(int clientSock, const std::string& data);
    bool receiveData(int clientSock, std::string& data);
    void closeSocket(int sock);
private:
    int m_port;
    int m_serverSock;
};
