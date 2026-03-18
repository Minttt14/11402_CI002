# UVa 10170 - The Hotel with Infinite Rooms

## 問題描述
 一間旅館有無限多個房間。一組大小為 $S$ 的團體會在第 1 天入住並住滿 $S$ 天。接著下一組大小為 $S+1$ 的團體會在第 $S+1$ 天入住並住滿 $S+1$ 天。給定起始團體人數 $S$ 與目標天數 $D$，求第 $D$ 天時旅館內的團體人數。[Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1111)

## 學習目標
- [ ] 練習使用 while 迴圈模擬時間演進
- [ ] 理解等差數列的成長概念
- [ ] 處理大數值範圍（天數 $D$ 可達 $10^{15}$）

## 解題方法

### 演算法邏輯
1. 讀取起始人數與目標天數
2. 將起始人數先存進tmp中，宣告cnt計算加了幾次人數
3. while迴圈，當不足目標天數時目標天數減去當前團體人數
4. 輸出初始人數加上計數器結果

### 關鍵見解
- D的數字有可能極大，使用long long避免溢位
- S的增長是等差數列，尋找第一次使數列和大於等於D的值

## 程式結構
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
[source code](./src/s1131408-UVa10170.cpp)

## 複雜度分析
- **時間複雜度:** O($\sqrt{D}$)
  - $D$: 目標天數
- **空間複雜度:** O(1)

## 筆記與反思
- 改進方向: 其實不需要額外建立tmp與cnt計算，直接對s進行運算即可(while(d > s) { d -= s; s++; })
- 學習心得: 閱讀題目時可以觀察題目的規律性，並利用此規律著手

## 參考
- [Problem Link](https://onlinejudge.org/)