# [UVa] [11364] - [Parking]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 11364
- **題目標題:** Parking
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2349)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa11364-correct.cpp](./src/s1131408-UVa11364-correct.cpp)

## 2. 題目說明
開車去一條直線街道上的商店購物，必須造訪所有的商店，最後還要回到車子停放的位置，找找一個最優的停車位，讓總步行距離最小
- **輸入:** 測試案例數 $t$，每組案例包含商店數量 $n$ ($1 \le n \le 20$)，以及 $n$ 個商店在數線上的位置
- **預期輸出:** 最短的步行距離
- **主要規則或限制**
  1. 商店全部位在一條直線上
  2. 必須造訪所有商店，且最終必須回到起點
- **核心任務:** 找出涵蓋所有點並返回原點的最短路徑長度

## 3. 思考邏輯與解題策略

### 初始想法

- 用中位數來決定停車位

### 最終策略

- 在一條直線上，如果要拜訪最左邊的點（$minPos$）和最右邊的點（$maxPos$）並回到起點，無論車子停在這兩個點之間的哪個位置，都得走完這段區間兩次，總路程就是 $2 \times (\text{maxPos} - \text{minPos})$
- 如果只有一家店或者店家都在相同位置上，則 $maxPos = minPos$，距離為 0

## 4. 虛擬碼

```text
START
1. 讀取測試案例數 t
2. 當 t-- > 0:
   a. 讀取商店數量 n
   b. 初始化 minPos = 100, maxPos = -1 (根據題目範圍)
   c. 迴圈 n 次讀取每個位置 x:
      i. 若 x < minPos，更新 minPos = x
      ii. 若 x > maxPos，更新 maxPos = x
   d. 計算 距離 = (maxPos - minPos) * 2
   e. 輸出 距離 並換行
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        int minPos = 100;
        int maxPos = -1;
        
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x < minPos) minPos = x;
            if (x > maxPos) maxPos = x;
        }
        cout << (maxPos - minPos) * 2 << endl;
    }
    return 0;
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 只需計算最外層的兩個端點 |
| 邊際情況 |  | 正確初始化 minPos = 100（上限外）與 maxPos = -1，確保能捕捉數線上任何點 |
| 輸出處理 |  | 直接輸出 $(maxPos - minPos) \times 2$，簡潔且符合題目要求的返回起點規則 |

### 反思

- 在處理「線性距離」的問題時，觀察邊界值往往比處理中間的數據更重要
- 下次遇到類似問題時會優先思考這是不是一個「範圍涵蓋」的問題，在 1D 空間中，覆蓋所有點的最短路徑一定是連通端點的線段