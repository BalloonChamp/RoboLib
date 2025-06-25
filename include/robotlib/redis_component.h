#pragma once
#include "robotlib/base_component.h"
#include "robotlib/redis.h"
#include <string>

class RedisComponent : public BaseComponent {
public:
    RedisComponent(const std::string& name, Redis& db);
    void run() override;
protected:
    virtual std::string handleMessage(const std::string& message) = 0;
    std::string cmdKey() const { return m_name + ":cmd"; }
    std::string replyKey() const { return m_name + ":reply"; }
private:
    std::string m_name;
    Redis& m_db;
};
