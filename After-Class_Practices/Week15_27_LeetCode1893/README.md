# [LeetCode] [1893] - [Check if All the Integers in a Range Are Covered]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1893
- **題目標題:** Check if All the Integers in a Range Are Covered
- **題目連結:** [Link to problem](https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1893-correct.cpp](./src/s1131408-LeetCode1893-correct.cpp)

## 2. 題目說明
給定一個二維整數陣列 ranges 以及兩個整數 left 和 right。ranges[i] = [start_i, end_i] 代表一個包含起點與終點的閉區間，判斷在目標區間 [left, right] 內的「每一個整數」是否都被 ranges 中的至少一個區間所涵蓋
- **輸入:** 一個包含多個區間的陣列 ranges，與目標檢查範圍的起點 left 和終點 right
- **預期輸出:** 布林值 (true 代表全覆蓋，false 代表有數字遺漏)
- **主要規則或限制**
  1. $1 \le ranges.length \le 50$
  2. $1 \le start_i \le end_i \le 50$
  3. $1 \le left \le right \le 50$
- **核心任務:** 驗證給定範圍內的每一個數字，是否都能在任意一個提供的小區間內找到歸屬

## 3. 思考邏輯與解題策略

### 初始想法

- 先將所有 ranges 排序並合併成幾個不重疊的大區間，接著再檢查 [left, right] 是否完全落在其中一個合併後的大區間之內
- 實作較為繁瑣，需要考慮排序 $O(M \log M)$ 及多種區間重疊的邊界情況

### 最終策略

- 目標數字最多只有 50 個，且區間最多也只有 50 個，我們完全可以直接把 left 到 right 之間的每一個數字拿出來，逐一去問所有的區間：「你們有人能罩我嗎？」只要有一個數字沒人罩，就立刻宣告失敗
- 使用外層迴圈遍歷從 left 到 right 的每一個整數 i。在每次迴圈開頭，先立一個旗標 isCovered = false。接著開啟內層迴圈遍歷所有的 ranges，一旦發現 i 剛好落在某個區間內 (i >= range[0] && i <= range[1])，就將旗標改為 true 並立刻 break 跳出內層迴圈。如果內層迴圈結束後，旗標依然是 false，代表這個數字 i 成了漏網之魚，馬上回傳 false 提早結束整個程式。若所有數字都順利通過，最後回傳 true

## 4. 虛擬碼

```text
START
方法 isCovered(ranges, left, right):
    外層迴圈 i 從 left 走到 right (檢查每個目標數字)：
        1. 預設當前數字未被涵蓋：isCovered = false
        
        2. 內層迴圈遍歷 ranges 中的每一個區間 range：
           - 如果 i 落在 range 內 (i >= range[0] 且 i <= range[1])：
               代表找到了涵蓋該數字的區間
               將 isCovered 設為 true
               跳出內層迴圈 (break)，不需再檢查其他區間
               
        3. 檢查涵蓋狀態：
           - 如果 isCovered 還是 false (代表掃遍所有區間都沒人罩這個數字)：
               立刻回傳 false (提早中斷)
               
    所有數字都檢查完畢且無遺漏，回傳 true
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        for (int i = left; i <= right; i++) {
            bool isCovered = false; 
            
            for (auto& range : ranges) {
                if (i >= range[0] && i <= range[1]) {
                    isCovered = true; 
                    break;            
                }
            }

            if (!isCovered) return false;       
        }
        return true;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 針對目標範圍內的每個數字，逐一確認歸屬 |
| 邊際情況 |  | 利用 !isCovered 攔截遺漏 |
| 輸出處理 |  | 利用雙重迴圈的 break 與 return 實現提早中斷 |

### 反思
- 在解題或實務開發時，第一步永遠是「觀察測資範圍限制」。這題因為資料量極小 ($N, M \le 50$)，採用直觀的暴力破解反而擁有了最短的開發時間、最乾淨的程式碼與最低的 Bug 發生率
- 如果再遇到類似題目，但目標數字極大，可以改用差分陣列的思路來實作