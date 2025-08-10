#include "ObserverInterface.cpp"
#include "../Observable/Observable.h"


class mobileObserver : public ObserverInterface {
    string mobileNo;
    string name;
    ObservableInterface* observableObject;
    public:
        mobileObserver(string name, string mobileNo, ObservableInterface* observableObject) {
            this->mobileNo = mobileNo;
            this->name = name;
            this->observableObject = observableObject;
        }
        
        void update() override{
            cout<< "Notification has been sent via mobile to "<<name<<" by using "<< mobileNo<<" for object set as "<<observableObject->getState() << endl;
        }
};