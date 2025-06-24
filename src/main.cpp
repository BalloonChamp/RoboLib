#include "robotlib/motor.h"
#include "robotlib/touch_sensor.h"
#include "robotlib/controller.h"
#include "robotlib/database_server.h"
#include "robotlib/db_motor.h"
#include "robotlib/db_touch_sensor.h"
#include "robotlib/scheduler.h"
#include <iostream>
#include <string>
#include <vector>

void printUsage(const char* prog) {
    std::cout << "Usage: " << prog
              << " [--main | --motor <id> | --sensor | --dbmotor <id> | --dbsensor | --database | --scheduler]"
              << " [--port <p>]" << std::endl;
}

int main(int argc, char* argv[]) {
    enum Mode {NONE, MAIN, MOTOR, SENSOR, DATABASE, DBMOTOR, DBSENSOR, SCHEDULER};
    Mode mode = NONE;
    int motorId = 0;
    int port = 0;
    std::vector<int> motorPorts;
    std::vector<int> sensorPorts;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--main") {
            mode = MAIN;
        } else if (arg == "--motor" && i + 1 < argc) {
            mode = MOTOR;
            motorId = std::stoi(argv[++i]);
        } else if (arg == "--sensor") {
            mode = SENSOR;
        } else if (arg == "--database") {
            mode = DATABASE;
        } else if (arg == "--dbmotor" && i + 1 < argc) {
            mode = DBMOTOR;
            motorId = std::stoi(argv[++i]);
        } else if (arg == "--dbsensor") {
            mode = DBSENSOR;
        } else if (arg == "--scheduler") {
            mode = SCHEDULER;
        } else if (arg == "--port" && i + 1 < argc) {
            port = std::stoi(argv[++i]);
        } else if (arg == "--motor-port" && i + 1 < argc) {
            motorPorts.push_back(std::stoi(argv[++i]));
        } else if (arg == "--sensor-port" && i + 1 < argc) {
            sensorPorts.push_back(std::stoi(argv[++i]));
        } else {
            printUsage(argv[0]);
            return 1;
        }
    }

    if (mode == MAIN) {
        if (motorPorts.empty()) motorPorts = {5001, 5002};
        if (sensorPorts.empty()) sensorPorts = {5003};
        Controller controller(motorPorts, sensorPorts);
        controller.run();
    } else if (mode == MOTOR) {
        if (port == 0) port = 5000 + motorId;
        Motor motor("Motor" + std::to_string(motorId), port, motorId);
        motor.run();
    } else if (mode == SENSOR) {
        if (port == 0) port = 5003;
        TouchSensor sensor("TouchSensor", port);
        sensor.run();
    } else if (mode == DATABASE) {
        if (port == 0) port = 6000;
        DatabaseServer db(port);
        db.run();
    } else if (mode == DBMOTOR) {
        DbMotor motor("DbMotor" + std::to_string(motorId), motorId, port==0?6000:port);
        motor.run();
    } else if (mode == DBSENSOR) {
        DbTouchSensor sensor("DbTouchSensor", port==0?6000:port);
        sensor.run();
    } else if (mode == SCHEDULER) {
        std::vector<std::string> seq = {"Motor1:MOVE 10", "Motor2:MOVE -10", "Sensor:READ"};
        Scheduler sched(seq, port==0?6000:port);
        sched.run();
    } else {
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}
