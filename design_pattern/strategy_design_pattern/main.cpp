#include <vector>
#include "vechile/vechile.h"

using namespace std;

int main() {
    vector<Vehicle*> vehicles;
    vehicles.push_back(new Passenger());
    vehicles.push_back(new Sports());
    vehicles.push_back(new OffRoad());
    for (auto vehicle : vehicles) {
        vehicle->performDrive();
        delete vehicle;
    }
    return 0;
}