class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2){
        vector<int> rank(1001, 1001);
        
        for(int i=0; i<arr2.size(); ++i){
            rank[arr2[i]] = i;
        }

        sort(arr1.begin(), arr1.end(), [&](int a, int b){
            if (rank[a] != rank[b]) {
                return rank[a] < rank[b];
            }
            return a < b;
        });
        return arr1;
    }
};