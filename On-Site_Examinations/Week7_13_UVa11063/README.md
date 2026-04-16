# [UVa] [11063] - [B2-Sequence]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 11063
- **題目標題:** B2-Sequence
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2004)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa11063-correct.cpp](./src/s1131408-UVa11063-correct.cpp)

## 2. 題目說明

判斷一個給定的整數數列是否符合 B2-Sequence 的定義
- **輸入:** 多組測試案例，每組包含數列長度 $N$ 及數列內容 $a_1, a_2, \dots, a_n$
- **預期輸出:** 格式為 Case #x: It is [not] a B2-Sequence.，每組結果後需印一個空行
- **主要規則或限制**
  1. 必須滿足 $1 \le a_1 < a_2 < \dots < a_n$
  2. 所有 $a_i + a_j$ ($i \le j$) 的結果必須是獨一無二的
- **核心任務:** 檢查數列是否嚴格遞增且起始值 $\ge 1$，並檢查所有兩兩之和是否有重複

## 3. 思考邏輯與解題策略

### 初始想法

- 利用雙層迴圈枚舉所有可能的 a[i] + a[j]
- 宣告一個足夠大的陣列存取所有出現的和

### 最終策略

- 讀入資料時，同步檢查 $a[i] \ge 1$ 以及是否滿足嚴格遞增
- 執行雙層迴圈判斷每一次的 a[i] + a[j] 是否出現過

## 4. 虛擬碼

```text
START
1. 初始化 case_count = 1
2. 只要 讀取到長度 n：
   a. 初始化 布林變數 isB2 = true, exist[20001] 清零
   b. 讀取 n 個數字存入陣列 a：
      - 若 a[i] < 1 或 a[i] <= a[i-1]，則 isB2 = false
   c. 若 isB2 仍為 true：
      - 執行雙層迴圈 (i 從 0 到 n-1, j 從 i 到 n-1)：
        - sum = a[i] + a[j]
        - 若 exist[sum] 已被標記：isB2 = false, 跳出迴圈
        - 否則：標記 exist[sum] = 1
   d. 輸出 "Case #[case_count]: " 加上 判斷結果
   e. 輸出一個換行 (空行)
   f. case_count 增加 1
END
```

### 正確程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, cnt = 1;
    while (cin >> n) {
        vector<int> a(n);
        bool B2 = true;
        int exist[20001] = {0};

        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] < 1 || (i > 0 && a[i] <= a[i - 1])) {
                B2 = false;
            }
        }

        if (B2) {
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    int sum = a[i] + a[j];
                    if (exist[sum] == 1) {
                        B2 = false;
                        break;
                    }
                    else exist[sum] = 1;
                }
                if (!B2) break;
            }
        }

        if (B2) cout << "Case #" << cnt << ": It is a B2-Sequence.\n";
        else cout << "Case #" << cnt << ": It is not a B2-Sequence.\n";
        cout << "\n";
        cnt ++;
    }
    return 0;
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 檢查了 $a_i \ge 1$ 、嚴格遞增以及和是否重複出現 |
| 邊際情況 |  | 在輸入資料時就先判斷是否符合大於等於 1 與嚴格遞增 |
| 輸出處理 |  | 有記得多輸出一行空行確保格式符合要求 |

### 反思

- 這題的條件限制比較多，容易漏掉一項就造成錯誤且不易除錯，應該更認真觀察題目給的線索，例如嚴格遞增的排列
- 當 $a_i$ 範圍很大時，標記陣列會失效（空間不足），屆時應改用 set<int> 或 unordered_set