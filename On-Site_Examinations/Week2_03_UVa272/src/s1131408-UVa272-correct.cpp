#include <bits/stdc++.h>
using namespace std;

int main(){

    string s;
    int cnt = 1;

    while(getline(cin, s)){
        for(int i=0; i<s.length(); ++i){

        if(s[i] == '\"'){
            if(cnt % 2 != 0){
                cout<<"``";
            }
            else{
                cout<<"''";
            } 
            cnt++;
        }
        else{
            cout<<s[i];
        }
    }
    cout<<"\n";
    }
}
