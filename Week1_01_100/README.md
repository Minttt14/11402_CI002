# UVa 100 - The 3n+1 Problem

## 問題描述
Brief description of the problem here. [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=36)

## 學習目標
- [ ] 理解 3n+1 猜想
- [ ] 實作迭代邏輯
- [ ] 練習 C++ 的輸入與輸出處理

## 解題方法

### 演算法邏輯
1. 讀取輸入
2. 先依序輸出原始i、j值
3. 比較i、j的大小，將較小的值放到i中
4. 實作3n+1邏輯，使用cnt計算每次循環長度
5. 迴圈遍歷，當cnt > cycle時更新cycle
6. 輸出cycle

### 關鍵見解
- 題目給的i可能大於j，但輸出時必須維持原始順序
- 運算過程中，3n+1可能導致數值暫時超出32-bit整數範圍，使用long long處理運算過程中的n

## 程式結構
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int i, j;
    while (cin >> i >> j) {
        cout << i << " " << j << " ";
        
        if (i > j) swap(i, j);
        
        int cycle = 0;
        
        for (int a = i; a <= j; ++a) {
            long long n = a;
            int cnt = 1;
            
            while (n != 1) {
                if (n % 2 != 0) {
                    n = 3 * n + 1;
                } 
                else {
                    n /= 2;
                }
                cnt++;
            }
            
            if (cnt > cycle) {
                cycle = cnt;
            }
        }
        cout << cycle << "\n";
    }
}
```
[source code](./src/s1131408-UVa100.cpp)

## 複雜度分析
- **時間複雜度:** O(T \times L \times K)
  - $T$: 測試資料的筆數 (Total Test Cases)
  - $L$: 區間長度，即 $|j - i| + 1$
  - $K$: 該區間內數字的最大循環長度 (Max Cycle Length)
- **空間複雜度:** O(1)

## 筆記與反思
- 挑戰:沒有考慮到i可能會大於j的情況，導致答案錯誤
- 改進方向:作答前要謹慎考慮各種可能情況
- 學習心得:將題目讀懂再下手，注意邊界與溢位的可能性

## References
- [Problem Link](https://onlinejudge.org/)