#include<iostream>
#include<vector>
using namespace std;


class Card{
    int balance;
    bool isInserted;
    string pin;
    
    public:
        Card(int amount, string defaultPin="1234"){
            pin=defaultPin;
            balance=amount;
            isInserted=false;
        }

        void removeCard(){
            isInserted=false;
        }

        bool setPin(string pin){
            if(this->pin!=pin){
                this->pin=pin;
                return true;
            }
            return false;
        }

        bool checkPIN(string pin){
            return this->pin==pin;
        }

        int getBalance(){
            return balance;
        }
        
        bool isCardInserted(){
            if(isInserted){
                cout<<"Card already inserted"<<endl;
                return false;
            }
            isInserted=true;
            return true;
        }

        void addAmount(int money){
            balance+=money;
        }

        bool withdrawAmount(int money){
            if(balance>=money){
                balance-=money;
                removeCard();
                return true;
            }
            removeCard();
            return false;
        }
};

class Account{
    
    vector<Card*> cards;
    string username;
    public:
    Account(string username){
        this->username = username;
        cards.empty();
    }
    Card* addCard(int balance=0){
        Card* card=new Card(balance);
        cards.push_back(card);
        return card;
    }
};


class ATM{
    Card* card;
    bool validatepin(Card* card){
        string pin;
        cout<<"Enter pin"<<endl;
        cin>>pin;
        if(card->checkPIN(pin)){
            return true;
        }
        cout<<"Invalid pin"<<endl;
        return false;
    }
    void withdraw(){
        int amount;
        cout<<"Enter amount"<<endl;
        cin>>amount;
        if(card->withdrawAmount(amount)){
            cout<<"Amount withdrawn"<<endl;
        }
        else{
            cout<<"Insufficient balance"<<endl;
        }
    }

    void deposit(){
        int amount;
        cout<<"Enter amount"<<endl;
        cin>>amount;
        card->addAmount(amount);
        cout<<"Amount deposited"<<endl;
    }

    void setPin(){
        string newPin;
        cout<<"Enter new pin"<<endl;
        cin>>newPin;
        if(card->setPin(newPin)){
            cout<<"Pin changed"<<endl;
        }
        else{
            cout<<"Invalid pin"<<endl;
        }
    }

    void SelectOption(){
        cout<<"1. Withdraw"<<endl;
        cout<<"2. Deposit"<<endl;
        cout<<"3. Check Balance"<<endl;
        cout<<"4. Change Pin"<<endl;
        cout<<"5. Exit"<<endl;
        int option;
        cin>>option;
        switch(option){
            case 1:
                withdraw();
                SelectOption();
                break;
            case 2:
                deposit();
                SelectOption();
                break;
            case 3:
                cout<<"Balance: "<<card->getBalance()<<endl;
                SelectOption();
                break;
            case 4:
                setPin();
                SelectOption();
                break;
            case 5:
                card->removeCard();
                break;
            default:
                cout<<"Invalid option"<<endl;
        }
    }
    public:
    static ATM* ATM_instance;
    ATM(){
        if(ATM_instance!=NULL){
            cout<<"ATM already in use"<<endl;
        }
        else{
            ATM_instance=this;
        }
    }

    Card* CreateCard(Account* account, int balance=0){
        Card* card=account->addCard(balance);
        return card;
    }

    Account* CreateAccount(string username){
        Account* account=new Account(username);
        return account;
    }

    void insertCard(Card* card){
        if(!card->isCardInserted()){
            return;
        }
        if(!validatepin(card)){
            card->removeCard();
        }
        this->card=card;
        SelectOption();
        card->removeCard();
        this->card=NULL;
        cout<<"Thanks for Choosing Us"<<endl;
    }

};

ATM* ATM::ATM_instance=NULL;
int main(){
    ATM* atm=new ATM();
    Account* account=atm->CreateAccount("Rahul");
    Card* card=atm->CreateCard(account);
    atm->insertCard(card);
    
    return 0;
}



/*
ATM system
exposed APIs:
1. void insertCard(Card card)
2. void removeCard()
3. void enterPin(string pin)
4. void withdrawCash(int amount)
5. int getBalance()
6. void depositCash(int amount)
7. bool setNewPin(string oldPin, string newPin)
8. vector<transection> getStatement()


entity 
Account -> card, username
Card -> balance, isInserted, pin
Cash -> number
statement -> account, amount, transection
transection -> account, amount, type, date

*/