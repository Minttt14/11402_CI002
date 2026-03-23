# [LeetCode] [8] - [String to Integer (atoi)]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 8
- **題目標題:** String to Integer (atoi)
- **題目連結:** [Link to problem](https://leetcode.com/problems/string-to-integer-atoi/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode8-correct.cpp](./src/s1131408-LeetCode8-correct.cpp)

## 2. 題目說明
實作一個 atoi 的函式，將字串轉換為 32 位元有號整數
- **輸入:** 字串 s
- **預期輸出:** 將字串轉成整數
- **主要規則或限制**
  1. 忽略前導空格
  2. 檢查下一個字元是否為 '+' 或 '-'（若無則預設為正）
  3. 讀取後續的數字字元，直到遇到非數字字元或字串結束
  4. 若沒有讀取到任何數字，則結果為 0
- **核心任務:** 嚴謹地按照順序處理「空格 -> 正負號 -> 數字轉換 -> 溢位檢查」

## 3. 思考邏輯與解題策略

### 初始想法

- 依照題目要求按照順序分別判斷
- 一開始不知道如何處理溢位

### 最終策略

- 先用 while 跳過所有空白，第二步判斷正負號，最後判斷是否為數字並進行溢位判斷等處理
- 在每次數字累加的過程中（result = result * 10 + digit），立刻檢查是否超過 INT_MAX 或 INT_MIN

## 4. 虛擬碼

```text
START
1. 初始化 指標 i = 0, 結果 result = 0 (使用 long), 符號 sign = 1
2. 忽略開頭空格：當 s[i] 為空格時，i 遞增
3. 處理正負號：
   - 若 s[i] 為 '-'，則 sign = -1，i 遞增
   - 否則若 s[i] 為 '+'，則 sign = 1，i 遞增
4. 轉換數字：當 i 未越界且 s[i] 為數字時：
   a. 更新 result = result * 10 + (s[i] - '0')
   b. 檢查溢位：
      - 若 (sign * result) >= INT_MAX，回傳 INT_MAX
      - 若 (sign * result) <= INT_MIN，回傳 INT_MIN
   c. i 遞增
5. 回傳 (int)(result * sign)
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int n = s.length();
        long result = 0; 
        int sign = 1;

        while (i < n && s[i] == ' ') {
            i++;
        }

        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if(sign = (s[i] == '+')) sign = 1;
            else sign = -1;
            i++;
        }

        while (i < n && isdigit(s[i])) {
            result = result * 10 + (s[i] - '0');

            if (sign == 1 && result > INT_MAX) return INT_MAX;
            if (sign == -1 && -result < INT_MIN) return INT_MIN;
            i++;
        }

        return (int)(result * sign);
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 空格、符號、數字分別處理 |
| 邊際情況 |  | 只在開頭判斷一次符號，後續遇到 + 或 - 直接終止轉換 |
| 輸出處理 |  | 最終輸出時強制執行 (int)(result * sign)，確保回傳型別正確且正負號一致 |

### 反思

- 一開始覺得要判斷的條件很多，順序容易錯亂
- 處理大數轉換時，使用比目標型態大一階的變數（如用 long 存 int）來做中轉判斷是非常穩健的技巧


