#include "MotorComponent.h"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <thread>

MotorComponent::MotorComponent(int id)
    : Component("motor" + std::to_string(id)), id_(id) {}

void MotorComponent::start() {
    pid_ = fork();
    if (pid_ == 0) {
        loop();
        _exit(0);
    }
}

void MotorComponent::stop() {
    if (pid_ > 0) {
        kill(pid_, SIGTERM);
        waitpid(pid_, nullptr, 0);
        pid_ = -1;
    }
}

void MotorComponent::loop() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "[motor" << id_ << "] running" << std::endl;
    }
}
