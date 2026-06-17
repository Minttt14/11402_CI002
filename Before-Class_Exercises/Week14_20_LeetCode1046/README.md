# [LeetCode] [1046] - [Last Stone Weight]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1046
- **題目標題:** Last Stone Weight
- **題目連結:** [Link to problem](https://leetcode.com/problems/last-stone-weight/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1046-correct.cpp](./src/s1131408-LeetCode1046-correct.cpp)

## 2. 題目說明
給一個代表石頭重量的整數陣列 stones，每次選出兩塊最重的石頭進行粉碎
- **輸入:** 一個整數陣列 stones
- **預期輸出:** 最後剩下一塊石頭的重量，如果沒有石頭剩下則回傳 0
- **主要規則或限制**
  1. 每次選出兩塊最重的石頭 $x$ 和 $y$ (且 $x \le y$)
  2. 若 $x == y$，兩塊石頭皆完全粉碎；若 $x \neq y$，$x$ 被粉碎，$y$ 剩下重量為 $y - x$ 的新石頭，並放回群體中
- **核心任務:** 能夠高效地「反覆找出並移除最大與次大的元素」，並將產生的新元素「重新加入」且維持排序狀態

## 3. 思考邏輯與解題策略

### 初始想法

- 每次粉碎前都使用 sort() 將陣列由大到小排序，取出前兩個相減，如果相減不為 0 再把結果塞回陣列
- 每次 sort() 的時間複雜度是 $O(N \log N)$，若反覆執行 $N$ 次會導致整體時間複雜度來到 $O(N^2 \log N)$，且涉及陣列元素的搬移，效能較差

### 最終策略
- 利用「優先佇列 (Priority Queue / Max-Heap)」，它能在 $O(1)$ 時間取得最大值，並在 $O(\log N)$ 的時間內完成插入與刪除
- 將所有石頭丟入 priority_queue 中，每次迴圈取出並移除兩個最大值，相減後若有剩餘重量，再將差值 push 放回佇列，直到佇列內剩下的石頭數量 $\le 1$ 為止

## 4. 虛擬碼

```text
START
1. 利用 stones 陣列初始化一個最大優先佇列 (Max-Heap) pq
2. 當 pq 的大小大於 1 時，進入迴圈重複執行：
   a. 取出 pq 的最大值存為 a，並將其彈出 (pop)
   b. 取出 pq 的次大值存為 b，並將其彈出 (pop)
   c. 如果 a 不等於 b (代表有殘餘重量)：
      - 將相減的差值 (a - b) 重新推入 (push) pq 中
3. 迴圈結束後，檢查 pq 是否為空：
   - 若為空，代表石頭全部粉碎，回傳 0
   - 若不為空，回傳 pq 中最後剩下的數字 (pq.top())
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {

        priority_queue<int> pq(stones.begin(), stones.end());
        
        while(pq.size() > 1){
            int a = pq.top(); 
            pq.pop();
            
            int b = pq.top(); 
            pq.pop();

            if(a != b) pq.push(a-b);
        }
        return pq.empty() ? 0 : pq.top();
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用 Priority Queue 自動維護最大值 |
| 邊際情況 |  | 利用 pq.empty() ? 0 : pq.top() 防止全數粉碎的空佇列存取 |
| 輸出處理 |  | 三元運算子處理「剩 1 個」與「剩 0 個」的輸出分支 |

### 反思
- 學到了 Priority Queue 的特性與用法
- 只要題目出現「反覆尋找極大值/極小值」，並伴隨著「動態新增/刪除資料」的特徵，第一時間就應該聯想到 Priority Queue
