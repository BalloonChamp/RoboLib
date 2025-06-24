#include "robotlib/tcp_client.h"
#include <iostream>

int main() {
    TcpClient motor1("127.0.0.1", MOTOR1_PORT);
    TcpClient motor2("127.0.0.1", MOTOR2_PORT);
    TcpClient sensor("127.0.0.1", SENSOR_PORT);

    if (!motor1.connectToServer() || !motor2.connectToServer() || !sensor.connectToServer()) {
        std::cerr << "Failed to connect to components\n";
        return 1;
    }

    auto ping = [](TcpClient& client){
        client.sendData("PING");
        std::string reply; client.receiveData(reply);
        std::cout << reply << "\n";
    };

    ping(motor1);
    ping(motor2);
    ping(sensor);

    motor1.sendData("MOVE 10");
    std::string r; motor1.receiveData(r); std::cout << r << "\n";

    sensor.sendData("READ"); sensor.receiveData(r); std::cout << r << "\n";

    motor1.closeConnection();
    motor2.closeConnection();
    sensor.closeConnection();
    return 0;
}
