# [UVa] [10931] - [Parity]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10931
- **題目標題:** Parity
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1872)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10931-correct.cpp](./src/s1131408-UVa10931-correct.cpp)

## 2. 題目說明

輸入一個正整數，轉成二進制的格式並計算二進制形式下有幾個1
- **輸入:** 一系列的正整數 $I$ ($1 \le I \le 2^{31}-1$)，以 0 作為輸入結束
- **預期輸出:** 格式為 The parity of B is P (mod 2).，其中 $B$ 是該數的二進位字串，$P$ 是二進位中 1 的數量
- **主要規則或限制**
  1. 輸入的整數範圍可達 $2^{31}-1$，需注意資料型別
  2. 二進位轉換時，最低位會先被算出，但輸出時必須由高位到低位
- **核心任務:** 實作十進位轉二進位的演算法，並統計過程中 1 出現的次數

## 3. 思考邏輯與解題策略

### 初始想法

- 用除以 2 取餘數的方法來獲得二進位位元

### 最終策略

- 改用 string 來存取每個位元，並搭配 reverse() 進行翻轉
- 當存入位元為 1 時，計數器同步加 1 處理
- 使用 long long 宣告防止溢位

## 4. 虛擬碼

```text
START
1. 當 讀取到整數 n 且 n 不為 0 時：
   a. 初始化 空字串 b, 計數器 cnt = 0
   b. 當 n > 0 時：
      i. 若 n 除以 2 的餘數為 1：
         - b 加上 '1', cnt 加 1
      ii. 否則：
         - b 加上 '0'
      iii. n = n / 2
   c. 反轉字串 b
   d. 輸出 "The parity of [b] is [cnt] (mod 2)."
END
```

### 正確程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    while (cin >> n && n != 0) {
        string b = "";
        int cnt = 0;
        
        while (n > 0) {
            if (n % 2 == 0) {
                b += '0';
            } else {
                b += '1';
                cnt ++;
            }
            n /= 2;
        }

        reverse(b.begin(), b.end());   
        cout << "The parity of " << b << " is " << cnt << " (mod 2).\n";
    }
    return 0;
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 模仿手算邏輯，易於理解與除錯 |
| 邊際情況 |  | 透過 n /= 2 確保迴圈能收斂到 0 |
| 輸出處理 |  | 直接將餘數轉字元存入 string ，反轉後輸出 |

### 反思

- 加強進位制轉換的基礎邏輯
-  除了除法也能考慮使用位元運算 (n >> i) & 1。這樣可以從最高位開始讀取，省去最後 reverse 字串的步驟