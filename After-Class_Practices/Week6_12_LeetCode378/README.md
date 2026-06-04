# [LeetCode] [378] - [Kth Smallest Element in a Sorted Matrix]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 378
- **題目標題:** Kth Smallest Element in a Sorted Matrix
- **題目連結:** [Link to problem](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode378-correct.cpp](./src/s1131408-LeetCode378-correct.cpp)

## 2. 題目說明
給一個 n x n 的矩陣 matrix，每行每列都按照升冪順序排列，找出矩陣中第 k 小的元素
- **輸入:** 二維整數陣列 matrix，以及一個整數 k
- **預期輸出:** 矩陣中第 k 小的整數
- **主要規則或限制**
  1. 可以有重複數字
- **核心任務:** 利用行與列皆已排序的特性，快速定位目標數值

## 3. 思考邏輯與解題策略

### 初始想法

- 把二維陣列所有的數字放入一維陣列裡，用 sort() 排好後直接取第 k-1 個索引
- 時間複雜度高且沒有用到題目敘述中行列皆已排序好的特性

### 最終策略

- 矩陣的最小值一定在左上角 matrix[0][0]，最大值一定在右下角 matrix[n-1][n-1]，對這個區間做二分搜尋，每次猜一個中間值 mid，然後去矩陣裡算有幾個數字小於等於 mid
- 如果當前數字 <= mid，因為這整列的上面所有數字都比當前數字小，所以必定也 <= mid，直接把整根柱子的數量 (row + 1) 加進總數，然後往右走一步（col++）；如果當前數字 > mid，代表太大了，往上走一步（row--）來找更小的數字

## 4. 虛擬碼

```text
START
1. 設定 left = 矩陣左上角 (最小值)
2. 設定 right = 矩陣右下角 (最大值)
3. 當 left < right 時，執行迴圈：
   a. 計算中間值 mid = left + (right - left) / 2
   b. 初始化計數器 count = 0
   c. 從左下角出發，設定 row = n - 1, col = 0
   d. 當不越界時 (row >= 0 且 col < n)：
      i. 若 matrix[row][col] <= mid：
         - 該行上方所有元素皆 <= mid，count 增加 (row + 1)
         - 往右移動 (col++)
      ii. 否則 (大於 mid)：
         - 往上移動 (row--)
   e. 判斷 count 與 k：
      - 若 count < k，代表 mid 太小，更新 left = mid + 1
      - 若 count >= k，代表答案可能是 mid 或更小，更新 right = mid
4. 迴圈結束，回傳 left (即為第 k 小的元素)
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int left = matrix[0][0];       
        int right = matrix[n - 1][n - 1]; 
        
        while(left < right){
            int mid = left + (right - left) / 2;
            int count = 0;
            
            int row = n - 1; 
            int col = 0;
            while(row >= 0 && col < n){
                if(matrix[row][col] <= mid){
                    count += (row + 1);
                    col++;
                }
                else row--;
            }
            
            if(count < k) left = mid + 1;
            else right = mid;
        } 
        return left;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 將問題轉化為對數值範圍進行猜測與驗證 |
| 邊際情況 |  | 穩定高效，不受 k 大小影響 |
| 輸出處理 |  | 正確輸出矩陣中第 k 小的數字 |

### 反思
- 學到了二分搜尋不一定只能用在「連續索引」上，只要具備單調性（數值越大，小於等於該數值的個數就越多），就可以直接對「值域」進行二分搜