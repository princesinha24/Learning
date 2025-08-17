#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findOrder(string dict[], int n, int k) {
        vector<int>a[k];
        vector<int>order(k,0);
        for(int i=1;i<n;i++){
            for(int j=0;j<min(dict[i-1].length(),dict[i].length());j++){
                if(dict[i-1][j]!=dict[i][j]){
                    a[dict[i-1][j]-'a'].push_back(dict[i][j]-'a');
                    order[dict[i][j]-'a']++;
                    break;
                }
            }
        }
        string ans="";
        for(int i=0;i<k;i++){
            if(order[i]==0){
                ans+=char(i+'a');
            }
        }
        for(int i=0;i<ans.length();i++){
            for(int j=0;j<a[ans[i]-'a'].size();j++){
                order[a[ans[i]-'a'][j]]--;
                if(order[a[ans[i]-'a'][j]]==0){
                    ans+=char(a[ans[i]-'a'][j]+'a');
                }
            }
        }
        return ans;
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    string dict[n];
    
    for (int i = 0; i < n; ++i) {
        cin >> dict[i];
    }
    
    Solution obj;
    string order = obj.findOrder(dict, n, k);
    
    cout << order << endl;
    
    return 0;
}