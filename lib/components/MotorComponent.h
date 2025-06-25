#ifndef MOTOR_COMPONENT_H
#define MOTOR_COMPONENT_H

#include "Component.h"
#include <sys/types.h>

class MotorComponent : public Component {
public:
    MotorComponent(int id);
    void start() override;
    void stop() override;

private:
    int id_;
    pid_t pid_{-1};
    void loop();
};

#endif // MOTOR_COMPONENT_H
