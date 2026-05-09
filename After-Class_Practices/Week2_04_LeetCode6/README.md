# [LeetCode] [6] - [Zigzag Conversion]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 6
- **題目標題:** Zigzag Conversion
- **題目連結:** [Link to problem](https://leetcode.com/problems/zigzag-conversion/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode6-correct.cpp](./src/s1131408-LeetCode6-correct.cpp)

## 2. 題目說明
將一個字串按照指定的行數進行之字型排列，然後由左至右、由上而下重新組合成新的字串
- **輸入:** 字串 s，整數 numRows
- **預期輸出:** 轉換後的字串
- **主要規則或限制**
  1. 字串會先「向下」填滿每一行，到底後轉向「右上斜向」填寫，直到回到第一行再重複
  2. 最終結果是將每一行的字元依序連接起來
- **核心任務:** 模擬字元在各行之間的彈回路徑

## 3. 思考邏輯與解題策略

### 初始想法

- 想要建立一個真正的二維陣列來模擬
- 浪費大量的空間，因為大部分格點是空的，且計算每個字元的精確 $(i, j)$ 座標非常複雜

### 最終策略

- 使用 vector<string> rows(numRows)，其中每一項代表該列目前累積的字元
- 當 currRow == 0 時，強制方向向下 (step = 1)；currRow == numRows - 1 時，強制方向向上 (step = -1)

## 4. 虛擬碼

```text
START
1. 如果 numRows 為 1 或 大於等於字串長度：
   - 直接回傳 s (不需轉換)
2. 初始化 rows 陣列 (長度為 numRows 的空字串)
3. 初始化 currRow = 0, step = 1
4. 遍歷字串中的每個字元 c：
   a. 將 c 加入 rows[currRow]
   b. 如果 currRow 到了第一列 (0)：
      - step = 1 (向下)
   c. 否則如果 currRow 到了最後一列 (numRows - 1)：
      - step = -1 (向上)
   d. currRow = currRow + step
5. 將 rows 陣列中所有的字串拼接在一起，存入 result
6. 回傳 result
END
```

### 正確程式碼

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || numRows >= s.length()) {
            return s;
        }

        vector<string> rows(numRows);
        int currRow = 0;
        int step = 1; 

        for (char c : s) {
            rows[currRow] += c;
            
            if (currRow == 0) step = 1;      
            else if (currRow == numRows - 1) step = -1; 
            
            currRow += step;
        }

        string result = "";
        for (string row : rows) {
            result += row;
        }
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 透過 step 模擬上下彈跳的過程 |
| 邊際情況 |  | 正確處理 numRows=1 的例外 |
| 輸出處理 |  | 拼接 vector<string>，邏輯乾淨 |

### 反思

- 雖然題目描述的是二維結構，但因為我們最終只需要按列輸出，所以只要維護好「列索引」這一維度即可
- 利用 step = -step 或條件式的 step = 1 / -1 來切換方向，是處理來回震盪邏輯的好方法


