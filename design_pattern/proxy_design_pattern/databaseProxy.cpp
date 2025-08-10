#include<iostream>

using namespace std;

// few more ussage of proxy design pattern
// Banking system
// centralise logging
// pre/post processing
// security checks

enum userType {
    ADMIN,
    USER,
    GUEST
};
class actualDB{
    public:
        void updateData(int data){
            cout << "Data updated in actual database: " << data << endl;
        }
        string getData(int id){
            cout << "Data retrieved from actual database for ID: " << id << endl;
            return "Data for ID: " + to_string(id);
        }
        void deleteData(int id){
            cout << "Data deleted from actual database for ID: " << id << endl;
        }
        void insertData(int data){
            cout << "Data inserted into actual database: " << data << endl;
        }
};

class proxyDB{
    actualDB* db;
    public:
        proxyDB() {
            db = new actualDB();
        }
        ~proxyDB() {
            delete db;
        }

        void updateData(userType user, int data) {
            if(user == GUEST) {
                cout << "Guest users are not allowed to update data." << endl;
                return;
            }
            else{
                cout << "Proxy: Updating data..." << endl;
                db->updateData(data);
            }
        }

        string getData(userType user, int id) {
            if(user == GUEST || user == USER) {
                cout << "Guest and User are not allowed to retrieve data." << endl;
                return "";
            }
            cout << "Proxy: Retrieving data..." << endl;
            return db->getData(id);
        }

        void deleteData(userType user, int id) {
            if(user == ADMIN){
                cout << "Proxy: Deleting data..." << endl;
                db->deleteData(id);
            } else {
                cout << "Only admin users are allowed to delete data." << endl;
            }
        }

        void insertData(userType user, int data) {
            if(user == GUEST) {
                cout << "Guest users are not allowed to insert data." << endl;
                return;
            }
            cout << "Proxy: Inserting data..." << endl;
            db->insertData(data);
        }
};

int main(){
    proxyDB* db = new proxyDB();
    
    db->insertData(ADMIN, 100);
    db->updateData(ADMIN, 200);
    cout << db->getData(ADMIN, 1) << endl;
    db->deleteData(ADMIN, 1);

    db->insertData(USER, 300);
    db->updateData(USER, 400);
    cout << db->getData(USER, 2) << endl;
    db->deleteData(USER, 2);

    db->insertData(GUEST, 500);
    db->updateData(GUEST, 600);
    cout << db->getData(GUEST, 3) << endl;
    db->deleteData(GUEST, 3);

    delete db;
    
    return 0;
}