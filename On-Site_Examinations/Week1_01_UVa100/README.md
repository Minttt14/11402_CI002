# [UVa] [100] - [The 3n+1 Problem]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 100
- **題目標題:** The 3n+1 Problem
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=36)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa100-correct.cpp](./src/s1131408-UVa100-correct.cpp)

## 2. 題目說明
給定兩個整數 $i$ 與 $j$，計算在 $[i, j]$ 區間內（包含 $i$ 與 $j$）的所有整數中，經過 3n+1 運算回到 1 所需步數（包含起點與終點）的最大值是多少
- **輸入:** 整數 $i$ 與 $j$
- **預期輸出:** 輸出原始的 $i$ 與 $j$ 值，以及在 $[i, j]$ 區間內所有整數中，計算 3n+1 序列直到回到 1 所需的最大步數
- **主要規則或限制**
  1. 如果 $n$ 是奇數，則 $n = 3n + 1$
  2. 如果 $n$ 是偶數，則 $n = n / 2$
  3. 步數包含起點與終點的 1
  4. 輸入的 $i$ 可能大於 $j$
- **核心任務:** 遍歷給定區間內的所有數字，對每個數字執行 3n+1 運算並統計步數，最後找出最大值

## 3. 思考邏輯與解題策略

### 初始想法

- 直接實作 3n+1 的迴圈
- 使用 while 迴圈直到 $n$ 變為 1 為止，並用計數器紀錄次數

### 最終策略

- 題目給的 $i$ 可能大於 $j$，但在計算區間時需要從小到大遍歷，所以先輸出原始值後，再用 swap 確保 $i < j$
- 在遍歷區間的過程中，若當前數字的步數 cnt 大於目前紀錄的最大值 cycle，則更新 cycle
- 運算過程中 $3n+1$ 可能導致數值暫時超出 32-bit int 的範圍，因此將 $n$ 宣告為 long long

## 4. 虛擬碼

```text
START
1. 持續讀取整數 $i$ 與 $j$，若無資料則結束
2. 先依序輸出原始 $i$、$j$值
3. 比較i、j的大小，將較小的值放到i中
4. 實作3n+1邏輯，使用cnt計算每次循環長度
5. 迴圈遍歷，當cnt > cycle時更新cycle
6. 輸出cycle
END
```

### 正確程式碼

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

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 先判斷大小並交換後再執行迴圈 |
| 邊際情況 |  | 能正確處理任何順序的輸入 |
| 輸出處理 |  | 正確輸出區間內最大步數 |

### 反思

- 剛開始沒有考慮到i可能會大於j的情況，導致答案錯誤
- 下次要將題目讀懂再下手，要仔細考慮邊界情況與規定的輸出格式