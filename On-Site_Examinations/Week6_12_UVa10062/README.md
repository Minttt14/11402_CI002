# [UVa] [10062] - [Tell me the frequencies!]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10062
- **題目標題:** Tell me the frequencies!
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1003)
- **原始程式碼 (失敗):** [src/s1131408-UVa10062-fail.cpp](./src/s1131408-UVa10062-fail.cpp)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10062-correct.cpp](./src/s1131408-UVa10062-correct.cpp)

## 2. 題目說明

統計輸入字串中每個字元出現的次數，並依照 ASCII 值與出現頻率進行排序輸出
- **輸入:** 每一行代表一個測試字串，直到檔案結束 (EOF)
- **預期輸出:** 輸出各字元的 ASCII 值與出現頻率
- **主要規則或限制**
  1. 出現次數少的排在前面
  2. 若出現次數相同，ASCII 值大的排在前面
  3. 每兩組測試結果之間必須有一個空行
- **核心任務:** 讀取字串並實現特定的雙重條件排序

## 3. 思考邏輯與解題策略

### 初始想法

- 使用 vector 來存取字元

### 最終策略

- 使用 map<char, int> 統計，再丟進丟進 vector 中自定義排序
- 用計數器控制除了第一組數據外，每組數據輸出前先印出一個換行符

## 4. 虛擬碼

```text
START
1. 初始化測試組計數器 first_case = true
2. 只要讀取得到一行字串 s：
   a. 如果不是第一組測試結果，輸出一個空行
   b. 初始化 map 統計 s 中所有字元的出現頻率
   c. 將統計結果存入 vector v
   d. 對 v 進行排序：
      - 若次數不同：回傳 次數A < 次數B
      - 若次數相同：回傳 ASCII_A > ASCII_B
   e. 遍歷 v，輸出 ASCII 值 與 頻率
   f. 將 first_case 設為 false
END
```

## 5. 錯誤程式碼 vs 正確程式碼


### 錯誤程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int cnt = 0;
    while(getline(cin, s) && s != ""){
        if(cnt > 0) cout << "\n";
        cnt ++;

        map<char, int> mp;
        for(int i=0; i<s.length(); ++i){
            mp[s[i]] ++;
        }

        vector<pair<char, int>> v(mp.begin(), mp.end());
        sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b){
            if(a.second != b.second){
                return a.second < b.second;
            }
            else{
                return a.first > b.first;
            }
        });

        for (pair<char, int> i : v) {
            cout << (int)i.first << " " << i.second << "\n";
        }
    }
}
```

**錯誤原因**

- 終止條件是檔案結束 (EOF)。在某些測試資料中，中間可能出現空行，若使用 s != ""，程式會提前結束，導致後面的資料沒被讀取

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int cnt = 0;
    while(getline(cin, s)){
        if(cnt > 0) cout << "\n";
        cnt ++;

        map<char, int> mp;
        for(int i=0; i<s.length(); ++i){
            mp[s[i]] ++;
        }

        vector<pair<char, int>> v(mp.begin(), mp.end());
        sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b){
            if(a.second != b.second){
                return a.second < b.second;
            }
            else{
                return a.first > b.first;
            }
        });

        for (pair<char, int> i : v) {
            cout << (int)i.first << " " << i.second << "\n";
        }
    }
}
```

**可運作原因**

- 會持續讀取直到輸入串流關閉，不論字串內容為何，都能完整處理所有資料


## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 讀取邏輯 | 遇到空字串即停止 | 直到檔案結束 (EOF) 才停止 |
| 空行處理 | 有處理，但可能因提前停止而漏掉資料 | 正確地在測試案例之間插入空行 |
| 排序準則 | 雙重條件排序正確 | 雙重條件排序正確 |

### 反思

- 讀取字串時常會習慣性加上 s != "" 來避開換行符，但在這題這反而成了障礙
- 學到了自定義排序的方法


