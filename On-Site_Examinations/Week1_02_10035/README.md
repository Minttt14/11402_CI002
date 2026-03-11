# UVa 10035 - Primary Arithmetic

## 問題描述
給予兩個非負整數，計算將這兩個數相加時，一共會產生多少次「進位」動作。 [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=97)

## 學習目標
- [ ] 理解基本算術
- [ ] 實作迭代邏輯
- [ ] 練習 C++ 中的輸入/輸出處理、格式調整

## 解題方法

### 演算法邏輯
1. 讀取輸入
2. 將兩數個別取餘數後相加，若總和大於等於 10，則將 carry 設為 1 並增加計數器 cnt；否則 carry 歸零
3. 利用 / 10 去除已處理的末位，重複步驟直到兩數皆處理完畢
4. 依不同結果與格式輸出

### 關鍵見解
- 即使當前位數相加只有 9，若前一位有進位（9 + 0 + 1），依然會產生新的進位，因此 carry 必須參與每一次的 sum 計算
- 數字可高達 10 位數，使用long long避免溢位

## 程式結構
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n1, n2;
    
    while (cin >> n1 >> n2 && (n1 != 0 || n2 != 0)){
        int carry = 0;  
        int cnt = 0;
        
        while (n1 > 0 || n2 > 0){
            int sum = (n1 % 10) + (n2 % 10) + carry;
            
            if(sum >= 10){
                carry = 1;
                cnt++; 
            } 
            else
            {
                carry = 0;
            }
            n1 /= 10;
            n2 /= 10;
        }
        
        if(cnt == 0){
            cout << "No carry operation." << endl;
        } 
        else if(cnt == 1){
            cout << "1 carry operation." << endl;
        }
        else{
            cout << cnt << " carry operations." << endl;
        }
    }
}
```
[source code](./src/s1131408-UVa10035.cpp)

## 複雜度分析
- **時間複雜度:** O($\log N$)
- **空間複雜度:** O(1)

## 筆記與反思
- 挑戰: 忘記將carry重置、忽略輸出時cnt為1的情況時應為operation而非operations
- 改進方向: 可同步使用紙筆作計算，更容易發現細微的錯誤邏輯
- 學習心得: 此題的運算邏輯固然簡單，當中卻暗藏些許小細節，若忽略將導致程式錯誤，因此在閱讀題目以及輸出時要特別注意格式

## 參考
- [Problem Link](https://onlinejudge.org/)