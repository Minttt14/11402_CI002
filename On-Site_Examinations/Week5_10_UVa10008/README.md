# [UVa] [10008] - [What's Cryptanalysis]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10008
- **題目標題:** What's Cryptanalysis
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=949)
- **原始程式碼 (失敗):** [src/s1131408-UVa10008-fail.cpp](./src/s1131408-UVa10008-fail.cpp)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10008-correct.cpp](./src/s1131408-UVa10008-correct.cpp)

## 2. 題目說明

統計給定文本中各個英文字母出現的頻率，由高頻率往低頻率輸出，若頻率相同時先輸出英文字母排序較前的那一項
- **輸入:** 輸入一個整數 $n$，代表接下來有 $n$ 行文本
- **預期輸出:** 每一行輸出一個大寫字母與其出現次數，中間以空格隔開
- **主要規則或限制**
  1. 只統計英文字母，忽略數字、標點符號與空格
  2. 不分大小寫
  3. 依照出現次數由高到低排列；若次數相同，則依照字母在字母表中的順序排列
- **核心任務:** 建立字母出現頻率表，並實現多條件排序

## 3. 思考邏輯與解題策略

### 初始想法

- 使用一個大小為 26 的陣列來儲存每個字母出現的次數
- 在讀取與輸出時都要強制轉換很麻煩

### 最終策略

- 使用 map<char, int> 進行統計，它會自動按字母順序排列，後續再丟至 vector 中做頻率排序
- 透過轉存 vector 並使用自定義比較器，可以完全掌控多個排序條件

## 4. 虛擬碼

```text
START
1. 讀取行數 n
2. 執行 n 次循環：
   a. 讀取整行字串 s
   b. 遍歷 s 中的每個字元 c：
      - 如果 c 是英文字母：
        - 將 c 轉為大寫
        - 在 map[c] 中累加次數
3. 將 map 的內容 (字母, 次數) 複製到 vector v 中
4. 對 v 進行排序：
   - 條件 1: 若 a.次數 != b.次數，則回傳 a.次數 > b.次數 (降序)
   - 條件 2: 否則，回傳 a.字母 < b.字母 (升序)
5. 遍歷排序後的 v 並輸出結果
END
```

## 5. 錯誤程式碼 vs 正確程式碼


### 錯誤程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    cin.ignore(); 
    
    map<char, int> mp;
    while (n--) {
        string s;
        getline(cin, s);
        for (int i = 0; i < s.length(); i++) {
            if (isalpha(s[i])) {
                mp[toupper(s[i])]++; 
            }
        }
    }

    vector<pair<char, int>> v(mp.begin(), mp.end());

    sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b) {
        if (a.second != b.second) 
            return a.second > b.second; 
        return a.first < b.first;       
    });

    for (pair<char, int> i : mp) {
        cout << i.first << " " << i.second << "\n";
    }
}

```

**錯誤原因**

- 雖然在 vector 中進行了正確的排序，但最後輸出的時候卻遍歷了原始未經排序的 map

### 正確程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    cin.ignore(); 
    
    map<char, int> mp;
    while (n--) {
        string s;
        getline(cin, s);
        for (int i = 0; i < s.length(); i++) {
            if (isalpha(s[i])) {
                mp[toupper(s[i])]++; 
            }
        }
    }

    vector<pair<char, int>> v(mp.begin(), mp.end());

    sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b) {
        if (a.second != b.second) 
            return a.second > b.second; 
        return a.first < b.first;       
    });

    for (pair<char, int> i : v) {
        cout << i.first << " " << i.second << "\n";
    }
}

```

**可運作原因**

- 確保了程式輸出的內容是經過 sort 處理後的序列 v


## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 | 排序了 vector 卻沒使用它 | 正確遍歷排序後的 vector |
| 排序效果 | 永遠依照字母 A-Z 輸出 (map 特性) | 符合題目要求的雙重條件排序 |
| 輸出處理 | 忽略了排序的成果 | 輸出與排序結果同步 |

### 反思

- 在最後一步呼叫未排序的 map 導致輸出錯誤
- 觀察與比較輸出結果與預期結果的差異會更容易找出程式碼的錯誤處
- 撰寫輸出前先確認，目前要輸出的這個容器，是否是已經經過處理的那個


