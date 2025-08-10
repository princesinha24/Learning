#pragma once
#include "../strategy/DriveStrategy.cpp"

class Vehicle {
protected:
    DriveStrategy* driveStrategy;
public:
    Vehicle(DriveStrategy* driveStrategy) : driveStrategy(driveStrategy) {}
    virtual ~Vehicle() { delete driveStrategy; }
    void performDrive() {
        driveStrategy->drive();
    }
};
