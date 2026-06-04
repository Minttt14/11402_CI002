# [LeetCode] [658] - [Find K Closest Elements]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 658
- **題目標題:** Find K Closest Elements
- **題目連結:** [Link to problem](https://leetcode.com/problems/find-k-closest-elements/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode658-correct.cpp](./src/s1131408-LeetCode658-correct.cpp)

## 2. 題目說明
給定一個已排序的整數陣列 arr，以及兩個整數 k 與 x，從陣列中找到距離 x 最近的 k 個元素
- **輸入:** 已排序陣列 arr，要找的數量 k，以及目標基準值 x
- **預期輸出:** 包含 k 個元素的陣列，結果必須也是升冪排序
- **主要規則或限制**
  1.  如果兩者距離相等，數值較小的那個優先被選擇
- **核心任務:** 找到一組長度為 $k$ 的連續子陣列，其內的元素最貼近目標值 $x$

## 3. 思考邏輯與解題策略

### 初始想法

- 寫一個自訂的比較函式，將整個陣列依照對 $x$ 的絕對值距離進行排序，排序後取前 $k$ 個元素，最後再對這 $k$ 個元素重新進行升冪排序
- 時間複雜度高且沒有利用到題目提供陣列已經排序好的條件

### 最終策略

- 利用雙指標不斷往中間縮減，直到找出符合題目需求的子陣列

## 4. 虛擬碼

```text
START
1. 宣告左指標 left = 0，右指標 right = arr 長度 - 1
2. 當目前區間長度 (right - left + 1) > k 時：
   a. 如果 左邊界到 x 的距離 > 右邊界到 x 的距離：
      - 淘汰左邊界 (left++)
   b. 否則 (右邊界更遠，或距離相等但右邊界數值較大)：
      - 淘汰右邊界 (right--)
3. 迴圈結束，剩下的區間 [left, left + k) 即為答案
4. 擷取並回傳該子陣列
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size() - 1;
        
        while(right - left + 1 > k){
            if(x - arr[left] > arr[right] - x){
                left++;
            }
            else right--;  
        }
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 從兩側向內擠壓，略過不需要的點 |
| 邊際情況 |  | 相容各種邊界 |
| 輸出處理 |  | 正確輸出最貼近基準值的子陣列 |

### 反思
- 與其「尋找最好的 $k$ 個」，不如「淘汰最差的 $N - k$ 個」，這種反向思維在處理連續區間或子陣列的問題時，往往能讓邏輯大幅簡化
- 下次遇到類似題目時可以改用二分搜尋法，直接尋找這 $k$ 個連續元素的「起始左邊界」，可以進一步壓縮時間複雜度