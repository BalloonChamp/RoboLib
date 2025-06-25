#include "robotlib/redis.h"
#include <iostream>

Redis::Redis(const std::string& host, int port)
    : m_host(host), m_port(port), m_ctx(nullptr) {}

Redis::~Redis() {
    if (m_ctx) {
        redisFree(m_ctx);
    }
}

bool Redis::connect() {
    m_ctx = redisConnect(m_host.c_str(), m_port);
    if (m_ctx == nullptr || m_ctx->err) {
        if (m_ctx) {
            std::cerr << "Redis connection error: " << m_ctx->errstr << "\n";
            redisFree(m_ctx);
            m_ctx = nullptr;
        }
        return false;
    }
    return true;
}

bool Redis::push(const std::string& list, const std::string& msg) {
    if (!m_ctx) return false;
    redisReply* r = (redisReply*)redisCommand(m_ctx, "RPUSH %s %s", list.c_str(), msg.c_str());
    if (!r) return false;
    freeReplyObject(r);
    return true;
}

bool Redis::blpop(const std::string& list, std::string& msg, int timeout) {
    if (!m_ctx) return false;
    redisReply* r = (redisReply*)redisCommand(m_ctx, "BLPOP %s %d", list.c_str(), timeout);
    if (!r) return false;
    bool ok = false;
    if (r->type == REDIS_REPLY_ARRAY && r->elements == 2 && r->element[1]->type == REDIS_REPLY_STRING) {
        msg = r->element[1]->str;
        ok = true;
    }
    freeReplyObject(r);
    return ok;
}
