# [LeetCode] [48] - [Rotate Image]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 48
- **題目標題:** Rotate Image
- **題目連結:** [Link to problem](https://leetcode.com/problems/rotate-image/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode48-correct.cpp](./src/s1131408-LeetCode48-correct.cpp)

## 2. 題目說明
給定一個 $n \times n$ 的二維矩陣，將其順時針旋轉 90 度
- **輸入:** 一個 $n \times n$ 的二維向量 matrix
- **預期輸出:** 旋轉後輸出
- **主要規則或限制**
  1. 不能使用額外的二維矩陣來儲存旋轉後的結果
- **核心任務:** 找出元素旋轉後的座標映射規律，並在不遺失數據的情況下完成交換

## 3. 思考邏輯與解題策略

### 初始想法

- 建立一個新的矩陣 new_matrix，根據規則 new_matrix[j][n-1-i] = matrix[i][j] 填入數值，最後再複製回去
- 會使用 $O(n^2)$ 的額外空間，違反了題目 "In-place" 的要求

### 最終策略

- 一個位置一個位置進行旋轉
-  先把「左上」存進 temp，然後按照「左下 $\to$ 左上」、「右下 $\to$ 左下」、「右上 $\to$ 右下」、「左上($temp$) $\to$ 右上」的順序進行覆蓋

## 4. 虛擬碼

```text
START
1. 取得矩陣維度 n
2. 遍歷每一層 i (從 0 到 n/2 - 1):
   a. 遍歷該層的起始位置 j (從 i 到 n - i - 2):
      i.   暫存 左上角: temp = matrix[i][j]
      ii.  左下 移至 左上: matrix[i][j] = matrix[n-1-j][i]
      iii. 右下 移至 左下: matrix[n-1-j][i] = matrix[n-1-i][n-1-j]
      iv.  右上 移至 右下: matrix[n-1-i][n-1-j] = matrix[j][n-1-i]
      v.   暫存(左上) 移至 右上: matrix[j][n-1-i] = temp
END
```

### 正確程式碼

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - i - 1; j++) {
                int temp = matrix[i][j];
                
                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = temp;
            }
        }
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 直接在原矩陣上對稱地移動四個頂點 |
| 邊際情況 |  | j < n - i - 1 確保每一組四個點只被處理一次，不重疊、不遺漏 |
| 輸出處理 |  | 正確輸出旋轉後的矩陣 |

### 反思

- 這題是練習了矩陣座標映射，重點在於找出四個點之間的關係
- 下次可以嘗試先進行矩陣轉置，再進行每一行的反轉
