# [LeetCode] [347] - [Top K Frequent Elements]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 347
- **題目標題:** Top K Frequent Elements
- **題目連結:** [Link to problem](https://leetcode.com/problems/top-k-frequent-elements/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode347-correct.cpp](./src/s1131408-LeetCode347-correct.cpp)

## 2. 題目說明
給定一個整數陣列 nums 和一個整數 k，回傳陣列中出現頻率前 k 高的元素
- **輸入:** 一個整數陣列 nums，與一個目標數量 k
- **預期輸出:** 一個包含 k 個整數的陣列，代表出現頻率最高的前 k 個數字
- **主要規則或限制**
  1. $1 \le nums.length \le 10^5$
  2. $k$ 的範圍在 $[1, \text{陣列中不同元素的總數}]$
- **核心任務:** 統計每個數字出現的次數，篩選出頻率最高的前 K 個數字

## 3. 思考邏輯與解題策略

### 初始想法

- 先用 Hash Map 統計出每個數字的頻率，接著把所有的 (數字, 頻率) 放進一個陣列中，然後針對頻率進行由大到小的排序，最後取出前 K 個
- 邏輯正確，但全排序的時間複雜度為 $O(U \log U)$ (U 為不同元素的數量，最差情況下 U 接近 N)

### 最終策略

- 不需要對「所有」元素進行排序，只要維護一個「容量只有 K 的最小堆積 (Min-Heap)」即可
- 遍歷 nums，用 unordered_map 計算出每個數字的頻率，遍歷 Map，將 {頻率, 數字} 推入 Min-Heap 中，一旦 Heap 的大小超過 k，就把頂端（頻率最低的元素）彈出，將最後留在 Heap 裡面的 K 個元素，抽出放入結果陣列回傳

## 4. 虛擬碼

```text
START
方法 topKFrequent(nums, k):
    1. 初始化一個雜湊表 countMap
    2. 遍歷陣列 nums：
       - 將每個數字的出現次數記錄到 countMap 中
       
    3. 宣告一個最小優先佇列 (Min-Heap) minHeap，用來儲存 {頻率, 數字} 的 pair
    
    4. 遍歷 countMap 中的每一個鍵值對 (key, value)：
       - 將 {value(頻率), key(數字)} 推入 minHeap 中
       - 如果 minHeap 的大小超過了 k：
           - 將 minHeap 頂端 (頻率最小的元素) 彈出 (pop) 淘汰
           
    5. 初始化結果陣列 result
    6. 當 minHeap 不為空時：
       - 將 minHeap 頂端 pair 的第二個元素 (數字) 塞入 result
       - 彈出 minHeap 頂端
       
    7. 回傳 result
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> countMap;
        for(int num : nums){
            countMap[num]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        for(auto& it : countMap){
            minHeap.push({it.second, it.first});
            if (minHeap.size() > k) minHeap.pop(); 
        }
        
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }      
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 建立大小為 K 的 Min-Heap，自動淘汰頻率較低者 |
| 邊際情況 |  | Heap Size 永遠鎖死在 $K$ |
| 輸出處理 |  | 將 Heap 內剩餘元素的 second (數字本身) 抽出即為答案 |

### 反思
- 學到了求 Top K 大/高頻，用 Min-Heap；求 Top K 小/低頻，用 Max-Heap
- 也可以使用桶排序 (Bucket Sort)」，統計完頻率後，建立一個大小為 N + 1 的陣列 buckets，陣列的索引代表頻率，裡面裝的是出現該頻率的數字列表，一個數字最多只可能出現 N 次，所以把數字根據頻率丟進對應的桶子裡，再從陣列尾巴（高頻率）往回掃描，收集數字直到湊滿 K 個為止，這種方法不依賴任何 Heap 或 Sort，直接將時間複雜度降到了 $O(N)$