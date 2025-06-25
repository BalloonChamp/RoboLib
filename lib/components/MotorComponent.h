#pragma once
#include "Component.h"
#include <string>

class MotorComponent : public Component {
public:
    MotorComponent(const std::string& name, int id, Database& db);
    void run() override;
private:
    int m_id;
    int m_position;
};
