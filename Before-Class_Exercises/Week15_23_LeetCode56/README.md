# [LeetCode] [56] - [Merge Intervals]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 56
- **題目標題:** Merge Intervals
- **題目連結:** [Link to problem](https://leetcode.com/problems/merge-intervals/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode56-correct.cpp](./src/s1131408-LeetCode56-correct.cpp)

## 2. 題目說明
給定一個二維整數陣列 intervals，其中 intervals[i] = [start_i, end_i] 表示一個區間，合併所有重疊的區間，並回傳一個涵蓋輸入中所有區間的「非重疊區間」陣列
- **輸入:** 包含多個區間的二維陣列 intervals
- **預期輸出:** 合併重疊部分後，互不重疊的區間二維陣列
- **主要規則或限制**
  1. $1 \le intervals.length \le 10^4$
  2. $0 \le start_i \le end_i \le 10^4$
  3. 區間的邊緣重疊也算作重疊
- **核心任務:** 找出一種有效率的方式來判斷區間是否交集，並將交集的區間組合成一個涵蓋範圍更大的單一區間

## 3. 思考邏輯與解題策略

### 初始想法
- 使用雙層迴圈，拿出一個區間去和其他所有區間比對，如果有重疊就合併，然後把合併後的新區間再拿去跟剩下的比對
- 這種寫法極度容易導致邏輯錯亂（因為合併後的區間可能又會和之前的區間重疊），且時間複雜度高達 $O(N^2)$，效能極差

### 最終策略
- 處理區間問題的最強起手式就是「排序」。當我們把所有區間依照「起點 (start)」由小到大排序後，會發生重疊的區間必定會「連續」出現在相鄰的位置上
- 首先針對 intervals 進行升冪排序，接著，準備一個空的 result 陣列，並把排序後的第一個區間放進去當作合併的基準。隨後依序遍歷後續的區間 (current)：如果 current 的起點 $\le$ 基準區間的終點，代表兩者重疊，此時基準區間的起點不變，終點則更新為兩者終點的最大值；若不重疊，代表前面的區間已經合併到極限了，直接把 current 塞入 result 中，使其成為下一個新的基準區間

## 4. 虛擬碼

```text
START
方法 merge(intervals):
    1. 邊界防禦：如果 intervals 數量 <= 1，不需要合併，直接回傳 intervals
    
    2. 將 intervals 依照區間的「起點」進行升冪排序
    
    3. 初始化一個二維陣列 result
    4. 將排序後的第一個區間 intervals[0] 推入 result 中
    
    5. 使用迴圈從索引 1 開始遍歷 intervals：
       a. 取出 result 陣列的最後一個元素，作為「當前正在合併的基準 (lastMerged)」
       b. 取得迴圈遍歷到的當前區間 current
       
       c. 判斷是否重疊：
          - 若 current 的起點 <= lastMerged 的終點：
              發生重疊！將 lastMerged 的終點更新為 max(lastMerged 的終點, current 的終點)
          - 否則 (沒有重疊)：
              直接將 current 推入 result 陣列的尾端
              
    6. 回傳 result 陣列
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1) return intervals;

        sort(intervals.begin(), intervals.end());

        vector<vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            vector<int>& lastMerged = result.back();
            vector<int>& current = intervals[i];

            if (current[0] <= lastMerged[1]) lastMerged[1] = max(lastMerged[1], current[1]);
            else result.push_back(current);
        }
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 先靠排序讓重疊區間相鄰，再透過一次線性掃描完成合併 |
| 邊際情況 |  | 開頭直接使用 if (intervals.size() <= 1) 完美防禦 |
| 輸出處理 |  | 開新陣列 result，利用 back() 進行尾端狀態更新，極度高效 |

### 反思
- 這題確立了一個極度重要的演算法樣板——「只要遇到『區間 (Intervals)』重疊的問題，第一步永遠先考慮按起點排序」。包含後續的 Meeting Rooms、Insert Interval 等進階題，全都是基於這個核心思維衍生出來的
- 在重疊合併時，使用 max(lastMerged[1], current[1]) 而非無腦覆寫為 current[1] 是非常嚴謹的防禦。這完美處理了「前一個大區間完全包覆住後一個小區間」的情況，確保終點不會反而變小