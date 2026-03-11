# UVa 490 - Rotating Sentences

## 問題描述
 將給定的多行字串順時針旋轉 90 度後輸出，每一行輸出的字元應該來自原始輸入的同一位數索引，且原始輸入的最後一行會變成旋轉後的第一個行。[Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=431)

## 學習目標
- [ ] 練習二維陣列的宣告與初始化
- [ ] 掌握二維陣列索引 ($i, j$) 的旋轉映射關係
- [ ] 處理不同長度字串相加時的空白補齊問題

## 解題方法

### 演算法邏輯
1. 因題目說明字串長度小於100，先宣告二維陣列 arr[101][101]並填滿空格，方便後續長度不一時自動填空格
2. 使用 getline 讀取每一行
3. 將字元存入陣列，並記錄總共有幾行 (row) 以及最長的字串長度 (tmp)
4. 外層迴圈遍歷字元索引（對應原始字串的位數），內層迴圈則由最後一行往第一行遍歷
5. 輸出重新排列後的字串

### 關鍵見解
- 如果某一行的長度比其他行短，旋轉後該位置必須輸出空格，預先初始化整個陣列為空字元可省去後續的判斷與補空白
- 輸出時colunm的索引值不受影響，只有row需要反向由最後一行往第一行逐行輸出

## 程式結構
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int row = 0;
    char arr[101][101];
    int tmp = 0;

    for(int i = 0; i < 101; i++) {
        for(int j = 0; j < 101; j++) {
            arr[i][j] = ' ';
        }
    }

    while(getline(cin, s)){
        if(s.length() > tmp) tmp = s.length(); 
        for(int i=0; i<s.length(); ++i){
            arr[row][i] = s[i];
        }
        row++;
    }
    for(int i=0; i<tmp; ++i){
        for(int j=0; j<row; ++j){
            cout << arr[row -1 -j][i];
        }
        cout << "\n";
    }
}
```
[source code](./src/s1131408-UVa490.cpp)

## 複雜度分析
- **時間複雜度:** O($R \times L$)
- **空間複雜度:** O($R \times L$)
  - $R$: 行數
  - $L$: 最長字串的長度

## 筆記與反思
- 挑戰: 雙層迴圈的運行邏輯容易混亂、忽略字串長短不同時須補空白
- 改進方向: 可用紙筆簡單繪製二維陣列，並模擬各行長度不同的情況，視覺化的方式能更有效並快速梳理程式邏輯與除錯
- 學習心得: 這是一題「找規律」的題型，當直接思考不易時，可以先用紙筆模擬再下手。另外，此題當中的補空白要求也讓我學到有些題目可以先針對輸出的格式做預處理，能夠省去後續許多處理邊界或長度判斷的麻煩。

## 參考
- [Problem Link](https://onlinejudge.org/)