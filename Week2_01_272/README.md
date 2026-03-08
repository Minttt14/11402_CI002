# UVa 272 - TEX Quotes

## 問題描述
 讀取輸入文本中成對出現的雙引號，將第一次出現的(")轉換為(``)，第二次出現轉換為('')，直到輸入結束。[Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=208)

## 學習目標
- [ ] 跳脫字元的應用
- [ ] 練習基礎字串遍歷與字元比對
- [ ] 處理包含空格的整行輸入 (getline)

## 解題方法

### 演算法邏輯
1. 使用getline讀取輸入
2. for迴圈遍歷每個字元
3. 以cnt判斷目前遇到的雙引號奇偶性
4. 奇數輸出(``);偶數輸出('')，其餘依原文本輸出

### 關鍵見解
- 雙引號成對出現，因此可利用%2或bool變數來記錄當前雙引號的狀態

## 程式結構
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
[source code](./src/s1131408-UVa272.cpp)

## 複雜度分析
- **時間複雜度:** O(N)
  - $N$: 文本的總字元數
- **空間複雜度:** O(L)
  - $L$: 單行文本的最大長度

## 筆記與反思
- 學習心得: 當程式在不同條件會有不同輸出的情況下，可利用簡易的計數器或bool來記錄與切換程式行為

## 參考
- [Problem Link](https://onlinejudge.org/)