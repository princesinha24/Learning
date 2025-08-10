#include<iostream>
using namespace std;

class weightMachineInterface{
    public:
    virtual ~weightMachineInterface() = default;
    virtual double getWeight() = 0; // Get weight in pounds
};

class poundsWeightMachine : public weightMachineInterface {
    double weight; // Weight in pounds
public:
    poundsWeightMachine(double weight) : weight(weight) {}
    double getWeight() override {
        return weight; // Return weight in pounds
    }
};


class weightConverterInterface {
    public:
    virtual ~weightConverterInterface() = default;
    virtual double weightInKg() = 0;
};

class toKgConverter : public weightConverterInterface {
    public:
    weightMachineInterface* wm;
    toKgConverter(weightMachineInterface* wm) : wm(wm) {}
    double weightInKg() override {
        double weight=wm->getWeight();
        return weight * 0.453592; // Convert pounds to kilograms
    }
};

int main() {
    weightMachineInterface* wm = new poundsWeightMachine(150); // 150 pounds
    weightConverterInterface* converter = new toKgConverter(wm);
    
    double weightInKg = converter->weightInKg();
    cout << "Weight in kilograms: " << weightInKg << endl; // Should print 68.18 kg
    
    delete wm;
    delete converter;
    
    return 0;
}

