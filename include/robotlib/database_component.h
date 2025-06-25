#pragma once
#include "robotlib/base_component.h"
#include <string>
#include <thread>

class DatabaseComponent : public BaseComponent {
public:
    explicit DatabaseComponent(int port = 6379);
    void run() override;
private:
    int m_port;
};
