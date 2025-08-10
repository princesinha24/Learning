#include "ObservableInterface.cpp"
#include <vector>

using namespace std;

class IphoneObservable : public ObservableInterface {
    private:
        vector<ObserverInterface*> observers;
        void notifyObservers() override{
            for (ObserverInterface* observer : observers) {
                observer->update();
            }
        }
        int state;
    public:
    IphoneObservable() {
        state = 0; // Initial state
        observers = vector<ObserverInterface*>();
    }
    void addObserver(ObserverInterface* observer) override {
        observers.push_back(observer);
    }
    void removeObserver(ObserverInterface* observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setState(int state) override{
        if(this->state == 0 && state != 0) {
            this->state = state;
            notifyObservers();
        } else if (this->state != 0 && state == 0) {
            this->state = state;
            notifyObservers();
        }
    }

    int getState() override{
        return state;
    }

};