# [LeetCode] [435] - [Non-overlapping Intervals]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 435
- **題目標題:** Non-overlapping Intervals
- **題目連結:** [Link to problem](https://leetcode.com/problems/non-overlapping-intervals/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode435-correct.cpp](./src/s1131408-LeetCode435-correct.cpp)

## 2. 題目說明
給定一個區間陣列 intervals ，其中 intervals[i] = [start_i, end_i]，找出需要移除的「最少區間數量」，使得剩下的區間互不重疊
- **輸入:** 包含多個區間的二維整數陣列 intervals
- **預期輸出:** 為了消滅所有重疊，最少需要刪除的區間「數量」
- **主要規則或限制**
  1. $1 \le intervals.length \le 10^5$
  2. $-5 \times 10^4 \le start_i < end_i \le 5 \times 10^4$
  3. 區間的邊緣相碰（例如 [1, 2] 和 [2, 3]）不算重疊
- **核心任務:** 在所有發生衝突的區間中，做出最佳的「取捨」，決定要移除哪一個區間，才能讓後面的區間有最大的存活空間

## 3. 思考邏輯與解題策略

### 初始想法

- 針對每一個區間，都考慮「保留」或「刪除」兩種狀態，窮舉出所有可能讓剩下區間不重疊的組合，最後選出刪除數量最少的那一組
- 每個區間有 2 種選擇，時間複雜度高達 $O(2^N)$。在 $10^5$ 的測資大小下，絕對會超時

### 最終策略

- 把區間按起點排序後，重疊的區間必然會相鄰。當發現兩個區間重疊時，必須丟掉其中一個。為了讓後續的區間盡可能「不被卡住」，應該貪心地保留「終點較小（較早結束）」的那個區間，因為它能留給後方區間的可用空間最大
- 先利用 sort 預設對所有區間的「起點」進行升冪排序，並用一個變數 prevEnd 記錄前一個區間的終點。接著使用單一迴圈從第二個區間開始掃描，如果發現當前區間的起點 $\ge$ prevEnd，代表沒有重疊，將 prevEnd 更新為當前區間的終點；反之，若起點 $<$ prevEnd，代表發生重疊，必須移除一個區間，此時將移除了計數器加 1，並且嚴格執行貪心策略——將 prevEnd 更新為兩者終點的「最小值」min(prevEnd, currentEnd)，代表捨棄了佔用太多空間的區間

## 4. 虛擬碼

```text
START
方法 eraseOverlapIntervals(intervals):
    1. 邊界防禦：如果 intervals 為空，直接回傳 0
    
    2. 將 intervals 依照區間的「起點」進行升冪排序
    
    3. 初始化計數器 removeCount = 0 (紀錄要刪除的數量)
    4. 初始化指標 prevEnd = intervals[0][1] (紀錄目前安全區間的終點)
    
    5. 使用迴圈 i 從 1 遍歷到陣列結尾：
       a. 取得當前區間的 currentStart 與 currentEnd
       
       b. 判斷是否重疊：
          - 若 currentStart >= prevEnd (無重疊)：
              更新指標 prevEnd = currentEnd
          - 否則 (發生重疊)：
              必須刪除一個區間，removeCount 增加 1
              貪心選擇：保留較早結束的區間，更新 prevEnd = min(prevEnd, currentEnd)
              
    6. 回傳 removeCount
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        sort(intervals.begin(), intervals.end());
        
        int removeCount = 0;       
        int prevEnd = intervals[0][1]; 
        
        for (int i = 1; i < intervals.size(); i++) {
            int currentStart = intervals[i][0];
            int currentEnd = intervals[i][1];
            
            if (currentStart >= prevEnd)  prevEnd = currentEnd;
            else {
                removeCount++;
                prevEnd = min(prevEnd, currentEnd);
            }
        } 
        return removeCount;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 重疊時，貪心保留「終點最早」的區間以騰出空間 |
| 邊際情況 |  | 開頭 intervals.empty() 提早防禦空陣列導致的越界 |
| 輸出處理 |  | 只更新 removeCount 與 prevEnd，極致高效 |

### 反思
- 當兩個區間發生衝突時，與其糾結「要刪掉誰」，不如反向思考「我要留下誰」。留下「終點最早結束」的區間，代表能為未來的區間騰出最大的生存空間。這種「為未來保留最大彈性」的思維，是解決這類排程問題（Scheduling Problem）最核心的靈魂
- 題的貪心策略其實還有另一種經典寫法：「直接以『終點』進行升冪排序」。如果一開始就以終點排序，每次只要找「起點大於等於前一個終點」的區間直接保留即可，連 min() 都不用比，邏輯會更加直覺