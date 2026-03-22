# [UVa] [10035] - [Primary Arithmetic]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10035
- **題目標題:** Primary Arithmetic
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=97)
- **正式程式碼 (正確/通過):** [src/s1131408-UVa10035.cpp](./src/s1131408-UVa10035.cpp)

## 2. 題目說明

給予兩個非負整數，計算將這兩個數相加時，一共會產生多少次「進位」動作
- **輸入:** 兩個不超過 10 位數的非負整數，以 0 0 作為結束符號
- **預期輸出:** 輸出進位的次數，依照不同次數輸出不同格式
- **主要規則或限制**
  1. 每一位的進位會影響到下一位的相加
- **核心任務:** 模擬每一位相加並處理連鎖進位的邏輯，同時注意輸出的單複數格式

## 3. 思考邏輯與解題策略

### 初始想法

- 用取餘數與取商數的方法一位一位進行處理
- 計數器記錄進位次數

### 最終策略

- 使用迴圈搭配 %10 取得當前最低位，並用 /10 移除已處理位數
- 注意 0 0 為結束條件
- 輸出格式需依照次數做單複數變化

## 4. 虛擬碼

```text
START
1. 讀取兩個整數 A, B
2. 如果 A=0 且 B=0 則結束
3. 設定 carry = 0, count = 0
4. 當 (A > 0 或 B > 0) 時循環：
   a. sum = (A % 10) + (B % 10) + carry
   b. 如果 sum >= 10:
      carry = 1, count++
   c. 否則: carry = 0
   d. A = A / 10, B = B / 10
5. 根據 count 數值輸出對應的格式
END
```

### 正確程式碼

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

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 判斷 a%10 + b%10 + carry |
| 邊際情況 |  | 透過 carry 變數處理連續進位 |
| 輸出處理 |  | 區分 No carry / 1 operation / n operations |

### 反思

- 第一次執行時忘記將carry重置、忽略輸出時cnt為1的情況時應為operation而非operations
- 核心邏輯正確後也要注意輸出的要求，免得因此失分