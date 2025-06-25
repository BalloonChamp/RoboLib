#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct AppConfig {
    std::vector<std::string> motors;
    std::vector<std::string> sensors;
    bool start_database = true;
    int redis_port = 6379;
};

AppConfig loadConfig(const std::string& path);
