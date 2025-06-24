#include "robotlib/motor.h"
#include <string>

int main() {
    Motor motor("Motor" + std::to_string(MOTOR_ID), MOTOR_PORT, MOTOR_ID);
    motor.run();
    return 0;
}
