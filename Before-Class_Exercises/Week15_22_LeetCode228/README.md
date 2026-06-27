# [LeetCode] [228] - [Summary Ranges]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 228
- **題目標題:** Summary Ranges
- **題目連結:** [Link to problem](https://leetcode.com/problems/summary-ranges/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode228-correct.cpp](./src/s1131408-LeetCode228-correct.cpp)

## 2. 題目說明
給定一個無重複元素且已排序的整數陣列 nums。請回傳一個涵蓋陣列中所有數字的最小「有序區間」集合字串陣列，也就是說，若數字是連續的（相差為 1），則合併為一個區間；若數字不連續，則獨立成為一個區間
- **輸入:** 一個已排序的整數陣列 nums
- **預期輸出:** 一個字串陣列，代表合併後的區間
- **主要規則或限制**
  1. $0 \le nums.length \le 20$
  2. $-2^{31} \le nums[i] \le 2^{31} - 1$ 
- **核心任務:** 掃描陣列，辨識出「連續」與「斷層」的邊界，並將對應的範圍轉換為題目要求的字串格式

## 3. 思考邏輯與解題策略

### 初始想法

- 宣告 start 和 end 兩個變數，用一個 for 迴圈遍歷陣列，如果發現當前數字不等於前一個數字加 1，代表出現了「斷層」。這時就把 start 到 end 轉成字串推入結果中，然後更新 start
- 這個寫法在處理「最後一個元素」時非常容易出 Bug，往往需要在 for 迴圈結束後，在外面再補寫一段額外的邏輯來處理最後一段尚未被推入的區間，導致程式碼冗長且易錯

### 最終策略
- 把尋找「連續區間終點」的邏輯，直接包在內層的 while 迴圈裡。只要下一個數字跟當前數字連續，就把外層迴圈的指標 i 往前推進

## 4. 虛擬碼

```text
START
方法 summaryRanges(nums):
    1. 初始化字串陣列 result
    2. 取得陣列大小 n
    
    3. 外層迴圈 i 從 0 走到 n-1：
       a. 記錄目前區間的起點：start = nums[i]
       
       b. 內層迴圈尋找終點 (指標快進)：
          當 (i+1 < n) 且 (nums[i+1] 剛好等於 nums[i] + 1) 時：
              將 i 往前推進 (i++)
              
       c. 離開內層迴圈時，i 已停在目前區間的終點
       d. 判斷區間長度並格式化字串：
          - 如果 start 不等於 nums[i] (區間大於 1)：
            將 "start->nums[i]" 加入 result
          - 如果 start 等於 nums[i] (區間只有 1 個數字)：
            將 "start" 加入 result
            
    4. 回傳 result
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        int n = nums.size();
        
        for (int i=0; i<n; ++i) {
            int start = nums[i];
            
            while (i+1 < n && nums[i + 1] == nums[i] + 1) {
                i++; 
            }
            
            if (start != nums[i]) result.push_back(to_string(start) + "->" + to_string(nums[i]));
            else result.push_back(to_string(start));
        }      
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 主動往後探測，單一 for 迴圈內完美閉環 |
| 邊際情況 |  | 利用 i + 1 < n 完美防禦越界，結尾自然處理完畢 |
| 輸出處理 |  | 統一在 while 結束後進行 if-else 字串處理 |

### 反思
- 「修改外層計數器」的優雅設計： 很多初學者會害怕在 for 迴圈裡面去動計數器 i，但這題完美示範了這項技巧的威力。透過內層 while (i+1 < n) 的探路，直接把 i 送到終點站，這讓時間複雜度依然嚴格保持在 $O(N)$，並且徹底消滅了「迴圈結束後還要處理最後一筆剩餘資料」的常見痛點。
- 短路求值 (Short-Circuit Evaluation) 的重要性： 在 while (i+1 < n && nums[i + 1] == nums[i] + 1) 這行條件判斷中，i+1 < n 必須寫在前面！ 如果前後順序反過來，當 i 走到陣列最後一格時，程式會先執行 nums[i+1] 引發陣列越界崩潰。這是一個非常細節但重要的防禦性編程習慣。