# [UVa] [11292] - [Dragon of Loowater]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 11292
- **題目標題:** Dragon of Loowater
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2267)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa11292-correct.cpp](./src/s1131408-UVa11292-correct.cpp)

## 2. 題目說明
Loowater 王國遭到一隻多頭龍的襲擊。這隻龍有 $n$ 顆頭，每顆頭有特定的直徑。王國裡有 $m$ 位騎士可以被雇用，每位騎士有特定的身高，為了砍下一顆直徑為 $D$ 的龍頭，必須雇用一位身高至少為 $D$ 的騎士，且這位騎士需要收取與他身高相等金幣的酬勞。一位騎士只能砍一顆頭
- **輸入:** 包含多筆測資。每筆測資第一行是兩個整數 $n$ (龍頭數量) 與 $m$ (騎士數量)。接著 $n$ 行是每顆龍頭的直徑，再來 $m$ 行是每位騎士的身高。輸入以 0 0 作為結束標記
- **預期輸出:** 如果能成功砍下所有龍頭，輸出所需花費的「最少金幣總和」。若無法砍下所有頭，則輸出 Loowater is doomed!
- **主要規則或限制**
  1. $1 \le n, m \le 20000$
  2. 每個騎士只能砍一顆頭，不能重複使用
  3. 必須「完全」砍掉所有的龍頭才算成功
- **核心任務:** 找出最划算的分配方式，最小化花費，若無法達成則宣告失敗

## 3. 思考邏輯與解題策略

### 初始想法

- 針對每一顆龍頭，去騎士陣列裡面掃描，尋找「身高大於等於這顆頭」且「最便宜」的騎士來砍，然後把這個騎士標記為已使用
- 每次找騎士都要掃描陣列，時間複雜度高達 $O(n \times m)$。當 $n$ 和 $m$ 達到 $20000$ 時，絕對會超時

### 最終策略

- 為了花最少的錢，我們應該貫徹「殺雞焉用牛刀」的貪心精神——「用能力剛好能砍下頭的最弱騎士去對付每一顆頭」。要有效率地做到這件事，最好的方法就是先把頭和騎士都按照大小排好隊
- 如果騎士總人數少於龍頭總數，絕對無法砍完，直接宣告失敗並跳過後續運算。接著，將龍頭直徑與騎士身高進行升冪排序，讓較小的頭與較弱的騎士排在前面。然後我們使用雙指標法，由小到大同時掃描兩個陣列。如果當前騎士的身高大於等於當前龍頭的直徑，代表他能勝任，我們將他的身高加入總花費，並將龍頭指標與騎士指標同時往後移；如果能力不足，則代表這位騎士連這顆剩餘最小的頭都砍不掉，於是我們直接放棄他，只將騎士指標往後移，尋找下一位騎士。當掃描結束時，只要檢查龍頭指標是否順利走到了最後，就能決定要輸出最小總花費，還是宣告王國毀滅

## 4. 虛擬碼

```text
START
當讀入 n 與 m，且 n 或 m 不為 0 時：
    1. 讀取 n 顆龍頭的直徑存入 heads 陣列
    2. 讀取 m 位騎士的身高存入 knights 陣列
    
    3. 邊界防禦：如果騎士人數小於龍頭數 (m < n)：
       印出 "Loowater is doomed!"，提早進入下一輪測資 (continue)
       
    4. 將 heads 陣列從小到大排序
    5. 將 knights 陣列從小到大排序
    
    6. 初始化雙指標：head_idx = 0, knight_idx = 0，以及花費 cost = 0
    
    7. 當 head_idx < n 且 knight_idx < m 時 (雙指標掃描)：
       - 如果目前騎士能砍下目前龍頭 (knights[knight_idx] >= heads[head_idx])：
           累積花費 cost += knights[knight_idx]
           頭被砍了，head_idx 前進 1 步
       - 不論有無砍下，目前騎士皆已驗證過，knight_idx 前進 1 步
       
    8. 結算判斷：
       - 如果 head_idx 等於 n (代表頭全部砍完)：印出 cost
       - 否則：印出 "Loowater is doomed!"
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;

    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<int> heads(n);
        vector<int> knights(m);

        for (int i = 0; i < n; ++i) {
            cin >> heads[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> knights[i];
        }

        if (m < n) {
            cout << "Loowater is doomed!\n";
            continue;
        }

        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());

        int cost = 0;    
        int head_idx = 0;   
        int knight_idx = 0; 

        while (head_idx < n && knight_idx < m) {

            if (knights[knight_idx] >= heads[head_idx]) {
                cost += knights[knight_idx]; 
                head_idx++;                  
            }
            knight_idx++; 
        }
        if (head_idx == n) cout << cost << "\n";
        else cout << "Loowater is doomed!\n";
    }
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 排序後依序比對，將複雜的尋找化為簡單的推進 |
| 邊際情況 |  | 利用 if (m < n) 在一開始就擋下必輸的局面，大幅提升效能 |
| 輸出處理 |  | 利用結束時的狀態 head_idx == n 判定最終勝負 |

### 反思
- 排序能把無序的資料整理出單調性，是實踐貪心法最關鍵的前置作業。當兩組資料都排序好之後，利用兩個指標同時往前跑，就能在 $O(N)$ 的時間內完成最佳配對，這是演算法解題中最優美且常見的樣板之一
- 在一開始判斷 if (m < n) 是一個極具工程 Sense 的寫法，如果必定失敗，就連「排序」和「雙指標掃描」的效能都省下來了，這在面對極端大量測資的 Competitive Programming 或是系統設計中，是非常重要的防禦機制