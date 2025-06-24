#include "robotlib/controller.h"
#include <iostream>
#include <thread>
#include <chrono>

Controller::Controller(const std::vector<int>& motor_ports,
                       const std::vector<int>& sensor_ports) {
    for (size_t i = 0; i < motor_ports.size(); ++i) {
        m_motors.push_back({TcpClient("127.0.0.1", motor_ports[i]), false, static_cast<int>(i)});
    }
    for (size_t i = 0; i < sensor_ports.size(); ++i) {
        m_sensors.push_back({TcpClient("127.0.0.1", sensor_ports[i]), false, static_cast<int>(i)});
    }
}

void Controller::run() {
    int step = 0;
    int target = 0;
    while (true) {
        // attempt connections
        for (auto& m : m_motors) {
            if (!m.connected) {
                m.connected = m.client.connectToServer();
                if (m.connected) {
                    std::cout << "Motor" << (m.index + 1) << " connected\n";
                } else {
                    std::cerr << "Warning: could not connect to Motor" << (m.index + 1) << "\n";
                }
            }
        }
        for (auto& s : m_sensors) {
            if (!s.connected) {
                s.connected = s.client.connectToServer();
                if (s.connected) {
                    std::cout << "Sensor" << (s.index + 1) << " connected\n";
                } else {
                    std::cerr << "Warning: could not connect to Sensor" << (s.index + 1) << "\n";
                }
            }
        }

        std::string reply;
        for (auto& m : m_motors) {
            if (!m.connected) continue;
            if (!m.client.sendData("GET") || !m.client.receiveData(reply)) {
                std::cerr << "Lost connection to Motor" << (m.index + 1) << "\n";
                m.client.closeConnection();
                m.connected = false;
            } else {
                std::cout << "Motor" << (m.index + 1) << " " << reply << "\n";
            }
        }
        for (auto& s : m_sensors) {
            if (!s.connected) continue;
            if (!s.client.sendData("READ") || !s.client.receiveData(reply)) {
                std::cerr << "Lost connection to Sensor" << (s.index + 1) << "\n";
                s.client.closeConnection();
                s.connected = false;
            } else {
                std::cout << "Sensor" << (s.index + 1) << " " << reply << "\n";
            }
        }

        if (step % 10 == 0) {
            target += 10;
            for (size_t i = 0; i < m_motors.size(); ++i) {
                auto& m = m_motors[i];
                if (!m.connected) continue;
                int sign = (i % 2 == 0) ? 1 : -1;
                std::string cmd = "MOVE " + std::to_string(sign * target);
                if (!m.client.sendData(cmd) || !m.client.receiveData(reply)) {
                    std::cerr << "Lost connection to Motor" << (m.index + 1) << "\n";
                    m.client.closeConnection();
                    m.connected = false;
                }
            }
        }

        ++step;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

