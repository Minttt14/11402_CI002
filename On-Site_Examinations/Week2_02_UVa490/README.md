# [UVa] [490] - [Rotating Sentences]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 490
- **題目標題:** Rotating Sentences
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=431)
- **正式程式碼 (正確/通過):** [src/s1131408-UVa490.cpp](./src/s1131408-UVa490.cpp)

## 2. 題目說明
將給定的多行字串順時針旋轉 90 度後輸出，每一行輸出的字元應該來自原始輸入的同一位數索引，且原始輸入的最後一行會變成旋轉後的第一個行
- **輸入:** 多行字串，長度不一（最大 100 字元，最多 100 行）
- **預期輸出:** 將原字串順時針旋轉90度後輸出
- **主要規則或限制**
  1. 若某一行較短，旋轉後對應的位置必須用空格補齊
- **核心任務:** 找出座標轉換規律並處理字串長度不一的補白問題

## 3. 思考邏輯與解題策略

### 初始想法

- 將字串視為一個二維矩陣，先全部讀取再做處理

### 最終策略

- 使用二維字元陣列，並在讀取前先用空格填滿整個陣列，省去後續補空白的問題

## 4. 虛擬碼

```text
START
1. 初始化二維字元陣列 arr[101][101]，將所有元素預填為「空格」 (' ')
2. 設定 row = 0 (計數總行數), tmp = 0 (追蹤最長字串長度)
3. 當 讀取到輸入字串 s 時：
   a. 如果 s 的長度大於 tmp，更新 tmp = s.length()
   b. 遍歷字串 s 的每個字元 s[i]：
      - 將其存入陣列對應位置 arr[row][i]
   c. row 加 1 (準備處理下一行輸入)

4. 開始旋轉輸出 (外層控制字元位置，內層控制行數反轉)：
   a. 外層迴圈 i 從 0 執行到 tmp - 1 (遍歷原字串的每一位數)：
      i. 內層迴圈 j 從 0 執行到 row - 1：
         - 輸出 arr[row - 1 - j][i] 
           (邏輯：由最後一行往第一行輸出，原 row 索引經反轉變成新 column)
      ii. 輸出一行結束後的換行符號 "\n"
END
```

### 正確程式碼

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

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 預先填滿空格後直接讀取 |
| 邊際情況 |  | 短行位置自動保留空格，格式完整 |
| 輸出處理 |  | 透過 tmp 記錄最長字串長度確保所有字元輸出 |

### 反思

- 一開始卡在如何動態補空白
- 這是一題「找規律」的題型，當直接思考不易時，可以先用紙筆模擬再下手。另外，此題當中的補空白要求也讓我學到有些題目可以先針對輸出的格式做預處理，能夠省去後續許多處理邊界或長度判斷的麻煩