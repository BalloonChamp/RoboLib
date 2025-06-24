#pragma once

#include "robotlib/base_component.h"
#include "robotlib/tcp_client.h"
#include <vector>
#include <string>

class Controller : public BaseComponent {
public:
    Controller(const std::vector<int>& motor_ports = {5001, 5002},
               const std::vector<int>& sensor_ports = {5003});
    void run() override;
private:
    struct Client {
        TcpClient client;
        bool connected;
        int index;
    };
    std::vector<Client> m_motors;
    std::vector<Client> m_sensors;
};
