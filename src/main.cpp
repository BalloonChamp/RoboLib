#include "robotlib/database_server.h"
#include "robotlib/db_motor.h"
#include "robotlib/db_touch_sensor.h"
#include "robotlib/scheduler.h"
#include <iostream>
#include <string>
#include <vector>

void printUsage(const char* prog) {
    std::cout << "Usage: " << prog
              << " [--dbmotor <id> | --dbsensor | --database | --scheduler]"
              << " [--port <p>]" << std::endl;
}

int main(int argc, char* argv[]) {
    enum Mode {NONE, DATABASE, DBMOTOR, DBSENSOR, SCHEDULER};
    Mode mode = NONE;
    int motorId = 0;
    int port = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--database") {
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
        } else {
            printUsage(argv[0]);
            return 1;
        }
    }

    if (mode == DATABASE) {
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
