# [LeetCode] [33] - [Search in Rotated Sorted Array]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 33
- **題目標題:** Search in Rotated Sorted Array
- **題目連結:** [Link to problem](https://leetcode.com/problems/search-in-rotated-sorted-array/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode33-correct.cpp](./src/s1131408-LeetCode33-correct.cpp)

## 2. 題目說明
給一個按升冪排序的整數陣列 nums，但在某個樞紐點（Pivot）發生了旋轉，在該陣列中尋找目標值 target
- **輸入:** 經過旋轉的排序陣列 nums，以及一個整數 target
- **預期輸出:** 如果 target 存在於陣列中，回傳其索引值；否則回傳 -1
- **主要規則或限制**
  1. 陣列中的所有元素皆不重複
  2. 時間複雜度為 O(log n)
- **核心任務:** 克服陣列斷層，在每次切半時判斷目標值落在哪一半邊

## 3. 思考邏輯與解題策略

### 初始想法

- 用一個 for 迴圈遍歷陣列找目標值
- 不符合題目要求的 $O(\log n)$ 限制

### 最終策略

- 比較左邊界 nums[left] 與中點 nums[mid] 的大小，判斷哪一半是有排序的，如果是左邊，檢查 target 是否在這個排好序的區間內，有就把搜尋範圍縮小到左半邊（right = mid - 1）；如果沒有，代表 target 一定在充滿斷層的右半邊（left = mid + 1），如果是右邊排好序也同理

- 找到就回傳索引值，否則回傳 -1

## 4. 虛擬碼

```text
START
1. 初始化左指標 left = 0，右指標 right = 陣列長度 - 1
2. 當 left <= right 時執行迴圈：
   a. 計算中點 mid = left + (right - left) / 2
   b. 若 nums[mid] 等於 target，直接回傳 mid
   c. 判斷哪一半邊是連續排序好的：
      - 若 nums[left] <= nums[mid] (代表左半邊完全排序)：
        i. 若 target 落在左半邊的範圍內 (nums[left] <= target < nums[mid])：
           更新 right = mid - 1
        ii. 否則 (target 不在左半邊)：
           更新 left = mid + 1
      - 否則 (代表右半邊完全排序)：
        i. 若 target 落在右半邊的範圍內 (nums[mid] < target <= nums[right])：
           更新 left = mid + 1
        ii. 否則 (target 不在右半邊)：
           更新 right = mid - 1
3. 迴圈結束仍未找到，回傳 -1
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] == target) return mid;
    
            if(nums[left] <= nums[mid]){
    
                if(target >= nums[left] && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
            else{
                if(target > nums[mid] && target <= nums[right]) left = mid + 1; 
                else right = mid - 1; 
                
            }
        }
        return -1;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 找排序好的一半後判斷落點，然後縮小區間 |
| 邊際情況 |  | nums[left] <= nums[mid] 的等號相容陣列長度只剩 2 的狀況 |
| 輸出處理 |  | 正確回傳索引值或例外狀況 |

### 反思
- 學到了二分搜尋不一定要求「整個陣列都是排序好的」，只要能找到一個條件，讓每次切半時都能「100% 確定目標不在其中一半」，就可以大膽地把那一半丟掉
- 遇到類似問題時一樣可以套用此邏輯，再根據不同題型加上對應的限制