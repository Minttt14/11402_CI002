# [LeetCode] [169] - [Majority Element]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 169
- **題目標題:** Majority Element
- **題目連結:** [Link to problem](https://leetcode.com/problems/majority-element/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode169-correct.cpp](./src/s1131408-LeetCode169-correct.cpp)

## 2. 題目說明
在一個大小為 $n$ 的陣列中，尋找其中的多數元素
- **輸入:** 一個整數陣列 nums
- **預期輸出:** 該陣列中的多數元素
- **主要規則或限制**
  1. 多數元素是指在陣列中出現次數 大於 $\lfloor n / 2 \rfloor$ 的元素
  2. 題目假設陣列是非空的，且多數元素一定存在於陣列中
- **核心任務:** 找出出現頻率超過一半的那個數字

## 3. 思考邏輯與解題策略

### 初始想法

- 使用迴圈來計算每個數出現的次數
- 效率很低

### 最終策略

- 排序取再取中間值
- 如果一個數字出現次數超過一半，那麼當陣列排序後，不論它偏左還是偏右，一定會佔據陣列的正中間位置

## 4. 虛擬碼

```text
START
1. 使用 sort() 對輸入陣列 nums 進行排序
2. 計算中點索引 mid = nums.size() / 2
3. 回傳 nums[mid]
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 排序後，多數元素必定會橫跨陣列的中點 |
| 邊際情況 |  | 排序後取 n/2 的位置，對於 $n=1$ 或 $n=2$ 依然精準 |
| 輸出處理 |  | 直接回傳位於中位數索引的數值 |

### 反思

- 有些看似需要計數的問題，其實可以轉換成位置問題
- 可以使用摩爾投票演算法，這是一個專門為了解決多數元素問題而設計的 $O(n)$ 時間、$O(1)$ 空間的演算法，其原理是不同元素兩兩抵消，最後剩下的必是多數

