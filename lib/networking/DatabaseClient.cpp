#include "DatabaseClient.h"
#include <iostream>

DatabaseClient& DatabaseClient::instance() {
    static DatabaseClient inst;
    return inst;
}

void DatabaseClient::connect(const char* host, int port) {
    if (ctx_) return;
    ctx_ = redisConnect(host, port);
    if (!ctx_ || ctx_->err) {
        if (ctx_) {
            std::cerr << "Redis connection error: " << ctx_->errstr << std::endl;
            redisFree(ctx_);
        }
        ctx_ = nullptr;
    }
}

void DatabaseClient::set(const std::string& key, const std::string& value) {
    if (!ctx_) connect();
    if (!ctx_) return;
    redisReply* reply = (redisReply*)redisCommand(ctx_, "SET %s %s", key.c_str(), value.c_str());
    if (reply) freeReplyObject(reply);
}

std::optional<std::string> DatabaseClient::get(const std::string& key) {
    if (!ctx_) connect();
    if (!ctx_) return std::nullopt;
    redisReply* reply = (redisReply*)redisCommand(ctx_, "GET %s", key.c_str());
    if (!reply) return std::nullopt;
    std::optional<std::string> res;
    if (reply->type == REDIS_REPLY_STRING) {
        res = reply->str;
    }
    freeReplyObject(reply);
    return res;
}

DatabaseClient::~DatabaseClient() {
    if (ctx_) redisFree(ctx_);
}
