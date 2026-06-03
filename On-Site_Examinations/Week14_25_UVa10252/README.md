# [UVa] [10252] - [Common Permutation]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10252
- **題目標題:** Common Permutation
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1193)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10252-correct.cpp](./src/s1131408-UVa10252-correct.cpp)

## 2. 題目說明
找出兩個字串的共同字母，並將這些共同字母依照字母順序印出
- **輸入:** 多組測資，每組包含兩行字串 s1 和 s2
- **預期輸出:** s1 和 s2 共同擁有的字元，按字母順序排列
- **主要規則或限制**
  1. 某個字元在輸出中出現的次數，必須是它在 s1 和 s2 中出現次數的較小值
  2. 必須精確處理空白或空字串的輸入，否則會導致測資讀取錯位
- **核心任務:** 統計兩字串的字元頻率，取交集後按順序輸出

## 3. 思考邏輯與解題策略

### 初始想法

- 建立一個結果字串，遍歷 s1 的每個字元，去 s2 裡面找，找到了就把該字元加入結果字串中，並且把 s2 中的那個字元刪除或標記
- 字串的比對、刪除操作很耗時

### 最終策略

- 使用兩個 map<char, int>分別記錄 s1 和 s2 的字元頻率
- 用一個迴圈從 'a' 跑到 'z'，對於每個字元，取它在兩個 Map 中出現次數的最小值（min(mp_a[c], mp_b[c])）。如果是 0 代表沒有交集就不印，如果是大於 0 的整數 k，就連續印出 k 次
 
## 4. 虛擬碼

```text
START
1. 當 可以讀取一整行存入 s1 時：
   a. 讀取下一整行存入 s2
   b. 建立並初始化兩個字典 mp_a 和 mp_b
   c. 遍歷 s1，將每個字元出現次數記錄進 mp_a
   d. 遍歷 s2，將每個字元出現次數記錄進 mp_b
   e. 針對字元 c 從 'a' 到 'z' 依序遍歷：
      i.   找出 c 在兩字典中次數的最小值 k = min(mp_a[c], mp_b[c])
      ii.  執行 k 次：印出字元 c
   f. 印出換行符號
END
```

### 正確程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){	
	string s1, s2;
	while(getline(cin, s1)){
		getline(cin, s2);
		
		map<char, int> mp_a;
		map<char, int> mp_b;
		
		for(int i=0; i<s1.length(); ++i){
			mp_a[s1[i]] ++;
		}
		
		for(int i=0; i<s2.length(); ++i){
			mp_b[s2[i]] ++;
		}
		
		for(char c = 'a'; c <= 'z'; c++){
			int k = min(mp_a[c], mp_b[c]);
			
			while(k--){
				cout << c;
			}
		}
		cout << "\n";
	}
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 統計頻率後直接取最小值 |
| 邊際情況 |  | 使用 getline(cin, s)處理空字串 |
| 輸出處理 |  | 按照 'a' 到 'z' 走訪，天然具備排序效果 |

### 反思
- 輸入可能會有「空行」，如果用 cin >> s1，遇到空行時它會直接跳過去吃下一行的非空白字元，導致原本該配對的字串發生錯位，因此使用getline(cin, s1)是最安全的寫法
- 字元範圍只限於 'a' 到 'z'（ASCII 碼固定），如果想追求極致效能，可以改用 int countA[26] = {0} 和 int countB[26] = {0}，利用 s1[i] - 'a' 當作陣列索引，執行速度會比 map 更快