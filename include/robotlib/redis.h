#pragma once
#include <string>
#include <hiredis/hiredis.h>

class Redis {
public:
    Redis(const std::string& host = "127.0.0.1", int port = 6379);
    ~Redis();
    bool connect();
    bool push(const std::string& list, const std::string& msg);
    bool blpop(const std::string& list, std::string& msg, int timeout = 0);
private:
    std::string m_host;
    int m_port;
    redisContext* m_ctx;
};
