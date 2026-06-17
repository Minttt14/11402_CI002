# [LeetCode] [1143] - [Longest Common Subsequence]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1143
- **題目標題:** Longest Common Subsequence
- **題目連結:** [Link to problem](https://leetcode.com/problems/longest-common-subsequence/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1143-correct.cpp](./src/s1131408-LeetCode1143-correct.cpp)

## 2. 題目說明
給兩個字串 ⁠text1⁠ 和 ⁠text2⁠，請回傳這兩個字串的最長共同子序列的長度，如果沒有共同子序列，則回傳 0
- **輸入:** 兩個字串 text1 與 text2
- **預期輸出:** 最長共同子序列的長度
- **主要規則或限制**
  1. $1 \le text1.length, text2.length \le 1000$
  2. 輸入字串僅包含小寫英文字母
- **核心任務:** 在保持字元相對順序的前提下，高效率地找出兩個字串最大的重疊部分

## 3. 思考邏輯與解題策略

### 初始想法

- 針對 text1 產生所有的子序列 (共有 $2^M$ 種)，再針對 text2 產生所有的子序列 (共有 $2^N$ 種)，然後一一比對找出最長的一組
- 時間複雜度高，會導致超時

### 最終策略
- 2D 動態規劃法，建立一個二維陣列 dp，dp[i][j] 代表 text1 的前 i 個字元與 text2 的前 j 個字元的 LCS 長度
- 將 dp 陣列的大小設為 (m + 1) x (n + 1)，並將第 0 列與第 0 行全設為 0，代表「當其中一個字串為空時，LCS 長度自然為 0」，能完美避開迴圈中 i-1 或 j-1 變成負數的越界崩潰

## 4. 虛擬碼

```text
START
方法 longestCommonSubsequence(text1, text2):
    1. 取得兩個字串的長度，分別為 m 和 n
    
    2. 建立一個大小為 (m + 1) x (n + 1) 的二維陣列 dp，並預設全為 0
       (利用 +1 技巧處理空字串的邊界條件)
       
    3. 雙層迴圈填表：
       - 外層 i 從 1 到 m (對應 text1)
       - 內層 j 從 1 到 n (對應 text2)
         - 如果當前字元相同 (text1[i-1] == text2[j-1]):
             dp[i][j] = 左上方格子的值 + 1 (即 dp[i-1][j-1] + 1)
         - 如果當前字元不同:
             dp[i][j] = 上方與左方格子的最大值 (即 max(dp[i-1][j], dp[i][j-1]))
             
    4. 回傳右下角終點的結果 dp[m][n]
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for(int i=1; i<=m; ++i){
            for(int j=1; j<=n; ++j){
                if(text1[i - 1] == text2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  |透過狀態轉移記錄子問題的最佳解 |
| 邊際情況 |  | 利用 m+1, n+1 的 Padding 吸收邊界條件 |
| 輸出處理 |  | 正確輸出最長共同子序列 |

### 反思
- 學到了在處理字串或陣列的動態規劃時，只要狀態會依賴到 i-1，將陣列多開一格 (m+1) 並將索引 0 視為「空字串/無元素」能夠簡化防越界判斷
- 計算第 i 列的資料時，只會用到第 i-1 列的資料，因此其實不需要儲存整個矩陣，只需要保留兩個長度為 $N+1$ 的一維陣列 (一個代表 current，一個代表 previous)，互相滾動更新即可，能將空間複雜度壓縮至 $O(N)$