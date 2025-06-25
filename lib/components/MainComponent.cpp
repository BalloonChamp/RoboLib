#include "MainComponent.h"
#include "MotorComponent.h"
#include "SchedulerComponent.h"
#include "DatabaseComponent.h"
#include <iostream>
#include <chrono>
#include <thread>

MainComponent::MainComponent(Database& db, const nlohmann::json& config)
    : Component("main", db), m_config(config) {}

void MainComponent::run() {
    // spawn components based on configuration
    if (m_config.contains("components")) {
        for (auto& c : m_config["components"]) {
            std::string type = c["type"];
            if (type == "Motor") {
                int id = c.value("id", 0);
                std::string name = "motor" + std::to_string(id);
                auto comp = std::make_unique<MotorComponent>(name, id, m_db);
                comp->start();
                m_children.push_back(std::move(comp));
            } else if (type == "Scheduler") {
                auto comp = std::make_unique<SchedulerComponent>(m_db, c);
                comp->start();
                m_children.push_back(std::move(comp));
            }
        }
    }

    // main loop just monitors database
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
