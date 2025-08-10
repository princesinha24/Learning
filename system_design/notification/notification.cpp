#include<iostream>
#include<unordered_map>
using namespace std;


class Log{
    unordered_map<string,vector<string>>logs;
    public:
    Log(){
        logs["message"].clear();
        logs["notification"].clear();
        logs["top"].clear();
    }
    void addLog(string message,string type,string date){
        // implement in further classes
        return ;
    }
};

class errorLog : public Log{
    public:
    void addLog(string message,string fileName,string date){
        logs[fileName].push_back(date+"[error]"+message);
    }
};

class warningLog : public Log{
    public:
    void addLog(string message,string fileName,string date){
        logs[fileName].push_back(date+"[warn]"+message);
    }
};

class normalLog : public Log{
    public:
    void addLog(string message,string fileName,string date){
        logs[fileName].push_back(date+message);
    }
};

class Client{
    string name;
    string email;
    string phone;
    public:
    Client(string name,string email,string phone){
        this->name=name;
        this->email=email;
        this->phone=phone;
    }
};

class NotificationAPP{
    vector<Notification*>notifications;
    public:
    Notification(string message,string type,string date,Client* client){
        this->message=message;
        this->type=type;
        this->date=date;
        this->client=client;
    }
};

int main(){

}


/*
    log type -> warn, error, info
    log -> message, type, date
    client -> name, email, phone
    Notification -> message, type, date, client, notify
    User interface -> addClient, addNotification, getLogs, 

*/