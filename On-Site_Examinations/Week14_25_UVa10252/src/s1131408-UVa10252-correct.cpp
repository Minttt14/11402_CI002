#include<bits/stdc++.h>
using namespace std;

int main(){	
	string s1, s2;
	while(getline(cin, s1)){
		getline(cin, s2);
		
		map<char, int> mp_a;
		map<char, int> mp_b;
		
		for(int i=0; i<s1.length(); ++i){
			mp_a[s1[i]] ++;
		}
		
		for(int i=0; i<s2.length(); ++i){
			mp_b[s2[i]] ++;
		}
		
		for(char c = 'a'; c <= 'z'; c++){
			int k = min(mp_a[c], mp_b[c]);
			
			while(k--){
				cout << c;
			}
		}
		cout << "\n";
	}
}