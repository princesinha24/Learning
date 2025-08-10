#pragma once
#include <iostream>
using namespace std;

class DriveStrategy {
public:
    virtual void drive() = 0;
    virtual ~DriveStrategy() = default;
};