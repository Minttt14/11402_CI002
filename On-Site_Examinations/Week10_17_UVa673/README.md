# [UVa] [673] - [Parentheses Balance]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 673
- **題目標題:** Parentheses Balance
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=614)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa673-correct.cpp](./src/s1131408-UVa673-correct.cpp)

## 2. 題目說明
檢查一個字串中的括號（包含小括號 () 與中括號 []）是否正確平衡
- **輸入:** 測試案例數 $n$，接著是 $n$ 行包含括號的字串
- **預期輸出:** 若平衡輸出 Yes，否則輸出 No
- **主要規則或限制**
  1. 空字串是平衡的
  2. 如果 A 是平衡的，則 (A) 與 [A] 也是平衡的
  3. 如果 A 與 B 都是平衡的，則連接起來的 AB 也是平衡的
- **核心任務:** 確保每個右括號都能與最靠近它的左括號正確配對，且種類一致

## 3. 思考邏輯與解題策略

### 初始想法

- 用兩個變數紀錄 ( 與 [ 的數量，當讀到 ( 或 [ 時對應變數做增加， 讀到 ) 或 ] 時對應變數減少
- 數量對不代表順序對，例如 ([)] 數量一致但結構錯誤

### 最終策略

- 使用 stack<char>，遇到 ( 或 [ 直接推入堆疊，後續再分不同情況檢查是否平衡
- 使用 cin.ignore() 消除讀取 $n$ 之後殘留的換行符號，否則第一行 getline 會讀到空字串

## 4. 虛擬碼

```text
START
1. 讀取案例數 n
2. 清除輸入緩衝區的換行符 (cin.ignore)
3. 執行 n 次循環：
   a. 讀取整行字串 s
   b. 初始化 stack st 與 valid = true
   c. 遍歷字串中的每個字元 c：
      i.   如果是 '(' 或 '['，將其 push 入堆疊
      ii.  如果是 ')' 或 ']'：
           - 若 st 為空，則 valid = false, 中斷
           - 若 c 為 ')' 但 st.top 不是 '('，則 valid = false, 中斷
           - 若 c 為 ']' 但 st.top 不是 '['，則 valid = false, 中斷
           - 以上皆無，則 st.pop()
   d. 如果 valid 為真 且 st 是空的，輸出 "Yes"
   e. 否則輸出 "No"
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();
    while (n--) {
        string s;
        stack<char> st;
        getline(cin, s);
        bool valid = true;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(' || s[i] == '[') {
                st.push(s[i]);
            } 
            else if (s[i] == ')' || s[i] == ']') {
                if (st.empty()) {
                    valid = false;
                    break; 
                }
                if (s[i] == ')' && st.top() != '(') {
                    valid = false;
                    break;
                }
                if (s[i] == ']' && st.top() != '[') {
                    valid = false;
                    break;
                }
                st.pop();
            }
        }
        if (valid && st.empty()) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 維護順序性，符合括號「後進先出」邏輯 |
| 邊際情況 |  | 能正確攔截 st.top() 不符的情況 |
| 輸出處理 |  | 判斷 valid 標記與 st.empty() 後正確輸出 |

### 反思

- 堆疊的 LIFO 特性非常適合處理對稱性、倒序或是巢狀結構
- getline 在 cin >> n 之後使用時，如果不加 ignore()，第一個讀到的字串會是 $n$ 後面的那個空換行
