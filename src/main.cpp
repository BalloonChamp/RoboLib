#include "robotlib/tcp_client.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    TcpClient motor1("127.0.0.1", MOTOR1_PORT);
    TcpClient motor2("127.0.0.1", MOTOR2_PORT);
    TcpClient sensor("127.0.0.1", SENSOR_PORT);

    bool m1ok = false;
    bool m2ok = false;
    bool senok = false;

    int target = 0;
    int step = 0;

    while (true) {
        if (!m1ok) {
            m1ok = motor1.connectToServer();
            if (m1ok) {
                std::cout << "Motor1 connected\n";
            } else {
                std::cerr << "Warning: could not connect to Motor1\n";
            }
        }
        if (!m2ok) {
            m2ok = motor2.connectToServer();
            if (m2ok) {
                std::cout << "Motor2 connected\n";
            } else {
                std::cerr << "Warning: could not connect to Motor2\n";
            }
        }
        if (!senok) {
            senok = sensor.connectToServer();
            if (senok) {
                std::cout << "TouchSensor connected\n";
            } else {
                std::cerr << "Warning: could not connect to TouchSensor\n";
            }
        }

        std::string r;
        if (m1ok) {
            if (!motor1.sendData("GET") || !motor1.receiveData(r)) {
                std::cerr << "Lost connection to Motor1\n";
                motor1.closeConnection();
                m1ok = false;
            } else {
                std::cout << "Motor1 " << r << "\n";
            }
        }

        if (m2ok) {
            if (!motor2.sendData("GET") || !motor2.receiveData(r)) {
                std::cerr << "Lost connection to Motor2\n";
                motor2.closeConnection();
                m2ok = false;
            } else {
                std::cout << "Motor2 " << r << "\n";
            }
        }

        if (senok) {
            if (!sensor.sendData("READ") || !sensor.receiveData(r)) {
                std::cerr << "Lost connection to TouchSensor\n";
                sensor.closeConnection();
                senok = false;
            } else {
                std::cout << "TouchSensor " << r << "\n";
            }
        }

        if (step % 10 == 0) {
            target += 10;
            if (m1ok) {
                std::string cmd = "MOVE " + std::to_string(target);
                if (!motor1.sendData(cmd) || !motor1.receiveData(r)) {
                    std::cerr << "Lost connection to Motor1\n";
                    motor1.closeConnection();
                    m1ok = false;
                }
            }
            if (m2ok) {
                std::string cmd = "MOVE " + std::to_string(-target);
                if (!motor2.sendData(cmd) || !motor2.receiveData(r)) {
                    std::cerr << "Lost connection to Motor2\n";
                    motor2.closeConnection();
                    m2ok = false;
                }
            }
        }

        step++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
