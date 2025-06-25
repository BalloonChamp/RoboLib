#pragma once
#include "Component.h"
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

class MainComponent : public Component {
public:
    MainComponent(Database& db, const nlohmann::json& config);
    void run() override;
private:
    const nlohmann::json m_config;
    std::vector<std::unique_ptr<Component>> m_children;
};
