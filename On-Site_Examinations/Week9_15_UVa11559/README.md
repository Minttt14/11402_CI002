# [UVa] [11559] - [Event Planning]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 11559
- **題目標題:** Event Planning
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2595)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa11559-correct.cpp](./src/s1131408-UVa11559-correct.cpp)

## 2. 題目說明
需要在預算內找到最便宜的飯店，每間飯店在不同週數提供的剩餘床位不同
- **輸入:** $N$ (人數), $B$ (總預算), $H$ (飯店數量), $W$ (週數)，接著是 $H$ 組資料，每組包含飯店的每人房價與 $W$ 個數字（代表每週剩餘床位）
- **預期輸出:** 如果在預算內且床位充足時輸出最便宜的總花費，否則輸出 stay home
- **主要規則或限制**
  1. 飯店必須在至少其中一週有足夠容納 $N$ 個人的床位
  2. 總花費不得超過總預算 $B$
- **核心任務:** 遍歷所有飯店，在符合床位條件的飯店中找出最低的總花費

## 3. 思考邏輯與解題策略

### 初始想法

- 想要將所有資料都先存進陣列中最後再作比較
- 需要寫很多次迴圈，增加不必要的操作

### 最終策略

- 即時過濾與更新，每讀一間就比較一次，讓程式碼更簡潔
- 初始化一個比預算還大的 minCost，只要算出的 total 比 minCost 小且在預算 $B$ 內，就更新它

## 4. 虛擬碼

```text
START
1. 當 讀取到 N, B, H, W 時：
   a. 初始化 minCost = B + 1 (代表尚未找到可用方案)
   b. 執行 H 次循環 (飯店遍歷)：
      i.   讀取該飯店價格 price
      ii.  初始化 stay = false (這家店能不能住)
      iii. 執行 W 次循環 (週數遍歷)：
           - 讀取該週床位 bed
           - 如果 bed >= N，將 stay 設為 true
      iv.  如果 stay 為 true：
           - 計算 total = N * price
           - 如果 total <= B 且 total < minCost：
             - 更新 minCost = total
   c. 如果 minCost 仍大於 B：
      - 輸出 "stay home"
   d. 否則：
      - 輸出 minCost
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, B, H, W;
    
    while (cin >> N >> B >> H >> W) {
        int minCost = B + 1;

        for (int i = 0; i < H; ++i) {
            int price;
            cin >> price;
            
            bool stay = false;
            for (int j = 0; j < W; ++j) {
                int bed;
                cin >> bed;
                if (bed >= N) {
                    stay = true;
                }
            }

            if (stay) {
                int total = N * price;
                if (total <= B) {
                    minCost = min(minCost, total);
                }
            }
        }

        if (minCost <= B) {
            cout << minCost << endl;
        } else {
            cout << "stay home" << endl;
        }
    }
    return 0;
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 即時判斷，每讀一家店就處理完畢，節省記憶體 |
| 邊際情況 |  | 使用 total <= B 正確處理花費與預算剛好相同的情況 |
| 輸出處理 |  | 只維護一個最優解 minCost，邏輯單純 |

### 反思

- 練習到如何處理多重過濾條件，在此題中 minCost = B + 1 是一個很好的技巧，它既能當作初始值，又能作為最後判斷是否有飯店合格的依據
- 這題讓我注意到「輸入流」的完整性。即使已經確定這間飯店不合格，還是必須完整地讀完該飯店的所有週數資料，否則下一組飯店的數據會讀錯