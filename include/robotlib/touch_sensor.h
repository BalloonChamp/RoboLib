#pragma once
#include "robotlib/redis_component.h"

class TouchSensor : public RedisComponent {
public:
    TouchSensor(const std::string& name, Redis& db);
protected:
    std::string handleMessage(const std::string& message) override;
private:
    bool m_pressed;
};
