# [UVa] [10783] - [Odd Sum]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10783
- **題目標題:** Odd Sum
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1724)
- **正式程式碼 (正確/通過):** [src/s1131408-UVa10783.cpp](./src/s1131408-UVa10783.cpp)

## 2. 題目說明

給予兩個整數 $a$ 與 $b$，計算區間 $[a, b]$ 中所有奇數的總和
- **輸入:** 第一行是測試資料的數量 $T$，接著每組包含兩個整數 $a$ 與 $b$（$0 \le a \le b \le 100$）
- **預期輸出:** 依照格式輸出為第幾筆資料以及總和
- **主要規則或限制**
  1. 需判斷邊界是否為奇數
- **核心任務:** 正確識別區間內的第一個奇數（首項）與奇數的總個數（項數）

## 3. 思考邏輯與解題策略

### 初始想法

- 利用等差數列和計算

### 最終策略

- 根據 a 的奇偶性調整首相與項數再套公式

## 4. 虛擬碼

```text
START
1. 讀取測試案總數 T
2. 初始化計數器 caseCnt = 1
3. 當 T > 0 時循環：
   a. 讀取 a, b
   b. 初始化項數 n = 0
   c. 判斷狀況：
      - 若 a 偶, b 奇：n = ((b-a)/2) + 1, a = a + 1
      - 若 a 偶, b 偶：n = ((b-a)/2), a = a + 1
      - 其餘 (a 奇)：n = ((b-a)/2) + 1
   d. 計算結果 ans = (n * (2*a + (n-1)*2)) / 2
   e. 輸出 "Case [caseCnt]: [ans]"
   f. caseCnt + 1, T - 1
END
```

### 正確程式碼

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

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 使用等差級數公式，直接算出結果 |
| 邊際情況 |  | 透過 if-else 判斷奇偶性，校正首項 $a$ 並根據區間長度精確推導出項數 $n$ |
| 輸出處理 |  | 使用計數器 cnt 並嚴格依照題目所需格式輸出 |

### 反思

- 在調整首項與項數時可以用紙筆模擬，較不易出錯