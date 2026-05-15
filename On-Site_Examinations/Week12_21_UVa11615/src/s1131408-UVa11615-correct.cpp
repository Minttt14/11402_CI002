# include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	while(n--){
		int depth, a, b , da, db;
		cin >> depth >> a >> b;
		
		int member = pow(2, depth) -1;
		
		for(int i=1; i<=depth; ++i){
			if(a < pow(2, i)){
				da = i;
				break;
			}
		}
		
		for(int i=1; i<=depth; ++i){
			if(b < pow(2, i)){
				db = i;
				break;
			}
		}
		int tmp1 = (depth - da);
		int tmp2 = (depth - db);
		int a_child = 0;
		int b_child = 0;
		
		for(int i=1; i<=tmp1; ++i){
			a_child += pow(2, i);
		}
		for(int i=1; i<=tmp2; ++i){
			b_child += pow(2, i);
		}
		
		if(da == depth || db == depth) cout << member << "\n";
		else if(da > db) cout << member - a_child << "\n";
		else if(da < db) cout << member - b_child << "\n";
		else if(da = db) cout << member - a_child << "\n";
	}	
}