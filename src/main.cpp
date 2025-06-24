#include "robotlib/tcp_client.h"
#include <iostream>

int main() {
    TcpClient motor1("127.0.0.1", MOTOR1_PORT);
    TcpClient motor2("127.0.0.1", MOTOR2_PORT);
    TcpClient sensor("127.0.0.1", SENSOR_PORT);


    bool m1ok = motor1.connectToServer();
    if (!m1ok) std::cerr << "Warning: could not connect to Motor1\n";
    bool m2ok = motor2.connectToServer();
    if (!m2ok) std::cerr << "Warning: could not connect to Motor2\n";
    bool senok = sensor.connectToServer();
    if (!senok) std::cerr << "Warning: could not connect to TouchSensor\n";

    if (!m1ok && !m2ok && !senok) {
        std::cerr << "No components connected. Continuing...\n";
    }

    auto ping = [](TcpClient& client, const std::string& name){
        client.sendData("PING");
        std::string reply; if (client.receiveData(reply)) {
            std::cout << reply << "\n";
        } else {
            std::cerr << "No reply from " << name << "\n";
        }
    };

    if (m1ok) ping(motor1, "Motor1");
    if (m2ok) ping(motor2, "Motor2");
    if (senok) ping(sensor, "TouchSensor");

    std::string r;
    if (m1ok) {
        motor1.sendData("MOVE 10");
        if (motor1.receiveData(r)) std::cout << r << "\n";
    }

    if (senok) {
        sensor.sendData("READ");
        if (sensor.receiveData(r)) std::cout << r << "\n";
    }

    if (m1ok) motor1.closeConnection();
    if (m2ok) motor2.closeConnection();
    if (senok) sensor.closeConnection();
    return 0;
}
