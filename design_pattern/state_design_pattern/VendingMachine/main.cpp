#include<iostream>
#include "VendingMachine.cpp"
#include "state.cpp"
using namespace std;

int main(){
    VendingMachine* vm= new VendingMachine();
    item* item1 = new item("Soda", 1, 10);
    item* item2 = new item("Chips", 2, 5);
    
    vm->addItem(item1);
    vm->addItem(item2);
    
    stateInterface* state=vm->getState(); // Should be Idle State
    state->pressInsertButton(); // Should transition to Insert Coin State
    state =vm->getState();
    state->insertCoin(10); // Should insert coin and transition to Select Product State
    state->setProduct(1); // Should select product 1 (Soda)
    state =vm->getState();
    state->pressProductButton(); // Should dispense Soda if available and enough coins are inserted
    state->setProduct(2); // Should select product 2 (Chips)
    state =vm->getState(); // Should show current state after dispensing
    delete state; // Clean up state
}

