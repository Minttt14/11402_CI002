# [LeetCode] [394] - [Decode String]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 394
- **題目標題:** Decode String
- **題目連結:** [Link to problem](https://leetcode.com/problems/decode-string/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode394-correct.cpp](./src/s1131408-LeetCode394-correct.cpp)

## 2. 題目說明
給一個經過編碼的字串，回傳解碼後的原始字串，編碼規則為 k[encoded_string]，表示括號內部的 encoded_string 必須被重複 k 次
- **輸入:** 包含英文字母、數字與中括號 [] 的字串 s
- **預期輸出:** 展開後的純英文字母字串
- **主要規則或限制**
  1. k 必為正整數
  2. 輸入字串永遠是合法的，不會有未閉合的括號
  3. 括號內部可以繼續包疊括號
- **核心任務:** 正確維護每一層括號的「重複次數」與「前面已解析的字串內容」，並由內而外將字串組合起來

## 3. 思考邏輯與解題策略

### 初始想法

- 遇到 [ 就呼叫一個遞迴函數去處理括號內的字串，遇到 ] 就回傳當前展開的字串給上一層
- 遞迴法需要精準維護一個全域的字串索引指標，確保遞迴回來後能從正確的位置繼續讀取，參數傳遞上容易寫得比較混亂

### 最終策略

- 使用兩個 stack 來儲存，一個紀錄倍數，一個紀錄外層字串
- 遇到數字時持續累加計算 currentNum * 10 + digit ，遇到字母時，直接接在 currentStr 後面，遇到 [ 時，將算好的 currentNum 和 currentStr 推入堆疊中，然後將兩者清空，遇到 ] 時，從堆疊中彈出上一層存好的字串 prevStr 與這層的重複次數 repeat，將目前的 currentStr 複製 repeat 次，接在 prevStr 後面，成為全新的 currentStr

## 4. 虛擬碼

```text
START
1. 初始化兩個堆疊：numStack (存整數), strStack (存字串)
2. 初始化當前字串 currentStr = ""，當前數字 currentNum = 0
3. 遍歷字串 s 中的每一個字元 c：
   a. 如果 c 是數字：
      - currentNum = currentNum * 10 + (c 轉換為整數)  // 處理多位數
   b. 如果 c 是英文字母：
      - currentStr 加上 c
   c. 如果 c 是 '[' (進入新層級)：
      - 將 currentNum 存入 numStack
      - 將 currentStr 存入 strStack
      - 重置 currentNum = 0, currentStr = ""
   d. 如果 c 是 ']' (離開當前層級)：
      - 從 numStack 取出重複次數 repeat
      - 從 strStack 取出上一層的字串 prevStr
      - 將 currentStr 重複 repeat 次，暫存為 temp
      - 更新 currentStr = prevStr + temp
4. 迴圈結束後，回傳 currentStr
END
```

### 正確程式碼

```cpp
class Solution {
public:
    string decodeString(string s){
        stack<int> numStack;   
        stack<string> strStack;  
        
        string currentStr = "";  
        int currentNum = 0;     
        
        for(char c : s){
            if(isdigit(c)) currentNum = currentNum * 10 + (c - '0');
            else if(isalpha(c)) currentStr += c;
            else if(c == '['){
                numStack.push(currentNum);
                strStack.push(currentStr);

                currentNum = 0;
                currentStr = "";
            } 
            else if(c == ']'){
                int repeat = numStack.top();
                numStack.pop();
                
                string prevStr = strStack.top();
                strStack.pop();
                
                string temp = "";
                for(int i=0; i<repeat; ++i){
                    temp += currentStr;
                }
                
                currentStr = prevStr + temp;
            }
        }   
        return currentStr;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 顯式建立堆疊，自己掌控狀態存取 |
| 邊際情況 |  | 利用 currentNum * 10 + digit 解決多位數問題 |
| 輸出處理 |  | 正確輸出展開後情形 |

### 反思
- 只要題目中出現「括號配對」、「由內而外展開」這類具有層級關係、需要「存檔再讀檔」的特徵，最先要想到的就是恰好符合此特性的 Stack，這題示範了如何用「雙堆疊（分開存數字與字串）」來優雅地控制狀態切換