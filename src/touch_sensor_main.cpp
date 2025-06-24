#include "robotlib/touch_sensor.h"

int main() {
    TouchSensor sensor("TouchSensor", SENSOR_PORT);
    sensor.run();
    return 0;
}
