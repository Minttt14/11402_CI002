# [LeetCode] [704] - [Binary Search]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 704
- **題目標題:** Binary Search
- **題目連結:** [Link to problem](https://leetcode.com/problems/binary-search/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode704-correct.cpp](./src/s1131408-LeetCode704-correct.cpp)

## 2. 題目說明
給一個整數陣列 nums，該陣列已按升冪排序，並給定一個目標值，寫一個函數在 nums 中尋找目標值
- **輸入:** 一個已排序的整數陣列 nums，以及一個整數 target
- **預期輸出:** 如果目標值存在陣列中，回傳其索引值；如果不存在，則回傳 -1
- **主要規則或限制**
  1. 陣列中的所有數字都是相異的
- **核心任務:** 用陣列已排序的特性，透過搜尋區間來極速定位目標值

## 3. 思考邏輯與解題策略

### 初始想法

- 寫一個 for 迴圈從頭掃描到尾
- 時間複雜度較高且沒有利用到題目給的已排序條件

### 最終策略

- 使用 <algorithm> 函式庫中的二分搜尋工具 lower_bound ，他能夠在已排序的區間中，找出「第一個大於或等於 target」的元素
- 若找得到目標值，利用 distance 計算迭代器與陣列起點的距離，就是索引值；找不到就回傳 -1

## 4. 虛擬碼

```text
START
1. 使用 lower_bound 在 nums 陣列中尋找第一個 >= target 的位置，存入迭代器 it
2. 如果 it 沒有越界 (不等於 nums 結尾) 且 it 指向的數值等於 target：
   a. 計算並回傳 nums 起點到 it 的距離 (即為目標索引值)
3. 否則 (代表找不到，或找到大於 target 的數字)：
   a. 回傳 -1
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target){
        auto it = lower_bound(nums.begin(), nums.end(), target);
        
        if(it != nums.end() && *it == target){
            return distance(nums.begin(), it);
        }
        return -1;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用底層寫好的二分搜尋工具 |
| 邊際情況 |  | STL 已在底層完美處理所有極端情況 |
| 輸出處理 |  | 正確回傳索引值或例外狀況 |

### 反思
- lower_bound 和 upper_bound 在處理排序陣列時非常實用
- 可以嘗試手刻二分搜，透過實際撰寫能夠更清楚其中的邏輯