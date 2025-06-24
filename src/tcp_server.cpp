#include "robotlib/tcp_server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

TcpServer::TcpServer(int port) : m_port(port), m_serverSock(-1) {}

TcpServer::~TcpServer() {
    if (m_serverSock != -1) {
        close(m_serverSock);
    }
}

bool TcpServer::start() {
    m_serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSock < 0) {
        perror("socket");
        return false;
    }
    int opt = 1;
    setsockopt(m_serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(m_port);
    if (bind(m_serverSock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return false;
    }
    if (listen(m_serverSock, 1) < 0) {
        perror("listen");
        return false;
    }
    return true;
}

int TcpServer::acceptClient() {
    sockaddr_in clientAddr{};
    socklen_t len = sizeof(clientAddr);
    int clientSock = accept(m_serverSock, (sockaddr*)&clientAddr, &len);
    if (clientSock < 0) {
        perror("accept");
    }
    return clientSock;
}

bool TcpServer::sendData(int clientSock, const std::string& data) {
    std::string msg = data + "\n";
    ssize_t sent = send(clientSock, msg.c_str(), msg.size(), 0);
    return sent == (ssize_t)msg.size();
}

bool TcpServer::receiveData(int clientSock, std::string& data) {
    char buffer[1024];
    ssize_t len = recv(clientSock, buffer, sizeof(buffer)-1, 0);
    if (len <= 0) return false;
    buffer[len] = '\0';
    data = buffer;
    if (!data.empty() && data.back() == '\n') data.pop_back();
    return true;
}

void TcpServer::closeSocket(int sock) {
    if (sock >= 0) close(sock);
}

