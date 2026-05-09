# [LeetCode] [231] - [Power of Two]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 231
- **題目標題:** Power of Two
- **題目連結:** [Link to problem](https://leetcode.com/problems/palindrome-number/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode231-correct.cpp](./src/s1131408-LeetCode231-correct.cpp)

## 2. 題目說明
判斷給定的整數 $n$ 是否為 2 的冪次方
- **輸入:** 一個整數 n
- **預期輸出:** 布林值 (true / false)
- **主要規則或限制**
  1. $n$ 可能為負數、零或極大的正整數
  2. 負數與零絕對不是 2 的冪次方
- **核心任務:** 檢查 $n$ 是否能被 2 連續整除直到剩下 1

## 3. 思考邏輯與解題策略

### 初始想法

- 想要使用 pow(2, x) 配合迴圈從 $x=0$ 開始跑，直到結果大於或等於 $n$
- 效率較低，且需要處理浮點數精度或整數溢位問題

### 最終策略

- 除法模擬法，只要 $n$ 還能被 2 整除，就將 $n$ 除以 2
- 停止除法後，如果 $n$ 變成了 1，說明它是 2 的冪次方

## 4. 虛擬碼

```text
START
1. 如果 n <= 0，回傳 false
2. 當 n 可以被 2 整除時：
   - n = n / 2
3. 如果最後 n 等於 1，回傳 true
4. 否則回傳 false
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) {
            return false;
        }
        
        while (n % 2 == 0) {
            n /= 2;
        }
        
        return n == 1;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 從 $n$ 開始除回 1 |
| 邊際情況 |  | 正確判斷負數與零絕對不是 2 的冪次方 |
| 輸出處理 |  | 正確輸出布林值 |

### 反思

- 這題最容易漏掉的是零與負數的判斷，若直接進入 while 迴圈，這會導致錯誤的結果或死迴圈
- 下次若遇到類似問題時可以試著使用 n & (n - 1) ，這個技巧在處理二進位問題（如計算位元 1 的個數）時，能直接將迴圈優化掉


