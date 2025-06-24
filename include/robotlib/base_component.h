#pragma once

class BaseComponent {
public:
    virtual ~BaseComponent() = default;
    virtual void run() = 0;
};
