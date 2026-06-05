# [LeetCode] [724] - [Find Pivot Index]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 724
- **題目標題:** Find Pivot Index
- **題目連結:** [Link to problem](https://leetcode.com/problems/find-pivot-index/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode724-correct.cpp](./src/s1131408-LeetCode724-correct.cpp)

## 2. 題目說明
給一個整數陣列 nums，計算並回傳該陣列的 Pivot Index ，該索引左側所有數字的總和，剛好等於右側所有數字的總和
- **輸入:** 整數陣列 nums
- **預期輸出:** 最左邊的 Pivot Index ，如果不存在則回傳 -1
- **主要規則或限制**
  1. 如果 Pivot Index 位在陣列的最左邊（索引 0），則其左側總和視為 0，在最右邊的情況同理
  2. 必須回傳最靠近左邊（索引值最小）的 Pivot Index
- **核心任務:** 避免重複計算左右區間的總和，設計一個高效的演算法來找出平衡點

## 3. 思考邏輯與解題策略

### 初始想法

- 雙層迴圈，外層迴圈走訪每一個索引 i，內層迴圈分別去加總 0 到 i-1 的左半部，以及 i+1 到陣列結尾的右半部，兩邊相等就回傳
- 每次移動索引都要重新把剩下的數字加總一次，時間複雜度高，可能導致超時

### 最終策略

- 前綴和，不需要每次都重新計算右邊的總和，因為整個陣列的總和是固定的 totalSum = leftSum + nums[i] + rightSum，經過移項可以得出 rightSum = totalSum - leftSum - nums[i]
- 先跑一次迴圈，算出整個陣列的 totalSum，維護一個 leftSum 變數，初始值為 0 ，再跑一次迴圈遍歷陣列，利用公式算出 rightSum，並檢查 leftSum 是否等於 rightSum ，如果相等，直接回傳 i；如果不相等，就把當前的數字 nums[i] 加進 leftSum 中，供下一個索引使用

## 4. 虛擬碼

```text
START
1. 初始化總和變數 totalSum = 0，左側總和變數 leftSum = 0
2. 遍歷 nums 陣列，將所有數字加總存入 totalSum
3. 使用迴圈遍歷 nums，取得索引 i 與數值 nums[i]：
   a. 計算當下右側總和 rightSum = totalSum - leftSum - nums[i]
   b. 如果 leftSum 等於 rightSum：
      - 找到最左側的樞紐索引，直接回傳 i
   c. 將當前數值 nums[i] 加入 leftSum，為下一輪做準備
4. 迴圈結束代表找不到平衡點，回傳 -1
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& nums){
        int totalSum = 0;
        int leftSum = 0;
        
        for(int num : nums){
            totalSum += num;
        }
        
        for(int i=0; i <nums.size(); ++i){
            int rightSum = totalSum - leftSum - nums[i];
            
            if (leftSum == rightSum) return i;
            
            leftSum += nums[i];
        }
        return -1;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 先算總和，利用減法推導右側 |
| 邊際情況 |  | 索引 0 時 leftSum 預設為 0，公式依舊成立 |
| 輸出處理 |  | 正確輸出索引值或例外狀況 |

### 反思
- 學到了寫程式不只是邏輯控制，有時候簡單的數學公式就能大幅提升程式效能，同時，滾動更新狀態（動態維護 leftSum）的技巧非常實用，能省去大量的重複計算
- 下次題目只要出現「連續子陣列總和」、「左右區間平衡」這類關鍵字時，就應該想到用前綴和來解題