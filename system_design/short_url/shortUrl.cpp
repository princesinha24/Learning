#include<iostream>
#include<unordered_map>
#include<queue>
using namespace std;

class RandomString{
    queue<string>randomStack;
    vector<char>charSet;
    int short_url_length;
    
    void createQueue(int l,string s){
        if(l==short_url_length){
            randomStack.push(s);
            return;
        }
        for(int i=0;i<charSet.size();i++){
            createQueue(l+1,s+charSet[i]);
        }
    }

    void printQueue(){
        while(!randomStack.empty()){
            cout<<randomStack.front()<<endl;
            randomStack.pop();
        }
    }
    public: 
        RandomString(int length=5){
            short_url_length = length;
            charSet.clear();
            
            for(int i=0;i<26;i++){
                charSet.push_back('a'+i);
                charSet.push_back('A'+i);
            }
            for(int i=0;i<10;i++){
                charSet.push_back('0'+i);
            }
            createQueue(0,"");
            // printQueue();
        }
        string generateRandom(){
            string s = randomStack.front();
            randomStack.pop();
            return s;
        }
        void deleteRandom(string s){
            randomStack.push(s);
        }

};

class URL{
    string url;
    int count;
    public:
    URL(string url,string shortURL){
        this->url = url;
        count=0;
    }
    string getShortURL(){
        count++;
        return url;
    }
};

class shortURL{
    unordered_map<string,URL*>urlDictonary;
    RandomString* randomGenerator;
    
    public:
        shortURL(int length=5){
            urlDictonary.clear();
            randomGenerator = new RandomString(length);
        }
        string addURL(string longUrl){
            string shortURL = randomGenerator->generateRandom();
            urlDictonary[shortURL] = new URL(longUrl,shortURL);
            return shortURL;
        }

        string getURL(string shortUrl){
            if(urlDictonary.find(shortUrl)==urlDictonary.end()){
                return "";
            }
            string longURL = urlDictonary[shortUrl]->getShortURL();
            return longURL;
        }

        void deleteURL(string URL){
            if(urlDictonary.find(URL)==urlDictonary.end()){
                return;
            }
            urlDictonary.erase(URL);
            randomGenerator->deleteRandom(URL);
        }

};

int main(){
    shortURL* urlShortener=new shortURL(3);
    string longURL = "https://www.google.com";
    string shortURL = urlShortener->getURL(longURL);
    cout<<shortURL<<endl;
    cout<<urlShortener->addURL(longURL)<<endl;
    cout<<urlShortener->addURL("https://www.linkdin.com")<<endl;
    cout<<urlShortener->addURL("https://www.linkdin.com1")<<endl;
}