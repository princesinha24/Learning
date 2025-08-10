#pragma once
#include "../Observer/ObserverInterface.cpp"
class ObservableInterface {
    public:
        virtual ~ObservableInterface() = default;
        virtual void addObserver(ObserverInterface* observer) = 0;
        virtual void removeObserver(ObserverInterface* observer) = 0;
        virtual void setState(int state) = 0;
        virtual int getState() =0;
        virtual void notifyObservers() = 0;
};