
#include <iostream>
#include <vector>
#include <string>

#include "Observer/Observer.h"

using namespace std;
int main(){
    ObservableInterface *Iphone= new IphoneObservable();
    ObserverInterface *user1 = new mobileObserver("User1", "12312312123", Iphone);
    ObserverInterface *user2 = new emailObserver("User2", "dads@gmail.com", Iphone);
    ObserverInterface *user3 = new mobileObserver("User3", "12312312123", Iphone);
    ObserverInterface *user4 = new emailObserver("User1", "user1@gmail.com", Iphone);
    Iphone->addObserver(user1);
    Iphone->addObserver(user2);
    Iphone->addObserver(user3);
    Iphone->addObserver(user4);
    Iphone->setState(15);
    Iphone->removeObserver(user2);
    delete user2; // Clean up removed observer
    Iphone->setState(0);
}