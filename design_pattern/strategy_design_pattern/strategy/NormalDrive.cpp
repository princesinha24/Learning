#pragma once
#include "DriveStrategy.cpp"

class NormalDrive : public DriveStrategy {
public:
    void drive() override {
        cout << "Driving with normal strategy." << endl;
    }
};