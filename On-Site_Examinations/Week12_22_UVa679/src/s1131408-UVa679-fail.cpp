# include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	while(cin >> n && n != -1){
		
		for(int i=0; i<n; ++i){
			int depth, ball;
			cin >> depth >> ball;
			
			int left = 2;
			int right = 3;
			for(int i=1; i<depth-1; ++i){
				left *= 2;
				right *= 2;
			}
			
			int tmp;
			if(ball % 2 != 0){
				tmp = (ball / 2);
				cout << left + tmp << "\n";
			}
			else {
				tmp = (ball / 2) - 1;
				cout << right + tmp << "\n";
			}		
		}	
	}
}