# [UVa] [11615] - [Family Tree]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 11615
- **題目標題:** Family Tree
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2662)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa11615-correct.cpp](./src/s1131408-UVa11615-correct.cpp)

## 2. 題目說明
給定一個特定世代深度的完美二元樹，每個人都恰有兩個父母，但是在這個家族中有一對兄弟具有相同父母，相同的父母不該被重複計算，目標是計算這個家族中實際擁有的人數
- **輸入:**  第一行包含一個整數代表測試案例數，接續每行包含三個整數，depth（家族樹總世代數）、$A$ 與 $B$（家族成員編號）
- **預期輸出:** 該家族樹中相異成員的最大可能數量
- **主要規則或限制**
  1. 根節點（1）代表本人，其子節點代表父母，再往下代表祖先，因此編號越大，代表越古老的世代
  2. 成員 $A$ 與成員 $B$ 實際上是同一個人
  3. 不能有成員被重複計算
- **核心任務:** 當兩個不同世代的節點重合時，較深世代（較老）其上的所有祖先子樹，都會完全與較淺世代（較年輕）的祖先子樹重疊。必須扣除這些重複的冗餘節點

## 3. 思考邏輯與解題策略

### 初始想法

- 想要一步一步見出樹再將重複的點刪除
- 邏輯判斷複雜且耗時

### 最終策略

- 觀察規律，利用數學算法再加上判斷式處理不同的情況
- 透過二進位區間，先用迴圈找出 $A$ 與 $B$ 分別位於哪一層（da 與 db），接著利用幾何級數，算出如果扣除 $A$ 或 $B$ 的祖先子樹時，各自會砍掉多少個子節點（a_child 與 b_child）
- 四種不同的判斷式
  1. if(da == depth || db == depth)：其中一人在最後一代（葉子節點），其身後沒有任何祖先子樹可以扣除，直接輸出總數
  2. else if(da > db)：$A$ 的世代比較深（老），$A$ 的祖先子樹完全被 $B$ 包容，因此直接扣除較小的 a_child
  3. else if(da < db)：$B$ 的世代比較深（老），$B$ 的祖先子樹完全被 $A$ 包容，因此直接扣除較小的 b_child
  4. else if(da == db)：兩者在同一層，對稱結構下扣除哪一個子樹（a_child）的數量都一樣

## 4. 虛擬碼

```text
START
1. 讀取測試案例數 n
2. 當 n-- > 0：
   a. 讀取 depth, a, b
   b. 計算標準完美二元樹總節點數 member = 2^depth - 1
   c. 尋找 a 的所在層級 da（滿足 a < 2^i 的最小 i）
   d. 尋找 b 的所在層級 db（滿足 b < 2^i 的最小 i）
   e. 計算 a 與 b 兩者若被扣除時的子樹大小 a_child 與 b_child：
      - a_child = sum(2^i)，其中 i 從 1 到 (depth - da)
      - b_child = sum(2^i)，其中 i 從 1 到 (depth - db)
   f. 條件判斷輸出：
      - 若 da == depth 或 db == depth：輸出 member
      - 若 da >= db：輸出 member - a_child
      - 若 da < db：輸出 member - b_child
END
```

### 正確程式碼

```cpp
# include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	while(n--){
		int depth, a, b , da, db;
		cin >> depth >> a >> b;
		
		int member = pow(2, depth) -1;
		
		for(int i=1; i<=depth; ++i){
			if(a < pow(2, i)){
				da = i;
				break;
			}
		}
		
		for(int i=1; i<=depth; ++i){
			if(b < pow(2, i)){
				db = i;
				break;
			}
		}
		int tmp1 = (depth - da);
		int tmp2 = (depth - db);
		int a_child = 0;
		int b_child = 0;
		
		for(int i=1; i<=tmp1; ++i){
			a_child += pow(2, i);
		}
		for(int i=1; i<=tmp2; ++i){
			b_child += pow(2, i);
		}
		
		if(da == depth || db == depth) cout << member << "\n";
		else if(da > db) cout << member - a_child << "\n";
		else if(da < db) cout << member - b_child << "\n";
		else if(da == db) cout << member - a_child << "\n";
	}	
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用完全二元樹規律，直接算出總數與子樹大小 |
| 邊際情況 |  | 利用四種不同的判斷式，精確分流深淺關係，自然相容各種邊界 |
| 輸出處理 |  | 直接以 member - child 公式計算， $O(1)$ 速度正確輸出結果 |

### 反思

- 這題透過完全二元樹的幾何特性，讓我們發現所有的重疊規律只跟「層級（Depth）」有關，進而能用四個精準的判斷式正確輸出，而不用暴力建樹
- 實作第四個判斷式時，不小心寫成了賦值 da = db，但因為前三個條件已經把「大於」與「小於」排除，走到這裡時 da 本來就等於 db，且兩者算出來的 child 數量完全對稱，這才讓這個數學算法誤打誤撞順利通過。下次在寫判斷式時，必須更專注於 == 的寫法，讓邏輯更加完美
