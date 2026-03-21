#include <bits/stdc++.h> 
using namespace std;

int main(){
	int s;
	long long d;
	
	while(cin >> s >> d){	
		int cnt = 0;
		int tmp = s;
		while(d>tmp){
			d -= tmp;
			tmp++;
			cnt++;
		}
		cout << s + cnt << "\n";
	}

}
