#include "SchedulerComponent.h"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <thread>

SchedulerComponent::SchedulerComponent() : Component("scheduler") {}

void SchedulerComponent::start() {
    pid_ = fork();
    if (pid_ == 0) {
        loop();
        _exit(0);
    }
}

void SchedulerComponent::stop() {
    if (pid_ > 0) {
        kill(pid_, SIGTERM);
        waitpid(pid_, nullptr, 0);
        pid_ = -1;
    }
}

void SchedulerComponent::loop() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "[scheduler] tick" << std::endl;
    }
}
