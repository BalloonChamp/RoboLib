#pragma once
#include "robotlib/component.h"

class TouchSensor : public Component {
public:
    TouchSensor(const std::string& name, int port);
protected:
    std::string handleMessage(const std::string& message) override;
private:
    bool m_pressed;
};
