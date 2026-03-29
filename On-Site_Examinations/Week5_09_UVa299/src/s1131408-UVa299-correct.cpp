#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    int L;
    while(N--){
        cin >> L;
        int arr[L];
        for(int i=0; i<L; ++i){
            cin >> arr[i];
        }

        int cnt = 0;
        for(int i = 0; i < L-1; ++i){
            for(int j = 0; j < L-i-1; ++j){
                if(arr[j]>arr[j+1]){
                    swap(arr[j], arr[j+1]);
                    cnt++;
                }
            }
        }
        cout<<"Optimal train swapping takes " << cnt <<" swaps.\n";
    }
}