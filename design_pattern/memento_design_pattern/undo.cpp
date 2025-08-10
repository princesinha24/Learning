#include<iostream>
#include<vector>
using namespace std;

class memento{
    int height;
    int width;
public:
    memento(int h, int w) : height(h), width(w) {}
    ~memento() = default; // Default destructor
    int getHeight() { return height; }
    int getWidth(){ return width; }
};

class saveMemento {
    vector<memento*> states;
public:
    saveMemento() = default; // Default constructor
    ~saveMemento() {
        for (auto state : states) {
            delete state; // Clean up allocated memory
        }
    }
    void addMemento(memento* state) {
        states.push_back(state);
    }
    
    memento* undo(){
        if(states.empty()){
            return nullptr;
        }

        memento* lastState = states.back();
        states.pop_back();
        return lastState;
    }
};

class originatorMemento {
    int height;
    int width;
    saveMemento mementoSaver;
public:
    originatorMemento(int h, int w) : height(h), width(w) {}

    void setHeight(int h) {
        height = h;
    }
    void setWidth(int w) {
        width = w;
    }
    void saveMemento() {
        cout << "Saving state: Height = " << height << ", Width = " << width << endl;
        mementoSaver.addMemento(new memento(height, width));
    }
    void restoreMemento() {
        cout<<"current state: Height = " << height << ", Width = " << width << endl;
        memento* revertSnapshot= mementoSaver.undo();
        if (revertSnapshot) {
            height = revertSnapshot->getHeight();
            width = revertSnapshot->getWidth();
            delete revertSnapshot; // Clean up restored state
        }
        cout << "Restored state: Height = " << height << ", Width = " << width << endl;
    }


};


int main() {
    originatorMemento originator(10, 20);
    
    originator.saveMemento(); // Save initial state
    originator.setHeight(15); // Change height
    originator.setWidth(25); // Change width

    originator.restoreMemento(); // Restore to previous state

    // delete originator; // Clean up originator
    return 0;
}