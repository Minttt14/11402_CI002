# [LeetCode] [150] - [Evaluate Reverse Polish Notation]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 150
- **題目標題:** Evaluate Reverse Polish Notation
- **題目連結:** [Link to problem](https://leetcode.com/problems/evaluate-reverse-polish-notation/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode150-correct.cpp](./src/s1131408-LeetCode150-correct.cpp)

## 2. 題目說明
給一個字串陣列 tokens，該陣列代表一個以 RPN 撰寫的算術表達式，計算並回傳該表達式的結果
- **輸入:** 包含數字與運算符號 ("+", "-", "*", "/") 的字串陣列 tokens
- **預期輸出:** 計算結果的整數值
- **主要規則或限制**
  1. 兩個整數相除時，結果只保留整數部分
  2. 輸入的 RPN 表達式永遠是合法且可被計算的
- **核心任務:** 利用合適的資料結構依序解析符號與數字，解決算術式中「先乘除後加減」的優先順序問題

## 3. 思考邏輯與解題策略

### 初始想法

- 試著用 for 迴圈掃描，看到符號就去找它前面的兩個數字
- 每個運算符號處理完後，結果必須「就地替換」成一個新的數字供後續符號使用，需要大量的陣列插入與刪除操作，實作複雜，效能也很差

### 最終策略

- 利用 stack 模擬
- 遍歷每一個 token，如果遇到數字就 push 入堆疊中，遇到運算符號就從堆疊中 pop 出兩個數字，執行對應的運算後，將結果重新推入堆疊中，作為未來其他運算符號的運算元，堆疊中最後剩下的數字就是最終答案

## 4. 虛擬碼

```text
START
1. 宣告一個堆疊 st (為了防範中間過程溢位，型態設為 long long)
2. 遍歷字串陣列 tokens 中的每一個字串 token：
   a. 若 token 是運算符號 ("+", "-", "*", "/")：
      - 彈出 st 頂端元素作為「右運算元 (right)」
      - 再次彈出 st 頂端元素作為「左運算元 (left)」
      - 根據 token 符號執行運算：(left [operator] right)
      - 將計算結果推回 st
   b. 否則 (token 是數字)：
      - 將 token 轉換為整數型態 (stoll) 並推入 st
3. 迴圈結束後，回傳 st 的頂端元素做為答案
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        
        for(const string& token : tokens){
            if(token == "+" || token == "-" || token == "*" || token == "/"){
                long long right = st.top(); 
                st.pop();
                
                long long left = st.top(); 
                st.pop();
                
                if (token == "+") st.push(left + right);
                else if (token == "-") st.push(left - right);
                else if (token == "*") st.push(left * right);
                else if (token == "/") st.push(left / right); 
            } 
            else st.push(stoll(token));
        }
        return st.top();
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 遇到數字推入 satck ，遇到符號出 satck 計算 |
| 邊際情況 |  | 使用 stack<long long> 與 stoll() 避免中間過程的整數溢位 |
| 輸出處理 |  | right 先出，left 後出，確保正確的算術方向 |

### 反思
- 學到了如何利用 stack 特性來模擬後序運算式
- 若之後題目中字定了許多運算式， if-else 的邏輯會讓程式碼很冗長，可以考慮使用 Hash Map 配合 C++ Lambda 函數，建立一個運算子字典，將符號直接映射到具體的運算邏輯上