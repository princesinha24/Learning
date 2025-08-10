#include <iostream>
#include <vector>
using namespace std;

class bidderInterface; // Forward declaration

// Abstract Mediator
class AuctionMediator {
protected:
    string auctionName;
public:
    AuctionMediator(string name) : auctionName(name) {}
    virtual ~AuctionMediator() {}
    virtual void addBidder(bidderInterface* bidder) = 0;
    virtual void notifyBidders(bidderInterface* bidder, int amount) = 0;
};

// Abstract Bidder Interface
class bidderInterface {
protected:
    AuctionMediator* mediator;
public:
    bidderInterface(AuctionMediator* mediator) : mediator(mediator) {}
    virtual ~bidderInterface() {}
    virtual void placeBid(int amount) = 0;
    virtual void receiveNotification(string message) = 0;
    virtual string getName() = 0;
};

// Concrete Bidder
class bidder : public bidderInterface {
    string name;
public:
    bidder(AuctionMediator* mediator, string name) : bidderInterface(mediator), name(name) {
        mediator->addBidder(this); // register with the auction
    }

    void placeBid(int amount) override {
        cout << name << " is placing a bid of " << amount << endl;
        mediator->notifyBidders(this, amount);
    }

    void receiveNotification(string message) override {
        cout << name << " received notification: " << message << endl;
    }

    string getName() override {
        return name;
    }
};

// Concrete Mediator
class Auction : public AuctionMediator {
    vector<bidderInterface*> bidders;
public:
    Auction(string name) : AuctionMediator(name) {}

    void addBidder(bidderInterface* bidder) override {
        bidders.push_back(bidder);
    }

    void notifyBidders(bidderInterface* sender, int amount) override {
        for (auto b : bidders) {
            if (b != sender) {
                b->receiveNotification(sender->getName() + " placed a bid of " + to_string(amount));
            }
        }
    }
};

// Main function to demonstrate
int main() {
    AuctionMediator* auction=new Auction("Art Auction");

    bidderInterface* b1=new bidder(auction, "Alice");
    bidderInterface* b2=new bidder(auction, "Bob");
    bidderInterface* b3=new bidder(auction, "Charlie");

    b1->placeBid(100);
    b2->placeBid(150);
    b3->placeBid(200);

    return 0;
}