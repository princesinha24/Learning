#include <set>

class lift{
public:
    enum Direction { UP, DOWN, IDLE };
private:
    int totalFloors;
    int currentFloor;
    Direction currentDirection;
    std::set<int> upRequests;
    std::set<int> downRequests;
    lift(int totalFloors);
    void callLift(int floor, Direction direction);
    void selectFloor(int floor);
    void step(); // Move the lift one step based on current requests
    int getCurrentFloor() const;
    Direction getCurrentDirection() const;
}