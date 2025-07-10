#include <iostream>
#include "shared.hpp"
#include "AppManager.hpp"

void runAppManager() {
    // Call into the shared library
    std::cout << "[runAppManager] shared says: "
              << getSharedMessage() 
              << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "[AppManager] starting up…" << std::endl;
    runAppManager();
    return 0;
}
