#pragma once

#include "robotlib/base_component.h"
#include "robotlib/redis.h"
#include <vector>
#include <string>

class Controller : public BaseComponent {
public:
    Controller(Redis& db,
               const std::vector<std::string>& motors,
               const std::vector<std::string>& sensors);
    void run() override;
private:
    Redis& m_db;
    std::vector<std::string> m_motors;
    std::vector<std::string> m_sensors;
};
