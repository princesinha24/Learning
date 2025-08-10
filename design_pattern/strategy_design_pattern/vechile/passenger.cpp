#pragma once
#include "vechile.cpp"
#include "../strategy/NormalDrive.cpp"

class Passenger : public Vehicle {
public:
    Passenger() : Vehicle(new NormalDrive()) {}
};
