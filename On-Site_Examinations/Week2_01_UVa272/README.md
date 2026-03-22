# [UVa] [272] - [TEX Quotes]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 272
- **題目標題:** TEX Quotes
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=208)
- **正式程式碼 (正確/通過):** [src/s1131408-UVa272.cpp](./src/s1131408-UVa272.cpp)

## 2. 題目說明
讀取輸入文本中成對出現的雙引號，將第一次出現的(")轉換為(``)，第二次出現轉換為('')，直到輸入結束
- **輸入:** 包含多行文字的文本，其中含有數量不等的雙引號
- **預期輸出:** 將第一次出現的(")轉換為(``)，第二次出現轉換為('')，其餘字元保持不變
- **主要規則或限制**
  1. 判斷目前遇到的雙引號是左引號還是右引號
- **核心任務:** 實作一個全域的狀態追蹤器，確保跨行讀取時引號的奇偶順序不會中斷

## 3. 思考邏輯與解題策略

### 初始想法

- 用getline讀取文本
- 使用簡易的計數器來確認遇到的雙引號是開始還是結束

### 最終策略

- 利用 cnt 判斷要輸出 `` 或 ''
- 引號會跨行出現 cnt 必須宣告在 while 迴圈之外

## 4. 虛擬碼

```text
START
1. 初始化 cnt = 1
2. 當讀取到輸入的一整行字串 s 時 (使用 getline)：
   a. 遍歷字串 s 中的每一個字元 s[i]：
      i. 如果 s[i] 等於 雙引號 (")：
         - 如果 cnt 為奇數 (cnt % 2 != 0)：
           輸出兩個反引號 "``"
         - 否則 (cnt 為偶數)：
           輸出兩個單引號 "''"
         - 將 cnt 加 1
      ii. 否則 (字元不是雙引號)：
         直接輸出該字元 s[i]
   b. 處理完該行後，輸出一個換行符號 "\n"
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){

    string s;
    int cnt = 1;

    while(getline(cin, s)){
        for(int i=0; i<s.length(); ++i){

        if(s[i] == '\"'){
            if(cnt % 2 != 0){
                cout<<"``";
            }
            else{
                cout<<"''";
            } 
            cnt++;
        }
        else{
            cout<<s[i];
        }
    }
    cout<<"\n";
    }
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 將 cnt 定義在 while 迴圈外，確保引號狀態在整個文本流中延續 |
| 邊際情況 |  | 能夠處理引號跨行出現的情況 |
| 輸出處理 |  | 根據 cnt 的奇偶性精確輸出 `` (左) 或 '' (右) |

### 反思

- 當程式在不同條件會有不同輸出的情況下，可利用簡易的計數器或bool來記錄與切換程式行為
- 對於這種逐字元處理且不需回頭檢查的問題，其實可以使用 getchar() 或 cin.get(c)，連 getline 都可以省略，程式會更簡潔且節省記憶體