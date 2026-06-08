#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int cnt = 0;
    while(getline(cin, s) && s != ""){
        if(cnt > 0) cout << "\n";
        cnt ++;

        map<char, int> mp;
        for(int i=0; i<s.length(); ++i){
            mp[s[i]] ++;
        }

        vector<pair<char, int>> v(mp.begin(), mp.end());
        sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b){
            if(a.second != b.second){
                return a.second < b.second;
            }
            else{
                return a.first > b.first;
            }
        });

        for (pair<char, int> i : v) {
            cout << (int)i.first << " " << i.second << "\n";
        }
    }
}