# [LeetCode] [64] - [Minimum Path Sum]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 64
- **題目標題:** Minimum Path Sum
- **題目連結:** [Link to problem](https://leetcode.com/problems/minimum-path-sum/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode64-correct.cpp](./src/s1131408-LeetCode64-correct.cpp)

## 2. 題目說明
給一個包含非負整數的 ⁠m x n⁠ 網格 ⁠grid⁠，找出一個從左上角走到右下角的路徑，使得路徑上的數字總和最小
- **輸入:** 一個 ⁠m x n⁠ 的二維整數陣列 ⁠grid
- **預期輸出:** 從左上到右下最小的路徑數字總和
- **主要規則或限制**
  1. 每次只能向下或者向右移動一步
  2. 1 \le m, n \le 200
- **核心任務:** 在眾多可能到達右下角的路徑中，利用動態規劃 (DP) 找出成本最低的走法

## 3. 思考邏輯與解題策略

### 初始想法

- 宣告一個與 ⁠grid⁠ 大小相同的二維陣列 ⁠dp⁠，dp[i][j]⁠ 代表走到格子 ⁠(i, j)⁠ 的最小路徑和，狀態轉移方程式為 ⁠dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
- 需要額外開闢一塊 O(M \times N) 的記憶體空間

### 最終策略
- 原地修改的動態規劃，⁠grid[i][j]⁠ 原本的值在加總後就不會再被單獨使用了，因此可以直接把算好的結果覆蓋回原來的 ⁠grid⁠ 上
- 第一列因為沒有上方格子，只能一直從左邊走過來，所以讓它累加左邊的格子；第一行因為沒有左邊格子，只能一直從上面走下來，所以讓它累加上面的格子。

## 4. 虛擬碼

```text
START
方法 minPathSum(grid):
    1. 取得網格的列數 m 與行數 n
    
    2. 初始化第一行 (只能由上往下走)：
       從 i = 1 到 m - 1，grid[i][0] 加上 grid[i-1][0]
       
    3. 初始化第一列 (只能由左往右走)：
       從 j = 1 到 n - 1，grid[0][j] 加上 grid[0][j-1]
       
    4. 狀態轉移填表：
       雙層迴圈遍歷剩下的網格 (i 從 1 到 m-1，j 從 1 到 n-1)：
           grid[i][j] 加上 min(grid[i-1][j], grid[i][j-1])
           
    5. 回傳右下角的數值 grid[m-1][n-1]
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        for(int i=1; i<m; ++i){
            grid[i][0] += grid[i - 1][0];
        }

        for(int j=1; j<n; ++j){
            grid[0][j] += grid[0][j - 1];
        }
        
        for(int i=1; i<m; ++i){
            for(int j=1; j<n; ++j){
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            }
        }
        return grid[m - 1][n - 1];
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 直接修改輸入的 ⁠grid⁠，把算過的格子變成 DP 狀態 |
| 邊際情況 |  | 預先獨立處理第 0 列與第 0 行 |
| 輸出處理 |  | 正確計算最小路徑的數字總和 |

### 反思
- 這題讓我學到，當原陣列的資料在參與計算後不需要被保留時，直接覆寫原陣列 (In-place) 能將空間複雜度降至 O(1) 
- 類似題目如果規定不可以直接修改原陣列的話，可以開一個大小為 O(N) 的一維滾動陣列 (Rolling Array) 來做優化