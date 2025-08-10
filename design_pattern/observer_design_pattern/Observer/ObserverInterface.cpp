#pragma once


class ObserverInterface {
public:
    virtual ~ObserverInterface() = default;
    virtual void update() = 0;
};