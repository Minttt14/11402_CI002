# [LeetCode] [35] - [Search Insert Position]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 35
- **題目標題:** Search Insert Position
- **題目連結:** [Link to problem](https://leetcode.com/problems/search-insert-position/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode35-correct.cpp](./src/s1131408-LeetCode35-correct.cpp)

## 2. 題目說明
給一個按升冪排序且無重複元素的整數陣列 nums，以及一個目標值 target，在陣列中尋找該目標值，找到就回傳其索引值；若找不到，回傳它應該被按順序插入的索引位置
- **輸入:** 已排序的無重複整數陣列 nums，以及一個整數 target
- **預期輸出:** 目標值的索引，或是目標值應被插入的位置索引
- **主要規則或限制**
  1. 陣列元素與目標值皆為整數
- **核心任務:** 找出陣列中第一個大於或等於 target 的元素位置

## 3. 思考邏輯與解題策略

### 初始想法

- 用一個 for 迴圈遍歷陣列，遇到第一個大於或等於 target 的數字，當下的索引就是答案，如果整個迴圈跑完都沒遇到，代表 target 比所有數字都大，應插入在陣列最後面
- 不符合題目要求的 $O(\log n)$ 限制

### 最終策略

- 使用 lower_bound ，它是會利用底層的二分搜尋，回傳陣列中第一個「大於或等於」target 的迭代器
- 若找得到目標值，利用 distance 計算迭代器與陣列起點的距離，就是索引值

## 4. 虛擬碼

```text
START
1. 呼叫底層二分搜尋函式 lower_bound，在 nums 陣列中尋找第一個「大於或等於 target」的元素，取得其記憶體位置 (迭代器)
2. 呼叫距離計算函式 distance，計算 nums 陣列「起點」與「剛才找到的位置」之間的距離
3. 該距離即為目標值存在或應被插入的「索引值 (Index)」，直接將其回傳
END
```

### 正確程式碼

```cpp
class Solution{
public:
    int searchInsert(vector<int>& nums, int target){
        return distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 直接呼叫底層 C++ 演算法 |
| 邊際情況 |  | nums.end() 處理越界插入 |
| 輸出處理 |  | 正確回傳索引值 |

### 反思
- lower_bound 和 upper_bound 在處理排序陣列時非常實用
- 可以嘗試手刻二分搜，透過實際撰寫能夠更清楚其中的邏輯