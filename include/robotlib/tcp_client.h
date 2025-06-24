#pragma once

#include <string>

class TcpClient {
public:
    TcpClient(const std::string& host, int port);
    ~TcpClient();

    bool connectToServer();
    bool sendData(const std::string& data);
    bool receiveData(std::string& data);
    void closeConnection();
private:
    std::string m_host;
    int m_port;
    int m_sock;
};
