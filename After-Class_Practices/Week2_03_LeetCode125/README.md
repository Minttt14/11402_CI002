# [LeetCode] [125] - [Valid Palindrome]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 125
- **題目標題:** Valid Palindrome
- **題目連結:** [Link to problem](https://leetcode.com/problems/valid-palindrome/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode125-correct.cpp](./src/s1131408-LeetCode125-correct.cpp)

## 2. 題目說明
判斷一個字串正著讀和反著讀是否相同，只考慮數字與字母，且大小寫視為相同
- **輸入:** 一個包含各種字元的字串 s
- **預期輸出:** 布林值（true 或 false）
- **主要規則或限制**
  1. 忽略所有非字母或數字的字元
  2. 字母大小寫視為相同
- **核心任務:** 檢查字串是否無論從前或後讀取都完全一致

## 3. 思考邏輯與解題策略

### 初始想法

- 分別從字串的第一個與最後一個位置往中間比對
- 一開始沒想到怎麼忽略非字母或數字的字元

### 最終策略

- 利用 isalnum() 來篩出數字與字母，若非則跳過
- 將字母全部轉為小寫，方便後續判斷

## 4. 虛擬碼

```text
START
1. 設定左指針 begin = 0, 右指針 end = 長度 - 1
2. 當 begin < end 時執行循環：
   a. 若 s[begin] 不是字母或數字，begin 往右移
   b. 否則若 s[end] 不是字母或數字，end 往左移
   c. 否則 (兩者都是有效字元)：
      - 將兩者轉為小寫並比較
      - 若不相等，回傳 false
      - 若相等，begin 往右移，end 往左移
3. 若循環結束，代表皆對稱，回傳 true
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int begin = 0;
        int end = s.length() - 1;

        while (begin < end) {
            if (!isalnum(s[begin])) {
                begin++;
            } 
            else if (!isalnum(s[end])) {
                end--;
            } 
            else {
                if (tolower(s[begin]) != tolower(s[end])) {
                    return false;
                }
                begin++;
                end--;
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
| 邏輯 |  | 兩指針在移動過程中同步過濾與比對 |
| 邊際情況 |  | 確保 begin < end 判斷正確，避免越界 |
| 輸出處理 |  | 只要一處不對稱立即回傳 |

### 反思

- isalnum() 和 tolower() 、 toupper() 在處理字串題目中非常實用
- 雙指針的結構在處理「對稱性」或「區間搜尋」問題時十分方便


