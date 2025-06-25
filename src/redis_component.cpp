#include "robotlib/redis_component.h"

RedisComponent::RedisComponent(const std::string& name, Redis& db)
    : m_name(name), m_db(db) {}

void RedisComponent::run() {
    while (true) {
        std::string msg;
        if (!m_db.blpop(cmdKey(), msg, 0)) continue;
        std::string reply = handleMessage(msg);
        m_db.push(replyKey(), reply);
    }
}
