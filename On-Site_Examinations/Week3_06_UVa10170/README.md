# [UVa] [10170] - [The Hotel with Infinite Rooms]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10170
- **題目標題:** The Hotel with Infinite Rooms
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1111)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10170-correct.cpp](./src/s1131408-UVa10170-correct.cpp)

## 2. 題目說明

一間旅館有無限多個房間。一組大小為 $S$ 的團體會在第 1 天入住並住滿 $S$ 天。接著下一組大小為 $S+1$ 的團體會在第 $S+1$ 天入住並住滿 $S+1$ 天。給定起始團體人數 $S$ 與目標天數 $D$，求第 $D$ 天時旅館內的團體人數
- **輸入:** 起始團體人數 $S$ ($1 \le S \le 10,000$) 與目標天數 $D$ ($1 \le D \le 10^{15}$)
- **預期輸出:** 第 $D$ 天時，當時房間內的團體人數
- **主要規則或限制**
  1. $D$ 的數值極大，必須使用 long long
  2. 每一組住的天數剛好等於該組的人數
- **核心任務:** 模擬天數的消耗，直到累積天數達到或超過 $D$

## 3. 思考邏輯與解題策略

### 初始想法

- 用計數器紀錄總共加了幾次人數

### 最終策略

- 用一個計數器 cnt 來紀錄人數增加的次數，並用 tmp 紀錄當前團體的人數
- 因為每次增加的人數都是 1 ， cnt 加上原本人數 S 即為答案

## 4. 虛擬碼

```text
START
1. 當 讀取到起始人數 s 與 目標天數 d (long long) 時：
   a. 初始化 計數器 cnt = 0
   b. 初始化 暫存變數 tmp = s 
   c. 執行迴圈，當 d 大於 tmp 時 (代表第 d 天還沒輪到這組或之後的人)：
      i.   從 d 中減去當前團體的天數：d = d - tmp
      ii.  準備處理下一組團體，人數加 1：tmp = tmp + 1
      iii. 紀錄團體更迭次數：cnt = cnt + 1
   d. 輸出起始人數 s 加上增加次數 cnt (s + cnt)
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h> 
using namespace std;

int main(){
	int s;
	long long d;
	
	while(cin >> s >> d){	
		int cnt = 0;
		int tmp = s;
		while(d>tmp){
			d -= tmp;
			tmp++;
			cnt++;
		}
		cout << s + cnt << "\n";
	}

}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 使用 while 迴圈模擬，透過 d -= tmp 逐次扣除天數，直觀且不易出錯 |
| 邊際情況 |  | 將 $D$ 宣告為 long long，確保能處理極大範圍的天數運算 |
| 輸出處理 |  | 透過 s + cnt 計算結果，保持了初始人數與增加組數的邏輯連結 |

### 反思

- 其實不需要額外建立tmp與cnt計算，直接對s進行運算即可(while(d > s) { d -= s; s++; })
- 對於這類等差級數求和的問題，可以使用一元二次方程式求根公式： $\frac{(S + n)(n - S + 1)}{2} \ge D$ ，可達到 $O(1)$ 的速度