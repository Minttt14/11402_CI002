# UVa 10783 - Odd Sum

## 問題描述
 給予兩個整數 $a$ 與 $b$，計算區間 $[a, b]$ 中所有奇數的總和。[Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1724)

## 學習目標
- [ ] 掌握等差級數求和公式 $S_n = \frac{n(2a + (n-1)d)}{2}$
- [ ] 練習判斷區間內的項數 $n$ 與首項 $a$ 的調整
- [ ] 輸出格式練習

## 解題方法

### 演算法邏輯
1. 讀取a、b
2. 判斷a、b的奇偶性決定首項與項數
3. 套用等差級數公式，公差(d)為2
4. 依照格式輸出結果

### 關鍵見解
- 
- 

## 程式結構
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    int cnt = 0;
    while(t--){
        cnt ++;
        int a, b;
        cin >> a >> b;
        int n = 0;
        if(a%2 == 0 && b%2 != 0){
            n = ((b-a)/2) +1;
            a++;
        }
        else if(a%2 == 0 && b%2 == 0){
            n = ((b-a)/2);
            a++;
        }
        else{
            n = ((b-a)/2) +1;
        }
        cout << "Case " << cnt << ": " << (n*(2*a +(n-1)*2))/2 << "\n";
    }
}
```
[source code](./src/s1131408-UVa10783.cpp)

## 複雜度分析
- **時間複雜度:** O($T$)
  - $T$: 測資數量
- **空間複雜度:** O(1)

## 筆記與反思
- 挑戰: 
- 改進方向: 
- 學習心得: 

## 參考
- [Problem Link](https://onlinejudge.org/)