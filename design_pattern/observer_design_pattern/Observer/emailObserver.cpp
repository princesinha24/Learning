
#include "ObserverInterface.cpp"
#include "../Observable/Observable.h"

class emailObserver: public ObserverInterface{
    string email;
    string name;
    ObservableInterface* observableObject;
    public:
        emailObserver(string name, string email, ObservableInterface* observableObject) {
            this->email = email;
            this->name = name;
            this->observableObject = observableObject;
        }
        
        void update() override {
            cout<< "Notification has been sent via email to "<<name<<" by using "<<email<<" for object set as " <<observableObject->getState()<< endl;
        }
};