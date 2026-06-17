# [LeetCode] [63] - [Unique Paths II]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 63
- **題目標題:** Unique Paths II
- **題目連結:** [Link to problem](https://leetcode.com/problems/unique-paths-ii/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode63-correct.cpp](./src/s1131408-LeetCode63-correct.cpp)

## 2. 題目說明
有一個機器人位於 ⁠m x n⁠ 網格的左上角，試圖走到右下角，每次只能向右或向下移動，網格中的 ⁠1⁠ 代表障礙物，⁠0⁠ 代表可以通行的空地，機器人無法走進有障礙物的格子
- **輸入:** 一個 ⁠m x n⁠ 的二維整數陣列 ⁠obstacleGrid
- **預期輸出:** 機器人走到右下角共有多少種不同的路徑
- **主要規則或限制**
  1. 障礙物阻斷了格子的通行，任何經過有障礙物格子的路徑都會失效
  2. 答案保證在 32-bit 整數範圍內
- **核心任務:** 在原本的動態規劃 (DP) 基礎上，加入對「障礙物」的判斷

## 3. 思考邏輯與解題策略

### 初始想法

- 先將所有格子預設為 1，然後在雙層迴圈中加上判斷，如果遇到 ⁠obstacleGrid[i][j] == 1⁠，就讓 ⁠dp[i][j] = 0
- 在有障礙物的情況下，第一列（或第一行）的路徑數並不全都是 1，有可能是0，全部初始化為 1 會報錯

### 最終策略
- 遇到障礙物時，該格子的方法數 ⁠dp[i][j] = 0⁠；若是空地，則是 ⁠dp[i-1][j] + dp[i][j-1]⁠
- 程式一開始先判斷 ⁠obstacleGrid[0][0] == 1⁠，如果機器人一出生就在障礙物上，那直接回傳 0
- 第一列和第一行的初始化，採用「繼承前一個格子」的概念 (⁠dp[i][0] = dp[i-1][0]⁠)，只要前面出現過障礙物變成 0，後面的格子就會跟著繼承這個 0

## 4. 虛擬碼

```text
START
方法 uniquePathsWithObstacles(obstacleGrid):
    1. 取得陣列的列數 m 與行數 n
    2. 終極邊界防禦：如果起點 obstacleGrid[0][0] 是 1，直接回傳 0
    
    3. 建立一個大小為 m x n 且預設值皆為 0 的 dp 陣列
    4. 確立起點：dp[0][0] = 1
    
    5. 初始化第一行 (i 從 1 到 m-1)：
       - 如果沒有障礙物，繼承上方格子的值：dp[i][0] = dp[i-1][0]
       - 如果有障礙物，保持為 0
       
    6. 初始化第一列 (j 從 1 到 n-1)：
       - 如果沒有障礙物，繼承左方格子的值：dp[0][j] = dp[0][j-1]
       - 如果有障礙物，保持為 0
       
    7. 主邏輯填表 (i, j 皆從 1 開始)：
       - 如果當前格子是障礙物，dp[i][j] = 0
       - 否則，dp[i][j] = dp[i-1][j] (上方) + dp[i][j-1] (左方)
       
    8. 回傳右下角終點的路徑數 dp[m-1][n-1]
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        
        if (obstacleGrid[0][0] == 1) return 0;
  
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        dp[0][0] = 1;
        
        for(int i=1; i<m; ++i) {
            if (obstacleGrid[i][0] == 0)  dp[i][0] = dp[i - 1][0];
            else dp[i][0] = 0;           
        }
        
        for (int j=1; j<n; ++j) {
            if (obstacleGrid[0][j] == 0) dp[0][j] = dp[0][j - 1];
            else dp[0][j] = 0; 
        }
       
        for(int i=1; i<m; ++i){
            for(int j=1; j<n; ++j){
                if (obstacleGrid[i][j] == 1) dp[i][j] = 0; 
                else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 遇到障礙物截斷加總 (⁠dp = 0⁠) |
| 邊際情況 |  | (⁠if (grid[0][0] == 1) return 0⁠)處理「起點即為障礙物」的死局 |
| 輸出處理 |  | 正確計算含有障礙物的網格有幾種不同路徑數 |

### 反思
- 這題讓我學到，在動態規劃的網格問題中，「障礙物」或「不可行走的區域」在數學狀態上的意義，就是「走到這裡的方法數為 0」，只要把有障礙物的地方強制設為 0，這個 0 就會在狀態轉移的過程中自然地與其他路線相加，不干擾其他合法路徑的計算
- 這題目前的空間複雜度是 O(M \times N)，不過當下這一列的計算，只依賴於上一列和當前列的左邊，因此可以把空間壓縮成一維陣列 (1D Array)，長度為 ⁠n⁠ ，遇到石頭時就把對應位置設為 0，否則 ⁠dp[j] += dp[j-1]⁠，這樣就能把空間複雜度降到 O(N)