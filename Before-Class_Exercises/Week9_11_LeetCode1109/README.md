# [LeetCode] [1109] - [Corporate Flight Bookings]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1109
- **題目標題:** Corporate Flight Bookings
- **題目連結:** [Link to problem](https://leetcode.com/problems/corporate-flight-bookings/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1109-correct.cpp](./src/s1131408-LeetCode1109-correct.cpp)

## 2. 題目說明
給一個陣列 bookings，其中 bookings[i] = [first_i, last_i, seats_i] 代表一個預訂紀錄，從航班 first_i 到航班 last_i 每個航班都預訂了 seats_i 個座位
- **輸入:** 一個二維陣列 bookings 代表所有預訂紀錄，以及一個整數 n 代表總航班數量
- **預期輸出:** 長度為 n 的陣列，代表每個航班最終被預訂的總座位數
- **主要規則或限制**
  1. 航班編號是從 1 開始計數
  2. $1 \le n \le 2 \times 10^4$ 且 $1 \le bookings.length \le 2 \times 10^4$
- **核心任務:** 面對大量且重疊的「區間範圍相加」操作時，設計出能快速算出每個節點最終總和的演算法

## 3. 思考邏輯與解題策略

### 初始想法

- 雙層迴圈，外層跑所有預約數量，內層將座位一格一格加上去
- 可能會超時

### 最終策略

- 差分陣列法，不需要紀錄每格的數量，只需要紀錄變化量
- 在起點 i 加上 V 代表從 i 開始，後面的數字相較於前面都多了 V ，在終點的下一格 j + 1 減去 V 代表到了 j + 1 時，前面加的 V 的影響力結束，要扣回來，最後從頭到尾做一次前綴和，就能還原每一格真實的總和

## 4. 虛擬碼

```text
START
1. 宣告一個長度為 n 的陣列 diff，預設全部填 0
2. 遍歷 bookings 中的每一筆預訂紀錄 booking：
   a. 取得真實起點索引 first = booking[0] - 1 (轉為 0-indexed)
   b. 取得真實終點索引 last = booking[1] - 1 (轉為 0-indexed)
   c. 取得座位數 seats = booking[2]
   d. 標記影響力起點：diff[first] 加上 seats
   e. 標記影響力終點：如果 last + 1 沒有超出陣列範圍 (last + 1 < n)：
      - diff[last + 1] 減去 seats
3. 根據變化量還原真實數值 (計算前綴和)：
   - 從索引 i = 1 遍歷到 n - 1：
     - diff[i] = diff[i] + diff[i - 1]
4. 直接回傳 diff
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n, 0);
        
        for(const auto& booking : bookings){
            int first = booking[0] - 1;
            int last = booking[1] - 1;  
            int seats = booking[2];
            
            diff[first] += seats;
            
            if(last + 1 < n) diff[last + 1] -= seats;
        }
        
        for(int i=1; i<n; ++i){
            diff[i] += diff[i - 1];
        }
        return diff;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 只在區間的「頭」與「尾+1」標記變化，最後還原 |
| 邊際情況 |  | 要判斷 last + 1 < n，防止終點剛好在陣列尾巴時發生越界錯誤 |
| 輸出處理 |  | 正確回傳記錄總座位的陣列 |

### 反思
- 學到了前綴和與差分陣列的結合應用
- 題目給的航班是 1-indexed，但 C++ 陣列是 0-indexed，下次只要看到題目給定 1 到 n 的編號，就應該在讀取資料進行 -1 轉換，以避免後續邏輯出現錯誤。