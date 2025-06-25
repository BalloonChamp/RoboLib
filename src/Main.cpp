#include "components/MainComponent.h"
#include "components/DatabaseComponent.h"
#include "components/MotorComponent.h"
#include "components/SchedulerComponent.h"
#include "networking/DatabaseClient.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main(int argc, char** argv) {
    std::string config_file = "config.json";
    if (argc > 1) {
        config_file = argv[1];
    }

    std::ifstream in(config_file);
    if (!in) {
        std::cerr << "Failed to open config: " << config_file << std::endl;
        return 1;
    }
    json config = json::parse(in, nullptr, true, true);

    MainComponent main;
    main.register_component(std::make_unique<DatabaseComponent>());
    if (config.contains("motors")) {
        for (int id : config["motors"]) {
            main.register_component(std::make_unique<MotorComponent>(id));
        }
    }
    if (config.value("scheduler", false)) {
        main.register_component(std::make_unique<SchedulerComponent>());
    }

    main.start();
    DatabaseClient::instance().connect();
    DatabaseClient::instance().set("robot:status", "running");
    std::cout << "Press enter to quit..." << std::endl;
    std::cin.get();
    DatabaseClient::instance().set("robot:status", "stopped");
    main.stop();
    return 0;
}
