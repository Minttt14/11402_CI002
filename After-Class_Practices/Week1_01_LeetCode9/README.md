# [LeetCode] [9] - [Palindrome Number]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 9
- **題目標題:** Palindrome Number
- **題目連結:** [Link to problem](https://leetcode.com/problems/palindrome-number/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode9-correct.cpp](./src/s1131408-LeetCode9-correct.cpp)

## 2. 題目說明
判斷整數 $x$ 是否為迴文數，是的話回傳 true ，否則回傳false
- **輸入:** 一個整數 $x$
- **預期輸出:** 布林值（true 或 false）
- **主要規則或限制**
  1. 負數絕對不是迴文
- **核心任務:** 檢查數字是否無論從前或後讀取都完全一致

## 3. 思考邏輯與解題策略

### 初始想法

- 想要用數學方式（取餘數 %10）把數字反轉過來，再看跟原本的數字是否相等
- 反轉整數可能會遇到溢位問題

### 最終策略

- 將整數透過 to_string() 轉換成字串，再進行對稱檢查
- 避免了溢位問題也不需要翻轉就能檢查對稱性
- 負數絕對不會是迴文數

## 4. 虛擬碼

```text
START
1. 將整數 x 轉換為字串 s
2. 設定迴圈從 i = 0 執行到長度的一半 (s.length() / 2)：
   a. 比較左側字元 s[i] 與對應的右側字元 s[長度 - 1 - i]
   b. 如果兩者不相等：
      立即回傳 false
3. 如果完整遍歷後都沒有不相等的情況：
   回傳 true
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        string s;
        s = to_string(x);
        for(int i=0; i<s.length()/2; ++i){
            if(s[i] != s[s.length() - 1 - i]){
             return false;
            }
        }
        return true;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 將數字視為字元序列進行首尾比對 |
| 邊際情況 |  | 不需擔心溢位，負數也很好處理 |
| 輸出處理 |  | 只要有不對稱就立刻回傳false |

### 反思

- 一個問題可能會有多種解法，例如此題可直接依照題目所給的整數去解，也可以轉成字串後再處理，轉成字串時能夠方便處理負數與溢位問題，但較耗費空間，因此可依照不同需求找出最適當的解法
- 下次可嘗試只反轉一半的數字，不僅不會溢位也不需要額外的字串空間，空間複雜度從 $O(L)$ 降到 $O(1)$


