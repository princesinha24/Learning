#pragma once
#include "vechile.cpp"
#include "../strategy/SportsDrive.cpp"

class OffRoad : public Vehicle {
public:
    OffRoad():Vehicle(new SportsDrive()) {}
};
