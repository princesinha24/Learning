#pragma once
#include "vechile.cpp"
#include "../strategy/SportsDrive.cpp"

class Sports : public Vehicle {
public:
    Sports() : Vehicle(new SportsDrive()) {}
};