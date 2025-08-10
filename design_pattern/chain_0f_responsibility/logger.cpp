#include<iostream>

using namespace std;

// Chain of Responsibility Design Pattern Implementation for Logging few more can be used like ATM, Vendor Machine, etc.

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger{
    
    public:
        Logger* nextLogger; // Pointer to the next logger in the chain
        Logger(Logger* nextLogger){
            this->nextLogger = nextLogger; // Initialize the next logger
        }
        virtual ~Logger() = default;
        virtual void log(int logLevel, string& message) = 0; // Pure virtual function for logging
};

class DebugLogger : public Logger {
    public:
        DebugLogger(Logger* nextLogger): Logger(nextLogger) {}
        void log (int logLevel, string& message) override {
            if (logLevel == DEBUG) {
                cout << "Debug: " << message << endl; // Log debug messages
            } else if (nextLogger != nullptr) {
                nextLogger->log(logLevel, message); // Pass to the next logger
            }
        }
};

class InfoLogger : public Logger {
    public:
        InfoLogger( Logger* nextLogger): Logger(nextLogger) {}
        void log (int logLevel, string& message) override {
            if (logLevel == INFO) {
                cout << "Info: " << message << endl; // Log info messages
            } else if (nextLogger != nullptr) {
                nextLogger->log(logLevel, message); // Pass to the next logger
            }
        }
};

class WarningLogger : public Logger {
    public:
        WarningLogger(Logger* nextLogger): Logger(nextLogger) {}
        void log (int logLevel, string& message) override {
            if (logLevel == WARNING) {
                cout << "Warning: " << message << endl; // Log warning messages
            } else if (nextLogger != nullptr) {
                nextLogger->log(logLevel, message); // Pass to the next logger
            }
        }
};

class ErrorLogger : public Logger {
    public:
        ErrorLogger(Logger* nextLogger): Logger(nextLogger) {}
        void log (int logLevel, string& message) override {
            if (logLevel == ERROR) {
                cout << "Error: " << message << endl; // Log error messages
            } else if (nextLogger != nullptr) {
                nextLogger->log(logLevel, message); // Pass to the next logger
            }
        }
};

int main(){
    Logger* log = new DebugLogger(
        new InfoLogger(
            new WarningLogger(
                new ErrorLogger(nullptr) // End of the chain
            )
        )
    );
    string message = "This is a test message"; // Example message
    log->log(DEBUG, message); // Log a debug message
    log->log(ERROR, message); // Log an error message
    log->log(INFO, message); // Log an info message
    delete log; // Clean up the logger chain
    return 0; // Exit the program
}