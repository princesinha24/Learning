#include<iostream>

using namespace std;

class VisitorInterface; // Forward declaration
class interfaceElement{
    protected:
        int roomPrice=0;
    public:
        virtual void accept(class VisitorInterface* v) = 0;
        virtual int getRoomPrice() {
            return roomPrice;
        }
        virtual ~interfaceElement() = default; // Virtual destructor for proper cleanup
};
class SingleRoom;
class DoubleRoom;
class SuiteRoom;
class VisitorInterface {
    public:
        virtual int visit(SingleRoom* room) = 0;
        virtual int visit(DoubleRoom* room) = 0;
        virtual int visit(SuiteRoom* room) = 0;
};

class SingleRoom : public interfaceElement {
    public:
        void accept(VisitorInterface* v) override{
            roomPrice=v->visit(this);
        };
};

class DoubleRoom : public interfaceElement {
    public:
        void accept(VisitorInterface* v) override{
            roomPrice=v->visit(this);
        };
};

class SuiteRoom : public interfaceElement {
    public:
        void accept(VisitorInterface* v) override{
            roomPrice=v->visit(this);
        };
};

class RoomPriceVisitor : public VisitorInterface {
    public:
        int visit(SingleRoom* room) override {
            return 100; // Price for Single Room
        }
        
        int visit(DoubleRoom* room) override {
            return 150; // Price for Double Room
        }
        
        int visit(SuiteRoom* room) override {
            return 250; // Price for Suite Room
        }
};

class RoomMaintenaceVisitor : public VisitorInterface {
    public:
        int visit(SingleRoom* room) override {
            return 20; // Maintenance cost for Single Room
        }
        
        int visit(DoubleRoom* room) override {
            return 30; // Maintenance cost for Double Room
        }
        
        int visit(SuiteRoom* room) override {
            return 50; // Maintenance cost for Suite Room
        }
};


int main() {
    SingleRoom singleRoom;
    DoubleRoom doubleRoom;
    SuiteRoom suiteRoom;

    RoomPriceVisitor priceVisitor;
    RoomMaintenaceVisitor maintenanceVisitor;

    singleRoom.accept(&priceVisitor);
    doubleRoom.accept(&priceVisitor);
    suiteRoom.accept(&maintenanceVisitor);

    cout << "Single Room Price: " << singleRoom.getRoomPrice() << endl;
    cout << "Double Room Price: " << doubleRoom.getRoomPrice() << endl;
    cout << "Suite Room Maintenance Cost: " << suiteRoom.getRoomPrice() << endl;

    singleRoom.accept(&maintenanceVisitor);
    cout << "Single Room Maintenace Price: " << singleRoom.getRoomPrice() << endl;

    return 0;
}