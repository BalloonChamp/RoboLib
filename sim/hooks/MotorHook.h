#include "GenericHook.h"
class MotorHook : public GenericHook {
public:
    std::string read() override { return "motor_env"; }
};
