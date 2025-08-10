#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "./item.cpp"
using namespace std;

class stateInterface; // Forward declaration

class VendingMachine {
    int coins;
    int totalCoins;
    item* currentItem;
    stateInterface* currentState;
    vector<item*> items;

    item* getItemById(int itemId) {
        for (auto item : items) {
            if (item->getId() == itemId) {
                return item;
            }
        }
        return nullptr;
    }

    void removeItem(item* itemToRemove) {
        items.erase(remove(items.begin(), items.end(), itemToRemove), items.end());
    }

public:
    VendingMachine();
    ~VendingMachine();

    void addItem(item* newItem);
    stateInterface* getState();
    void setState(stateInterface* newState);
    void setCoin(int coin);
    int getCoin();
    item* getItem();
    void setItem(int itemId);
    void updateInventory();
    void initialsize();
};

class stateInterface {
protected:
    VendingMachine* vm;
public:
    stateInterface(VendingMachine* vm) : vm(vm) {}
    virtual ~stateInterface() = default;
    virtual string name() = 0;
    virtual void insertCoin(int coin) = 0;
    virtual void pressInsertButton() = 0;
    virtual void pressProductButton() = 0;
    virtual void pressCancelButton() = 0;
    virtual void setProduct(int productId) = 0;
};


class dispenseState : public stateInterface {
    public:
        dispenseState(VendingMachine* vm) : stateInterface(vm) {
            cout << "Product dispensed successfully." << endl;
            vm->updateInventory();
            vm-> initialsize();
        }
    
        string name() override { return "Dispense State"; }
    
        void insertCoin(int coin) override {
            cout << "Dispensing product. Please wait." << endl;
        }
    
        void pressInsertButton() override {
            cout << "Dispensing product. Please wait." << endl;
        }
    
        void pressProductButton() override {
            cout << "Dispensing product. Please wait." << endl;
        }
    
        void pressCancelButton() override {
            cout << "Dispensing product. Please wait." << endl;
        }
    
        void setProduct(int productId) override {
            cout << "Dispensing product. Please wait." << endl;
        }
    };

class cancelState : public stateInterface {
    int returnCoin() {
        cout << "Returning coins: " << vm->getCoin() << endl;
        return vm->getCoin();
    }
public:
    cancelState(VendingMachine* vm) : stateInterface(vm) {
        cout << "Transaction cancelled. Returning to idle state." << endl;
        returnCoin();
        vm->setCoin(0);
        vm->setItem(0);
        vm-> initialsize();
    }

    string name() override { return "Cancel State"; }

    void insertCoin(int coin) override {
        cout << "Transaction cancelled. Cannot insert coins." << endl;
    }

    void pressInsertButton() override {
        cout << "Transaction cancelled. Cannot insert coins." << endl;
    }

    void pressProductButton() override {
        cout << "Transaction cancelled. Cannot select products." << endl;
    }

    void pressCancelButton() override {
        cout << "Already in cancel state. Returning to idle state." << endl;
    }

    void setProduct(int productId) override {
        cout << "Transaction cancelled. Cannot set products." << endl;
    }
};

class selectProductState : public stateInterface {
    bool checkProduct() {
        if (!vm->getItem()->isAvailable()) return false;
        if (vm->getCoin() < vm->getItem()->getPrice()) {
            cout << "Insufficient coins for the selected product." << endl;
            return false;
        }
        return true;
    }
public:
    selectProductState(VendingMachine* vm) : stateInterface(vm) {}

    string name() override { return "Select Product State"; }

    void insertCoin(int coin) override {
        cout << "Product selection in progress. Please wait." << endl;
    }

    void pressInsertButton() override {
        cout << "Product selection in progress. Please wait." << endl;
    }

    void pressProductButton() override {
        cout << "Product selection in progress. Please wait." << endl;
    }

    void pressCancelButton() override {
        cout << "Product selection cancelled." << endl;
        vm->setState(new cancelState(vm));
    }

    void setProduct(int productId) override {
        vm->setItem(productId);
        cout << "Product set to: " << productId << endl;
        if (checkProduct()) {
            vm->setState(new dispenseState(vm));
        } else {
            vm->setState(new cancelState(vm));
        }
    }
};

class insertCoinState : public stateInterface {
    int totalCoins = 0;
public:
    insertCoinState(VendingMachine* vm) : stateInterface(vm) {}

    string name() override { return "Insert Coin State"; }

    void insertCoin(int coin) override {
        totalCoins += coin;
    }

    void pressInsertButton() override {
        cout << "Please insert coin." << endl;
    }

    void pressProductButton() override {
        cout << "Coin inserted: " << totalCoins << endl;
        vm->setCoin(totalCoins);
        vm->setState(new selectProductState(vm));
    }

    void pressCancelButton() override {
        cout << "Coin insertion cancelled." << endl;
        vm->setState(new cancelState(vm));
    }

    void setProduct(int productId) override {
        cout << "No product selected in insert coin state." << endl;
    }
};

class idleState : public stateInterface {
public:
    idleState(VendingMachine* vm) : stateInterface(vm) {
        vm->setCoin(0);
        vm->setItem(0);
    }

    string name() override { return "Idle State"; }

    void insertCoin(int coin) override {
        cout << "Please press the insert button first." << endl;
    }

    void pressInsertButton() override {
        cout << "Please insert coin." << endl;
        vm->setState(new insertCoinState(vm));
    }

    void pressProductButton() override {
        cout << "Please press the insert button first." << endl;
    }

    void pressCancelButton() override {
        cout << "Please press the insert button first." << endl;
    }

    void setProduct(int productId) override {
        cout << "No product selected in idle state." << endl;
    }
};


// VendingMachine method definitions
VendingMachine::VendingMachine() {
    totalCoins = 0;
    currentItem = nullptr;
    currentState = new idleState(this);
    items = vector<item*>();
}

VendingMachine::~VendingMachine() {
    delete currentState;
    for (auto item : items) delete item;
}

void VendingMachine::addItem(item* newItem) {
    items.push_back(newItem);
}

stateInterface* VendingMachine::getState() {
    cout << "Getting current state of the vending machine: " << currentState->name() << endl;
    return currentState;
}

void VendingMachine::setState(stateInterface* newState) {
    if (currentState) delete currentState;
    currentState = newState;
    cout << "State changed to: " << currentState->name() << endl;
}

void VendingMachine::setCoin(int coin) {
    coins = coin;
}

int VendingMachine::getCoin() {
    return coins;
}

item* VendingMachine::getItem() {
    return currentItem;
}

void VendingMachine::setItem(int itemId) {
    if (itemId == 0) {
        currentItem = nullptr;
        return;
    }
    currentItem = getItemById(itemId);
}

void VendingMachine::updateInventory() {
    removeItem(currentItem);
}

void VendingMachine::initialsize() {
    cout << "Resetting vending machine state to initial size." << endl;
    coins = 0;
    currentItem = nullptr;
    currentState = new idleState(this);
}
