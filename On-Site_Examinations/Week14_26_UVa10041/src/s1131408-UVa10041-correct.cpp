#include<bits/stdc++.h>
using namespace std;

int main(){	
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> v(n);
		
		for(int i=0; i<n; ++i){
			cin >> v[i];
		}
		sort(v.begin(), v.end());
		
		int middle = v[n/2];
		
		int cnt = 0;
		for(int i : v){
			cnt += abs(middle - i);
		}
		cout << cnt << "\n";
	}
}