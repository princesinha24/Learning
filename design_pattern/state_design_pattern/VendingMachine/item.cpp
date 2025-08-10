#pragma once
#include<iostream>

using namespace std;
class item{
    string name;
    int id;
    bool available;
    int price;
    public:
    item(string name,int id, int price){
        this->name = name;
        this->id = id;
        this->price = price;
        available = true; // Assuming item is available by default
    }

    bool isAvailable() {
        return available;
    }

    int getPrice() {
        return price; // Assuming a fixed price for simplicity
    }

    ~item() {
        available = false; // Mark item as unavailable when destroyed
    }

    int getId() {
        return id; // Return item ID
    }
};