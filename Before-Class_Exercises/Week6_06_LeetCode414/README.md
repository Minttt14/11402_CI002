# [LeetCode] [414] - [Largest Number]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 414
- **題目標題:** Largest Number
- **題目連結:** [Link to problem](https://leetcode.com/problems/third-maximum-number/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode414-correct.cpp](./src/s1131408-LeetCode414-correct.cpp)

## 2. 題目說明
給一個整數陣列，找出陣列中第三大的相異整數
- **輸入:** 整數陣列 nums
- **預期輸出:** 陣列中第三大的相異整數，如果不存在第三大的數，則回傳陣列中最大的整數
- **主要規則或限制**
  1. 必須是相異的數字
  2. 陣列元素的值可能包含 32 位元有號整數的極小值
- **核心任務:** 找出前三大的不重複數值

## 3. 思考邏輯與解題策略

### 初始想法

- 先將陣列降冪排序，過濾掉重複的數字，取出索引值為 2 的元素，若過濾後長度小於 3，則取索引值為 0 的元素
- 時間複雜度較高

### 最終策略

- 宣告三個變數來模擬前三大的數字改變的過程，如果數字已經在三個變數中，直接跳過確保相異
- 因為陣列的數字可能剛好是整數的最小值，如果用 INT_MIN 來初始化這三個變數，會無法分辨「第三大的數字剛好是 INT_MIN」還是「根本沒有第三大的數字」，因此，將變數型態宣告為 long long 並以 LONG_MIN 初始化

## 4. 虛擬碼

```text
START
1. 初始化三個長整數變數 max1, max2, max3 為 LONG_MIN
2. 遍歷陣列 nums 中的每一個數字 num：
   a. 如果 num 等於 max1, max2 或 max3，直接繼續下一個迴圈 (過濾重複值)
   b. 如果 num > max1：
      - max3 = max2
      - max2 = max1
      - max1 = num
   c. 否則如果 num > max2：
      - max3 = max2
      - max2 = num
   d. 否則如果 num > max3：
      - max3 = num
3. 檢查 max3 是否還是初始值 LONG_MIN：
   a. 如果是，代表相異數字不到三個，回傳 max1
   b. 否則，回傳 max3 (轉型回 int)
END
```

### 正確程式碼

```cpp
class Solution{
public:
    int thirdMax(vector<int>& nums){
        long long max1 = LONG_MIN; // 第一大
        long long max2 = LONG_MIN; // 第二大
        long long max3 = LONG_MIN; // 第三大
        
        for(int num : nums){
            if (num == max1 || num == max2 || num == max3){
                continue;
            }

            if(num > max1){
                max3 = max2; 
                max2 = max1; 
                max1 = num; 
            }
            else if(num > max2){
                max3 = max2; 
                max2 = num;  
            }
            else if(num > max3){
                max3 = num; 
            }
        }
        return max3 == LONG_MIN ? max1 : max3;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 動態維護，僅追蹤前三大的數值 |
| 邊際情況 |  | 透過判斷 max3 == LONG_MIN 解決不足三個數字的情況 |
| 輸出處理 |  | 正確輸出第三大或陣列中最大的元素 |

### 反思

- 在尋找最大值或最小值時，習慣性會用 INT_MIN 或 INT_MAX 當底，但如果測資範圍包含型態的極限值時，我們必須使用更大範圍的型態（如 long long）來作為安全的初始狀態標記
- 如果是求「第 K 大」，變數宣告會變得太長，這時就必須轉換策略，改用優先佇列 (Min-Heap / Priority Queue) 來維持大小為 K 的視窗了
