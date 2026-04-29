#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();
    while (n--) {
        string s;
        stack<char> st;
        getline(cin, s);
        bool valid = true;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(' || s[i] == '[') {
                st.push(s[i]);
            } 
            else if (s[i] == ')' || s[i] == ']') {
                if (st.empty()) {
                    valid = false;
                    break; 
                }
                if (s[i] == ')' && st.top() != '(') {
                    valid = false;
                    break;
                }
                if (s[i] == ']' && st.top() != '[') {
                    valid = false;
                    break;
                }
                st.pop();
            }
        }
        if (valid && st.empty()) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}