# [LeetCode] [1122] - [Relative Sort Array]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1122
- **題目標題:** Relative Sort Array
- **題目連結:** [Link to problem](https://leetcode.com/problems/relative-sort-array/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1122-correct.cpp](./src/s1131408-LeetCode1122-correct.cpp)

## 2. 題目說明
給兩個陣列 arr1 和 arr2，根據 arr2 的元素順序來對 arr1 進行排序
- **輸入:** arr1 與 arr2
- **預期輸出:** 依照 arr2 順序重新排列的 arr1
- **主要規則或限制**
  1. arr2 中沒有出現的數字，必須被放置在 arr1 的最尾端，這些剩下的數字必須按照升冪排列
  2. 陣列長度皆不超過 1000
  3. 陣列內數字的大小範圍介於 0 到 1000 之間
- **核心任務:** 自訂排序決定數字的先後順序

## 3. 思考邏輯與解題策略

### 初始想法

- unordered_map<int, int> 記錄 arr2 中每個數字對應的索引值，自訂排序時，每次比較兩個數字去 Map 裡面查它們的 Index，Index 小的排前面，查不到的話就排到最後面
- unordered_map 的底層機制較為複雜，常數時間的消耗比較大

### 最終策略

- 將 rank 陣列的預設值全部填上 1001，代表一個比 arr2 任何合法索引都還要大的權重，遍歷 arr2，把出現的數字當作索引，對應的 rank 值設為它在 arr2 的位置
- 如果兩個數字的 rank 不同，代表其中至少有一個在 arr2 中，回傳 rank[a] < rank[b]；如果兩個數字的 rank 相同，代表它們都不在 arr2 中，需要升冪排列，回傳 a < b

## 4. 虛擬碼

```text
START
1. 宣告一個大小為 1001 的陣列 rank，並將所有元素初始化為 1001
2. 遍歷 arr2 (取得索引 i 與數值 val)：
   - 將 rank[val] 的值設為 i (建立相對順序表)
3. 使用內建 sort 函數對 arr1 進行排序，自訂比較條件 (a, b)：
   a. 如果 rank[a] 不等於 rank[b]：
      - 回傳 rank[a] < rank[b]
   b. 否則 (兩者 rank 相同，皆不在 arr2 或為相同數字)：
      - 回傳 a < b
4. 回傳排序完畢的 arr1
END
```

### 正確程式碼

```cpp
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
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用資料範圍限制，直接開 1001 格陣列 |
| 邊際情況 |  | 預設為 1001，配合 a < b 處理尾端升冪要求 |
| 輸出處理 |  | 輸出正確順序的 arr1 |

### 反思

- 學到了看測資範圍的重要性，當數字範圍較小時，開陣列取代 Hash Map 能提升查詢速度
- 也能用計數排序來解，完全不使用 sort() 函數，把 arr1 出現的數字頻率存在 count[1001] 中，接著遍歷 arr2 把對應數量的數字塞回答案裡，最後再把 count 剩下的數字依序塞進去，可以降低時間複雜度