#include "robotlib/motor.h"
#include "robotlib/touch_sensor.h"
#include "robotlib/controller.h"
#include "robotlib/redis.h"
#include "robotlib/config_loader.h"
#include "robotlib/database_component.h"
#include <iostream>
#include <thread>
#include <memory>

int main(int argc, char* argv[]) {
    std::string cfgPath = "config.json";
    if (argc > 1) cfgPath = argv[1];
    AppConfig cfg = loadConfig(cfgPath);

    Redis db;
    if (!db.connect()) {
        std::cerr << "Failed to connect to redis\n";
        return 1;
    }

    std::vector<std::thread> threads;
    DatabaseComponent dbComp;
    if (cfg.start_database) {
        threads.emplace_back([&](){ dbComp.run(); });
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::vector<std::unique_ptr<Motor>> motors;
    for (size_t i = 0; i < cfg.motors.size(); ++i) {
        motors.emplace_back(std::make_unique<Motor>(cfg.motors[i], db, i + 1));
        threads.emplace_back([&, i](){ motors[i]->run(); });
    }
    std::vector<std::unique_ptr<TouchSensor>> sensors;
    for (size_t i = 0; i < cfg.sensors.size(); ++i) {
        sensors.emplace_back(std::make_unique<TouchSensor>(cfg.sensors[i], db));
        threads.emplace_back([&, i](){ sensors[i]->run(); });
    }

    Controller controller(db, cfg.motors, cfg.sensors);
    controller.run();

    for (auto& t : threads) t.join();
    return 0;
}
