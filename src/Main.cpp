#include "components/MainComponent.h"
#include "components/DatabaseComponent.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config.json>" << std::endl;
        return 1;
    }
    nlohmann::json config;
    try {
        std::ifstream in(argv[1]);
        in >> config;
    } catch (...) {
        std::cerr << "Failed to load config" << std::endl;
        return 1;
    }

    Database db;
    DatabaseComponent dbComp(db);
    dbComp.start();
    MainComponent mainComp(db, config);
    mainComp.run();
    return 0;
}
