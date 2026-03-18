class Solution {
public:
    bool isPalindrome(int x) {
        string s;
        s = to_string(x);
        for(int i=0; i<s.length()/2; ++i){
            if(s[i] != s[s.length() - 1 - i]){
             return false;
            }
        }
        return true;
    }
};

// #include <bits/stdc++.h>
// using namespace std;

// int main(){
//     bool palindrome = true;
//     string x;
//     cin >> x;
//     for(int i=0; i<x.length()/2; ++i){
//         if(x[i] != x[x.length() - 1 - i]){
//             palindrome = false;
//             break;
//         }
//     }
//     if(palindrome) cout << "true\n";
//     else cout << "false\n";
// }