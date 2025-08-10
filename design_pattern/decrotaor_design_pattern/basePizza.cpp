#include <iostream>
using namespace std;

class Pizza{
    public:
        virtual ~Pizza() = default;
        virtual double getCost() const = 0;
};

class plainPizza : public Pizza {// Pointer to basePizza for decoration
    public:

        double getCost() const override {
            return 5.0; // Cost of a plain pizza
        }
};

class Magreeta : public Pizza {
    public:
    double getCost() const override {
        return 5.0; // Cost of a plain pizza
    }
};

class DecoratorPizza : public Pizza {
    protected:
        Pizza* pizza;
    public:
        DecoratorPizza(Pizza* p) {
            this->pizza = p; // Initialize with a base pizza
        }
        virtual ~DecoratorPizza() {
            delete pizza; // Clean up the base pizza
        }
        double getCost() const override {
            return pizza->getCost(); // Delegate cost calculation to the base pizza 
        }   
};

class CheeseDecorator : public DecoratorPizza {
    public:
        CheeseDecorator(Pizza* p) : DecoratorPizza(p) {}
        double getCost() const override {
            return DecoratorPizza::getCost() + 1.5; // Add cost of cheese
        }
};

class PepperoniDecorator : public DecoratorPizza {
    public:
        PepperoniDecorator(Pizza* p) : DecoratorPizza(p) {}
        double getCost() const override {
            return DecoratorPizza::getCost() + 2.0; // Add cost of pepperoni
        }
};  

class VeggieDecorator : public DecoratorPizza {
    public:
        VeggieDecorator(Pizza* p) : DecoratorPizza(p) {}
        double getCost() const override {
            return DecoratorPizza::getCost() + 1.0; // Add cost of veggies
        }
};  


int main() {
    Pizza* myPizza = new Magreeta();
    myPizza = new CheeseDecorator(new PepperoniDecorator( new CheeseDecorator(myPizza)));
    cout << "Total cost of pizza: " << myPizza->getCost() << endl;
    delete myPizza; // Clean up the pizza
    return 0;
}