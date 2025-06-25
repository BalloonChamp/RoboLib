#pragma once
#include "robotlib/redis_component.h"

class Motor : public RedisComponent {
public:
    Motor(const std::string& name, Redis& db, int id);
protected:
    std::string handleMessage(const std::string& message) override;
private:
    int m_id;
    int m_position;
};
