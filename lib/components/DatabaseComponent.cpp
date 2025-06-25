#include "DatabaseComponent.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

DatabaseComponent::DatabaseComponent() : Component("database") {}

void DatabaseComponent::start() {
    std::cout << "[database] starting redis-server" << std::endl;
    pid_ = fork();
    if (pid_ == 0) {
        execlp("redis-server", "redis-server", "--save", "", NULL);
        _exit(1);
    }
    // give server a moment to start
    sleep(1);
}

void DatabaseComponent::stop() {
    if (pid_ > 0) {
        std::cout << "[database] stopping" << std::endl;
        kill(pid_, SIGTERM);
        waitpid(pid_, nullptr, 0);
        pid_ = -1;
    }
}
