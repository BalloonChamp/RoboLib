#pragma once
#include <atomic>
#include <chrono>
#include <string>
#include <thread>

// Base class for any “app” that runs via a main loop.
class App {
public:
    App(const std::string& name);
    virtual ~App();

    // Called once before entering the loop. Return false to abort.
    virtual bool init() = 0;

    // Called repeatedly until stop() is called.
    virtual void loop() = 0;

    // Called once after the loop exits.
    virtual void cleanup() = 0;

    // Kick off init(), loop(), cleanup()
    void run();

    // Signal the loop to exit
    void stop();

    // How often between loop() calls
    void setLoopInterval(std::chrono::milliseconds interval);

    const std::string& getName() const;

protected:
    std::atomic<bool> running{false};
    std::string name;
    std::chrono::milliseconds loopInterval{1000};
};
