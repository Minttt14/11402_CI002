#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, m;
	int cnt = 1;
	while(cin >> n >> m && n != 0 || m != 0){
		
		char field[110][110] = {0};
		
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				cin >> field[i][j];
				if(field[i][j] == '.') field[i][j] = '0';
			}
		}
		
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				if(field[i][j] != '*'){
					if(field[i-1][j-1] == '*') field[i][j] ++;
					if(field[i][j-1] == '*') field[i][j] ++;
					if(field[i+1][j-1] == '*') field[i][j] ++;
					if(field[i-1][j] == '*') field[i][j] ++;
					if(field[i+1][j] == '*') field[i][j] ++;
					if(field[i-1][j+1] == '*') field[i][j] ++;
					if(field[i][j+1] == '*') field[i][j] ++;
					if(field[i+1][j+1] == '*') field[i][j] ++;
				}	
			}
		}
		
		cout << "Field #" << cnt << ":\n";
		cnt ++;
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				cout << field[i][j];
			}
			cout << "\n";
		}
		cout << "\n";
	}
}