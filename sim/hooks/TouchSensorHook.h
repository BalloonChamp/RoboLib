#include "GenericHook.h"
class TouchSensorHook : public GenericHook {
public:
    std::string read() override { return "touch_env"; }
};
