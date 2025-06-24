#include "robotlib/tcp_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

TcpClient::TcpClient(const std::string& host, int port)
    : m_host(host), m_port(port), m_sock(-1) {}

TcpClient::~TcpClient() {
    closeConnection();
}

bool TcpClient::connectToServer() {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0) {
        perror("socket");
        return false;
    }
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    inet_pton(AF_INET, m_host.c_str(), &addr.sin_addr);
    if (connect(m_sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return false;
    }
    return true;
}

bool TcpClient::sendData(const std::string& data) {
    std::string msg = data + "\n";
    ssize_t sent = send(m_sock, msg.c_str(), msg.size(), 0);
    return sent == (ssize_t)msg.size();
}

bool TcpClient::receiveData(std::string& data) {
    char buffer[1024];
    ssize_t len = recv(m_sock, buffer, sizeof(buffer)-1, 0);
    if (len <= 0) return false;
    buffer[len] = '\0';
    data = buffer;
    if (!data.empty() && data.back() == '\n') data.pop_back();
    return true;
}

void TcpClient::closeConnection() {
    if (m_sock >= 0) {
        close(m_sock);
        m_sock = -1;
    }
}

