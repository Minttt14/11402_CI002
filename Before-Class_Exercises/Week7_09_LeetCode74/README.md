# [LeetCode] [74] - [Search a 2D Matrix]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 74
- **題目標題:** Search a 2D Matrix
- **題目連結:** [Link to problem](https://leetcode.com/problems/search-a-2d-matrix/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode74-correct.cpp](./src/s1131408-LeetCode74-correct.cpp)

## 2. 題目說明
給一個 m x n 的整數矩陣 matrix 和一個目標值 target，判斷 target 是否存在於矩陣中
- **輸入:** 二維整數陣列 matrix，以及一個整數 target
- **預期輸出:** 布林值 (true / false)
- **主要規則或限制**
  1. 每行的整數從左到右按升冪排序
  2. 每行的第一個整數必定大於前一行的最後一個整數
- **核心任務:** 利用矩陣已排序的特性，設計高效的搜尋演算法

## 3. 思考邏輯與解題策略

### 初始想法

- 寫兩個 for 迴圈直接把整個矩陣掃描一遍
- 時間複雜度高

### 最終策略

- 從右上角出發，往左走數字一定會變小，往下走數字一定會變大
- 如果當前數字 == target，找到答案，回傳 true；當前數字 > target，代表這個數字太大了，往左走（col--）；當前數字 < target，往下走（row++）；找不到就回傳 false

## 4. 虛擬碼

```text
START
1. 邊界檢查：如果 matrix 為空，直接回傳 false
2. 取得矩陣的列數 m 和行數 n
3. 初始化指標，從右上角開始：
   - row = 0
   - col = n - 1
4. 當指標沒有越界時 (row < m 且 col >= 0) 執行迴圈：
   a. 如果 matrix[row][col] == target：
      - 找到了，回傳 true
   b. 否則如果 matrix[row][col] > target：
      - 當前值太大，往左移動 (col--)
   c. 否則 (matrix[row][col] < target)：
      - 當前值太小，往下移動 (row++)
5. 迴圈結束代表找不到，回傳 false
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        int row = 0;
        int col = n - 1;
        
        while(row < m && col >= 0){
            if (matrix[row][col] == target) return true;
            else if(matrix[row][col] > target) col--; 
            else row++;
        }
        return false;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 把二維陣列當作二元搜尋樹走訪 |
| 邊際情況 |  | 完美相容 |
| 輸出處理 |  | 正確回傳布林值 |

### 反思
- 學會了把二維陣列當作「二元搜尋樹」來看待，只要選對起點（右上角），往左走數字變小、往下走數字變大，這種利用幾何單調性的「階梯式搜尋法」不僅邏輯乾淨，還完美避開了一維轉二維索引時常見的數學錯誤
- 下次遇到類似題目時，可以把二維陣列想像成一條攤平的一維陣列，直接套用標準的 Binary Search，配合索引轉換公式 row = mid / n 與 col = mid % n，將時間複雜度進一步壓縮到 O(log(M * N))