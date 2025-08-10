#include<iostream>
#include<string>
#include<map>
using namespace std;

class interfaceChar{
    public:
        virtual void display() = 0; // Pure virtual function
        virtual ~interfaceChar() {} // Virtual destructor
};

class Character : public interfaceChar {
    char c;
public:    
    Character(char c) {
       this->c = c; 
    }
    void display() override {
        cout << c;
    }
};

class CharacterFactory{
    map<char, interfaceChar*> charMap;
    int charCount = 0; // To keep track of the number of characters created
    public:
        interfaceChar* getCharacter(char c) {
            if (charMap[c] == NULL) {
                charMap[c] = new Character(c);
                charCount++;
            }
            return charMap[c];
        }
        
        int getCharacterCount() const {
            return charCount;
        }

        ~CharacterFactory() {
            for (auto& pair : charMap) {
                delete pair.second; // Clean up allocated memory
            }
        }
};

int main(){
    CharacterFactory factory;
    string text = "Hello World! 123 Prince Sinha";
    
    for (char c : text) {
        interfaceChar* character = factory.getCharacter(c);
        character->display();
    }
    cout << "\nTotal unique characters created: " << factory.getCharacterCount() << endl;
    cout << endl; // New line after displaying all characters
    return 0;
}