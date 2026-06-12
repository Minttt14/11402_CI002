class NumMatrix{
private:
    vector<vector<int>> pre;

public:
    NumMatrix(vector<vector<int>>& matrix){
        if (matrix.empty() || matrix[0].empty()) return;
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        pre.assign(m + 1, vector<int>(n + 1, 0));
        
        for(int i=1; i<=m; ++i){
            for(int j=1; j<=n; ++j) {
                pre[i][j] = matrix[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2){
        return pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1] - pre[row2 + 1][col1] + pre[row1][col1];
    }
};