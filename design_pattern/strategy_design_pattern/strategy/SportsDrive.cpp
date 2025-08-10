#pragma once
#include "DriveStrategy.cpp"

class SportsDrive : public DriveStrategy {
public:
    void drive() override {
        cout << "Driving with sports mode." << endl;
    }
};