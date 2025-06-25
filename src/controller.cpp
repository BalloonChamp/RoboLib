#include "robotlib/controller.h"
#include <iostream>
#include <thread>
#include <chrono>

Controller::Controller(Redis& db,
                       const std::vector<std::string>& motors,
                       const std::vector<std::string>& sensors)
    : m_db(db), m_motors(motors), m_sensors(sensors) {}

void Controller::run() {
    int step = 0;
    int target = 0;
    while (true) {
        std::string reply;
        for (const auto& name : m_motors) {
            m_db.push(name + ":cmd", "GET");
            if (m_db.blpop(name + ":reply", reply, 1)) {
                std::cout << name << " " << reply << "\n";
            }
        }
        for (const auto& name : m_sensors) {
            m_db.push(name + ":cmd", "READ");
            if (m_db.blpop(name + ":reply", reply, 1)) {
                std::cout << name << " " << reply << "\n";
            }
        }

        if (step % 10 == 0) {
            target += 10;
            for (size_t i = 0; i < m_motors.size(); ++i) {
                const auto& name = m_motors[i];
                int sign = (i % 2 == 0) ? 1 : -1;
                std::string cmd = "MOVE " + std::to_string(sign * target);
                m_db.push(name + ":cmd", cmd);
                m_db.blpop(name + ":reply", reply, 1);
            }
        }

        ++step;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
