# [LeetCode] [950] - [Reveal Cards In Increasing Order]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 950
- **題目標題:** Reveal Cards In Increasing Order
- **題目連結:** [Link to problem](https://leetcode.com/problems/reveal-cards-in-increasing-order/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode950-correct.cpp](./src/s1131408-LeetCode950-correct.cpp)

## 2. 題目說明
給一個整數陣列 deck 代表一副牌，將這副牌重新排列，使得依照特定的翻牌規則操作後，被翻開的牌會剛好是升冪的順序
- **輸入:** 未排序的整數陣列 deck
- **預期輸出:** 重新排列後的陣列
- **主要規則或限制**
  1. 翻牌規則包含兩個連續動作，第一步是將最上面的牌翻開並拿走；第二步是如果還有剩餘的牌，將現在最上面的牌移到牌堆的最底下
  2. 持續重複上述兩個動作，直到所有的牌都被翻開
- **核心任務:** 找出牌組的初始順序

## 3. 思考邏輯與解題策略

### 初始想法

- 反向模擬法，最後的結果是從小到大，那就可以從最大的數字反著執行規則，把當前底部的牌移到最上面，然後再把下一個較小的數字放到最上面
- 雖然邏輯正確，但在陣列的頭尾不斷進行插入操作，思維上比較反直覺，容易搞混前進與後退的方向

### 最終策略

- 不需要模擬數字的移動，只需要模擬位置的移動
- 將輸入的 deck 進行升冪排序，然後宣告一個 queue，把代表位置的索引 0 到 n-1 排進去，這個 queue 代表「初始牌堆的位置」，依照題目的規則去操作這個 queue ，將排序好的數字依序填入找出的確切位置，最終的 result 陣列就是答案

## 4. 虛擬碼

```text
START
1. 取得牌組大小 n
2. 將 deck 進行升冪排序 (此為我們期望被翻出的數字順序)
3. 宣告一個佇列 q，將 0 到 n-1 的「索引值」依序推入 q
4. 宣告一個大小為 n 的陣列 result，準備存放還原後的牌組
5. 遍歷排序好的 deck，取出當前最小的數字 num：
   a. 取得 q 的最前端索引，並將該索引從 q 中移除 (模擬翻牌並拿走)
   b. 將 num 放入 result[剛才取得的索引] 中
   c. 防禦性檢查：如果 q 裡面還有元素 (!q.empty())：
      - 將 q 現在的最前端索引，推到 q 的最尾端 (模擬把牌移到最底下)
      - 移除該前端索引
6. 回傳 result
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck){
        int n = deck.size();
        sort(deck.begin(), deck.end());
        
        queue<int> q;
        for(int i=0; i<n; ++i){
            q.push(i);
        }
        
        vector<int> result(n);
        
        for(int num : deck){
            result[q.front()] = num;
            q.pop();
            
            if(!q.empty()){
                q.push(q.front());
                q.pop();
            }
        }
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 不移動實體數字，純粹模擬每個位置何時被翻開 |
| 邊際情況 |  | if(!q.empty()) 避免只剩最後一張牌時的越界問題 |
| 輸出處理 |  | 正確回傳排序過後的陣列 |

### 反思
- 學到了可以利用 Queue 順著題目規則走一遍，就能知道每個位置被翻開的先後順序，接著只要把排序好的數字填進去即可，這比反向推導要直覺非常多