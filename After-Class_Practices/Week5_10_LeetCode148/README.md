# [LeetCode] [148] - [Sort List]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 148
- **題目標題:** Sort List
- **題目連結:** [Link to problem](https://leetcode.com/problems/sort-list/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode148-correct.cpp](./src/s1131408-LeetCode148-correct.cpp)

## 2. 題目說明
給定一個單向鏈結串列的頭節點 head，將其按升冪排序，回傳排序後的鏈結串列
- **輸入:** 一個未排序的鏈結串列的頭節點 head
- **預期輸出:** 排序完成後的鏈結串列頭節點
- **主要規則或限制**
  1. 節點數量範圍介於 $0$ 到 $5 \times 10^4$ 之間
- **核心任務:** 實作一個排序機制來處理鏈結串列的節點

## 3. 思考邏輯與解題策略

### 初始想法

- 想要符合題目進階要求的 $O(1)$ 空間與 $O(N \log N)$ 時間，實作指標操作版的合併排序法
- 操作極度繁瑣，第一次遇到的情況下很容易寫錯

### 最終策略

- 建立一個動態陣列 vector ，將所有節點的值都放入再排序，排序完將新的值覆寫回節點
- 雖然時間複雜度較高，但邏輯簡單且不易出錯

## 4. 虛擬碼

```text
START
1. 邊界檢查：如果 head 是 NULL 或只有一個節點，直接回傳 head
2. 建立一個空的動態陣列 values
3. 設定目前節點 cur = head
4. 迴圈遍歷串列 (提取值)：
   a. 將 cur->val 推入 values 陣列
   b. cur 移動到下一個節點
   c. 直到 cur 為 NULL
5. 使用內建函數對 values 陣列進行升冪排序
6. 重置 cur = head，設定陣列索引 i = 0
7. 迴圈遍歷串列 (覆寫值)：
   a. 將 cur->val 更新為 values[i]
   b. i = i + 1
   c. cur 移動到下一個節點
   d. 直到 cur 為 NULL
8. 回傳 head
END
```

### 正確程式碼

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next){
            return head;
        }
        
        vector<int> values;
        ListNode* cur = head;
        while(cur){
            values.push_back(cur->val);
            cur = cur->next;
        }
        
        sort(values.begin(), values.end());
        
        cur = head;
        int i = 0;
        while(cur){
            cur->val = values[i];
            i++;
            cur = cur->next;
        }
        return head; 
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 不更動鏈結結構，純粹提取數值交給底層高度優化的 sort()，再依序覆寫 |
| 邊際情況 |  | 開頭用 if(!head \|\| !head->next) 完美攔截 |
| 輸出處理 |  | 正確排序各節點的值 |

### 反思

- 若題目強烈要求時間複雜度，會學習使用下而上的迭代版合併排序(Bottom-up Merge Sort)來解題