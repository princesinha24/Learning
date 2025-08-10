#include<iostream>
#include<vector>
using namespace std;

class fileSystem{
    protected:
        string name;
    public:
    fileSystem(string name){
        this->name = name;
    }
    virtual void ls(string pre)=0;
    virtual ~fileSystem() = default;
};

class file : public fileSystem{
    public:
    file(string name) : fileSystem(name) {}
    
    void ls(string pre="|") override {
        cout << pre<<"File: " << name << endl;
    }
};

class directory : public fileSystem{
    vector<fileSystem*> children;
    public:
    directory(string name) : fileSystem(name) {
        children = vector<fileSystem*>();
    }

    void ls(string pre="|->") override{
        cout << pre<<"Directory: " << name << endl;
        for(auto child : children){
            child->ls(pre+"->");
        }
    }

    void addItem(fileSystem* item){
        children.push_back(item);
    }
};

int main(){
    directory* root = new directory("root");
    file* file1 = new file("file1.txt");
    file* file2 = new file("file2.txt");
    
    root->addItem(file1);
    
    
    directory* subDir = new directory("subDir");
    file* subFile = new file("subFile.txt");
    
    subDir->addItem(subFile);
    root->addItem(subDir);
    root->addItem(file2);
    root->ls(); // List all files and directories in the root
    
    delete root; // Clean up memory
    return 0;
}