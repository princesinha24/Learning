// Write KMP algorithm for string matching

#include <iostream>
#include <vector>
using namespace std;
// Function to perform KMP string matching algorithm
vector<int> KMP(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m, 0); // Longest Prefix Suffix array
    vector<int> result; // To store the starting indices of matches
    int j = 0; // Index for pattern
    int i = 0; // Index for text
    // Preprocess the pattern to create the LPS array
    for (int len = 0, i = 1; i < m;) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else if (len) {
            len = lps[len - 1]; // Use the previous LPS value
        }
        else {
            lps[i] = 0;
            i++;
        }
    }
    // Start matching the pattern with the text
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            result.push_back(i - j); // Match found, store the index
            j = lps[j - 1]; // Reset j using LPS array
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j) {
                j = lps[j - 1]; // Use the previous LPS value
            }
            else {
                i++; // Move to the next character in text
            }
        }
    }
    return result; // Return the list of starting indices of matches
} 

// Example usage
int main() {
    string text = "ababcababcabc";
    string pattern = "abc";
    vector<int> matches = KMP(text, pattern);
    cout << "Pattern found at indices: ";
    for (int index : matches) { 
        cout << index << " ";
    }
    cout << endl;
    return 0;
}
    