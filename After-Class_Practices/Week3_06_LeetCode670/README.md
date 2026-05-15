# [LeetCode] [670] - [Maximum Swap]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 670
- **題目標題:** Maximum Swap
- **題目連結:** [Link to problem](https://leetcode.com/problems/maximum-swap/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode670-correct.cpp](./src/s1131408-LeetCode670-correct.cpp)

## 2. 題目說明
給定一個非負整數 num，最多可以交換這個數字中的兩個數位置一次，來獲得可能的最大值
- **輸入:** 一個整數 num
- **預期輸出:** 可以得到的最大整數
- **主要規則或限制**
  1. 最多只能交換一次，如果原本就是最大值，也可以選擇不交換
  2. num 的範圍是 0 到 10^8
- **核心任務:** 找出哪兩個位置的數字互換，能讓整體的數值增幅最大

## 3. 思考邏輯與解題策略

### 初始想法

- 從最高位數開始檢查，看低位數有沒有大於目前的數字可以交換
- 當出現重複數字可以交換時邏輯判斷較麻煩

### 最終策略

- 排列組合所有可能性，再取最大值
- 數字範圍夠小的情況下，用窮舉法邏輯直觀且能確保輸出百分百正確

## 4. 虛擬碼

```text
START
1. 將整數 num 轉成字串 s
2. 初始化 maxNum = num (代表如果不交換的基礎值)
3. 遍歷字串的第一個索引 i (從 0 到 s 長度 - 1)：
   a. 遍歷字串的第二個索引 j (從 i + 1 到 s 長度 - 1)：
      i.   交換 s[i] 和 s[j]
      ii.  將 s 轉回整數，如果大於 maxNum，則更新 maxNum
      iii. 再次交換 s[i] 和 s[j]，將字串還原
4. 回傳 maxNum
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        int maxNum = num;
        
        for (int i = 0; i < s.length(); i++) {
            for (int j = i + 1; j < s.length(); j++) {
                swap(s[i], s[j]);
                maxNum = max(maxNum, stoi(s));
                swap(s[i], s[j]); 
            }
        }  
        return maxNum;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 兩兩配對，全部換換看，挑最大的 |
| 邊際情況 |  | 窮舉了所有可能，絕對不會漏算 |
| 輸出處理 |  | 正確輸出可能的最大值 |

### 反思

- 這題展示了先看限制條件的重要性，很多時候我們一看到題目就想著要寫出 O(N) 的最佳解，卻忽略了如果 N 很小，暴力解才是最穩、最快開發出來的策略
- 遇到類似問題時，如果數字很小，採用窮舉，如果數字非常大，改用 O(N) 的貪婪法