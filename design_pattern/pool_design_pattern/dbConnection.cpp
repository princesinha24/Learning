#include<iostream>
#include<vector>
#include <mutex>
using namespace std;
mutex mtx;
class dbConnection{
    bool isConnected; // To track connection status
    int id;
    public:
        dbConnection(int id) {
            isConnected=false;
            this->id=id;
        } // Constructor initializes connection status
        void connect(){
            cout << "Database connected with id " <<id<< endl;
            isConnected = true; // Set connection status to true
        }
        void disconnect(){
            cout << "Database disconnected." << endl;
            isConnected = false; // Set connection status to false
        }
};

class dbPoolManager{
    static dbPoolManager* instance; // Singleton instance
    int id=0;
    vector<dbConnection*> usedConnectionPool; // Pool of database connections
    vector<dbConnection*> freeConnectionPool; // Pool of free database connections
    int maxConnections = 4; // Maximum number of connections in the pool
    int initialConnections = 2; // Initial number of connections to create
    public:
        dbPoolManager(){
            for (int i = 0; i < initialConnections; i++) {
                freeConnectionPool.push_back(new dbConnection(++id)); // Add to free pool
            }
        }
        static dbPoolManager* getInstance() {
            if (instance == NULL) {
                instance = new dbPoolManager(); // Create a new instance if it doesn't exist
            }
            return instance;
        }
        
        dbConnection* getConnection() {
            mtx.lock();
            if(freeConnectionPool.empty() && usedConnectionPool.size() < maxConnections) {
                freeConnectionPool.push_back(new dbConnection(++id)); // Create a new connection if the pool is empty
            }
            else if(freeConnectionPool.empty()) {
                cout << "No free connections available." << endl;
                return nullptr; // Return null if no connections are available
            }
            dbConnection* connection = freeConnectionPool.back(); // Get the last connection from the free pool
            freeConnectionPool.pop_back(); // Remove it from the free pool
            usedConnectionPool.push_back(connection);
            mtx.unlock();
            return connection; // Return the connection
        }
        
        void releaseConnection(dbConnection* connection) {
            mtx.lock();
            connection->disconnect(); // Disconnect the connection
            // Remove from used pool and add back to free pool
            usedConnectionPool.erase(remove(usedConnectionPool.begin(), usedConnectionPool.end(), connection), usedConnectionPool.end()); // Remove from used pool
            freeConnectionPool.push_back(connection); // Add back to free pool
            mtx.unlock();
        }
};


class Client{
    dbPoolManager* poolManager;
    public:
        Client() {
            poolManager = dbPoolManager::getInstance(); // Get the singleton instance of the pool manager
        }
        
        dbConnection* performDatabaseOperation() {
            dbConnection* connection = poolManager->getConnection(); // Get a connection from the pool
            if (connection) {
                connection->connect(); // Connect to the database
                return connection; // Return the connection
            }
            return NULL;
        }

        void releaseDatabaseConnection(dbConnection* connection) {
            poolManager->releaseConnection(connection); // Release the connection back to the pool
        }
};

dbPoolManager* dbPoolManager::instance = NULL;

int main(){

    Client client; // Create a client instance
    dbConnection* connection1 = client.performDatabaseOperation(); // Perform a database operation
    dbConnection* connection2 = client.performDatabaseOperation(); // Perform another database operation
    dbConnection* connection3 = client.performDatabaseOperation(); // Perform yet another database operation

    Client client2; // Create another client instance
    dbConnection* connection4 = client2.performDatabaseOperation(); // Perform a database operation with
   
    client.releaseDatabaseConnection(connection2); // Release the second connection
    client.releaseDatabaseConnection(connection1); // Release the first connection
    
    dbConnection* connection5 = client2.performDatabaseOperation(); // Perform another database operation
    dbConnection* connection6 = client2.performDatabaseOperation(); // Perform yet another database operation
    
    return 0; // End of program

}