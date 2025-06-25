#include "robotlib/config_loader.h"
#include <fstream>

AppConfig loadConfig(const std::string& path) {
    AppConfig cfg;
    std::ifstream in(path);
    if (!in) return cfg;
    nlohmann::json j; in >> j;
    if (j.contains("motors")) cfg.motors = j["motors"].get<std::vector<std::string>>();
    if (j.contains("sensors")) cfg.sensors = j["sensors"].get<std::vector<std::string>>();
    if (j.contains("start_database")) cfg.start_database = j["start_database"].get<bool>();
    return cfg;
}
