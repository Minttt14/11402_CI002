# [LeetCode] [20] - [Valid Parentheses]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 20
- **題目標題:** Valid Parentheses
- **題目連結:** [Link to problem](https://leetcode.com/problems/valid-parentheses/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode20-correct.cpp](./src/s1131408-LeetCode20-correct.cpp)

## 2. 題目說明
給一個只包含字元 '(', ')', '{', '}', '[', ']' 的字串 s，判斷該輸入字串是否合法
- **輸入:** 一個僅由上述六種括號組成的字串 s
- **預期輸出:** 布林值 (true / false)
- **主要規則或限制**
  1. 左括號必須由相同類型的右括號閉合
  2. 左括號必須以正確的順序閉合（即「後開的要先關」）
  3. 每個右括號都有一個對應的相同類型的左括號
- **核心任務:** 驗證符號的對稱性，確保符合「後進先出 (LIFO)」的順序

## 3. 思考邏輯與解題策略

### 初始想法

- 宣告三個整數變數，分別計算小、中、大括號出現的次數，遇到左括號 +1，右括號 -1，最後檢查是否都歸零
- 計數器只能保證「數量對稱」，無法處理「順序錯誤」的問題

### 最終策略

- 堆疊配對法，具有先進後出的特性，只要遇到左括號就推入，遇到右括號時檢查 stack 是否為空，是的話回傳 false ，不是則檢查當前的右括號有無對應的左括號，沒有就回傳 false ，反之 pop 當前的頂部的左括號
- 合法的括號字串長度必定是偶數，如果是奇數，直接回傳 false

## 4. 虛擬碼

```text
START
1. 邊界防禦：若字串 s 的長度不能被 2 整除，直接回傳 false
2. 宣告一個字元堆疊 st
3. 遍歷字串 s 中的每一個字元 c：
   a. 若 c 是左括號 ('(', '[', '{')：
      - 將 c 推入堆疊 st (st.push(c))
   b. 否則 (c 必定是右括號)：
      - 若堆疊 st 為空，代表沒有可配對的左括號，回傳 false
      - 讀取堆疊頂端字元 top = st.top()
      - 進行括號配對檢查：
        * 若 c 為 ')' 且 top 不為 '('，回傳 false
        * 若 c 為 ']' 且 top 不為 '['，回傳 false
        * 若 c 為 '}' 且 top 不為 '{'，回傳 false
      - 配對成功，將 top 從堆疊移除 (st.pop())
4. 迴圈結束後，回傳 st 是否為空 (st.empty())
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool isValid(string s){
        if(s.length() % 2 != 0) return false;
        
        stack<char> st;
        
        for(char c : s){
            if(c == '(' || c == '[' || c == '{') st.push(c);
            else{
                if(st.empty()) return false;
                
                char top = st.top();
                
                if(c == ')' && top != '(') return false; 
                else if(c == ']' && top != '[') return false; 
                else if(c == '}' && top != '{') return false; 

                st.pop();
            }
        }
        return st.empty();
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | LIFO特性，由內而外消除 |
| 邊際情況 |  | 堆疊能精準捕捉順序錯誤 |
| 輸出處理 |  | 正確輸出布林值 |

### 反思
- 只要遇到「先進後出」的題型，最先要想到的就是恰好符合此特性的 Stack 
- 在呼叫 st.top() 之前，先檢查 st.empty() 避開了存取空指標的嚴重錯誤
- 再遇到類似問題時如果需要判斷的種類更多，依此題寫法 if-else 會變得非常冗長，可以引入雜湊表做預處理，讓程式碼變得精簡