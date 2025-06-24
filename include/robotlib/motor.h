#pragma once
#include "robotlib/component.h"

class Motor : public Component {
public:
    Motor(const std::string& name, int port, int id);
protected:
    std::string handleMessage(const std::string& message) override;
private:
    int m_id;
    int m_position;
};
