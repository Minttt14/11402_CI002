# [UVa] [10041] - [Vito's Family]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10041
- **題目標題:** Vito's Family
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=982)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10041-correct.cpp](./src/s1131408-UVa10041-correct.cpp)

## 2. 題目說明
找一個最佳的位置建立自己的家，使得到所有親戚家的「總距離」最短
- **輸入:** 第一行為測試案例的數量 t，接下來的每一行代表一個測試案例，開頭第一個數字 r 是親戚的數量，接著的 r 個整數是親戚們的門牌號碼
- **預期輸出:** Vito 的家到所有親戚家的最小距離總和
- **主要規則或限制**
  1. 距離的計算方式為「絕對值差」
  2. 數個親戚可能住在同一個門牌號碼
- **核心任務:** 找出一個門牌號碼，使所有距離的絕對值總和最小化

## 3. 思考邏輯與解題策略

### 初始想法

- 把所有親戚的門牌加起來求平均值
- 平均數會使得「距離的平方和」最小化，但不會讓「絕對距離總和」最小化

### 最終策略

- 找中位數，保證可以讓總距離和最小
- 記錄所有門牌並進行排序，最中間那個數就是目標值

## 4. 虛擬碼

```text
START
1. 讀取測資數量 t
2. 當 t-- > 0 時：
   a. 讀取親戚數量 n
   b. 宣告大小為 n 的陣列 v
   c. 將親戚的門牌號碼依次存入 v
   d. 將陣列 v 進行升冪排序 (sort)
   e. 取得中位數 middle = v[n / 2]
   f. 初始化總距離 cnt = 0
   g. 遍歷陣列 v 中的每一個門牌號碼：
      - cnt = cnt + 絕對值(middle - 門牌號碼)
   h. 輸出 cnt
END
```

### 正確程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){	
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> v(n);
		
		for(int i=0; i<n; ++i){
			cin >> v[i];
		}
		sort(v.begin(), v.end());
		
		int middle = v[n/2];
		
		int cnt = 0;
		for(int i : v){
			cnt += abs(middle - i);
		}
		cout << cnt << "\n";
	}
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用中位數特性，找出最小化絕對距離 |
| 邊際情況 |  | n / 2 天然取中間偏右的點，對偶數或奇數皆成立 |
| 輸出處理 |  | 正確輸出最小的距離和 |

### 反思
- 「距離絕對值和最小化 $\to$ 中位數；距離平方和最小化 $\to$ 平均數」，這是一個在解題時可以直接拿來套用的定律
- 當親戚人數 n 為偶數時，其實中位數有兩個（中間偏左與中間偏右），而選在這兩個數字之間的任何一個點，求出來的總距離都會是一樣的