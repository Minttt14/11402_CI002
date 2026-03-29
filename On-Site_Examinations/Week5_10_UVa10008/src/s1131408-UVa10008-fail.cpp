#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    cin.ignore(); 
    
    map<char, int> mp;
    while (n--) {
        string s;
        getline(cin, s);
        for (int i = 0; i < s.length(); i++) {
            if (isalpha(s[i])) {
                mp[toupper(s[i])]++; 
            }
        }
    }

    vector<pair<char, int>> v(mp.begin(), mp.end());

    sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b) {
        if (a.second != b.second) 
            return a.second > b.second; 
        return a.first < b.first;       
    });

    for (pair<char, int> i : mp) {
        cout << i.first << " " << i.second << "\n";
    }
}