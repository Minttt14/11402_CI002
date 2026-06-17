# [LeetCode] [703] - [Kth Largest Element in a Stream]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 703
- **題目標題:** Kth Largest Element in a Stream
- **題目連結:** [Link to problem](https://leetcode.com/problems/kth-largest-element-in-a-stream/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode703-correct.cpp](./src/s1131408-LeetCode703-correct.cpp)

## 2. 題目說明
設計一個類別來找到找排序後的第 K 大元素
- **輸入:** 建構子 KthLargest(int k, nums)接收一個整數 k 與一個初始整數陣列 nums
- **預期輸出:** add 函式需回傳第 K 大的整數
- **主要規則或限制**
  1. $1 \le k \le 10^4$
  2. 初始陣列長度可為 0，且題目保證每次呼叫 add 時，資料流中至少有 k 個元素
  3. 最多呼叫 add 達 $10^4$ 次
- **核心任務:** 設計一個能以極低成本動態維護「前 K 大」狀態的資料結構

## 3. 思考邏輯與解題策略

### 初始想法

- 用一個 vector 把所有進來的數字存起來，每次呼叫 add 時，就把新數字放進去，然後呼叫 sort() 降冪排序，最後回傳索引 k-1 的數字
- 每次加入新元素都要排序，時間複雜度為 $O(N \log N)$，當資料流越來越大時會超時

### 最終策略

- 建立一個「只容納 K 個元素的 Min-Heap (最小優先佇列)」，這 K 個元素是資料流中「最大的 K 個數字」，那麼這 K 個數字裡面的「最小值 (也就是堆頂)」，就正好是全域的「第 K 大數字」
- 新數字進來時都推入 Min-Heap 中，如果推入後，Heap 的大小超過了 k，代表有不夠的的數字進來了，此時要把 Heap 頂端給 pop 掉，這樣 Heap 永遠只保留最大的 K 個數字

## 4. 虛擬碼

```text
START
類別 KthLargest:
    屬性:
        k (目標名次)
        minHeap (最小優先佇列，用來儲存前 K 大的元素)

    建構子 (k, nums):
        1. 儲存 k 值
        2. 遍歷初始陣列 nums，對每個數字呼叫 add(num)

    方法 add(val):
        1. 將新進來的 val 推入 (push) minHeap 中
        2. 如果 minHeap 的大小超過了 k (size() > k)：
           - 將 minHeap 頂端的元素 (當前最小的) 彈出 (pop) 丟棄
        3. 回傳 minHeap 的頂端元素 (top)，即為當前的第 K 大數字
END
```

### 正確程式碼

```cpp
class KthLargest {
private:
    int k;
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    KthLargest(int k, vector<int>& nums){
        this->k = k;
        for(int num : nums){
            add(num);
        }
    }
    
    int add(int val){
        minHeap.push(val);
        
        if (minHeap.size() > k) minHeap.pop();

        return minHeap.top();
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 只保留前 K 大的數字，利用堆積動態淘汰不合適的數字 |
| 邊際情況 |  | 容量永遠鎖死在 $K$ |
| 輸出處理 |  | 正確回傳第 K 大元素 |

### 反思
- 學到了求 Top K 大，用 Min-Heap；求 Top K 小，用 Max-Heap 的定律
- 想要再優化可以先手動將 nums 的前 $K$ 個元素放入 vector 中並使用 std::make_heap ($O(K)$)，然後再遍歷剩餘的 $N-K$ 個元素來進行比較與替換