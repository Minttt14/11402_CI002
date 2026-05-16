# [LeetCode] [31] - [Next Permutation]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 31
- **題目標題:** Next Permutation
- **題目連結:** [Link to problem](https://leetcode.com/problems/next-permutation/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode31-correct.cpp](./src/s1131408-LeetCode31-correct.cpp)

## 2. 題目說明
給定一個整數陣列，將數字重新排列，找出其「字典序」中的下一個，也就是剛好比現在大一點點的排列組合
- **輸入:** 一個整數陣列 nums
- **預期輸出:** 下一個比目前大的陣列
- **主要規則或限制**
  1. 必須是字典序中的下一個排列
  2. 如果當前陣列已經是最大排列，則必須將其重置為最小排列
- **核心任務:** 找到陣列中需要被替換的最高位數，將其替換為剛好大一點的數字，然後將其右側的序列重置為最小狀態

## 3. 思考邏輯與解題策略

### 初始想法

- 窮舉所有排列組合，再找出目前陣列的下一組
- 時間複雜度會高達 $O(N!)$，直接超時

### 最終策略

- 為了讓增加的幅度最小，應該盡量去變動越右邊的數字，從右邊往左看，如果數字逐漸變大，代表這部分已經達到該組合的最大極限，遇到第一個 nums[i] < nums[i+1]，這個 nums[i] 就是必須要換掉的數字
- 為了只大一點點，再次從最右邊往左找，找到第一個大於 nums[i] 的數字 nums[j]，將 nums[i] 與 nums[j] 交換
- 交換後，必須把 i 右邊的所有數字反轉，使其變成遞增（即最小狀態）

## 4. 虛擬碼

```text
START
1. 初始化 i = 陣列長度 - 2
2. 從右向左尋找第一個不滿足遞減的元素 (尋找 Pivot)：
   - 當 i >= 0 且 nums[i] >= nums[i+1] 時：
     - i = i - 1
3. 如果找到了這樣的 i (即 i >= 0，代表不是全陣列遞減)：
   a. 初始化 j = 陣列長度 - 1
   b. 從右向左尋找第一個大於 nums[i] 的元素：
      - 當 j >= 0 且 nums[j] <= nums[i] 時：
        - j = j - 1
   c. 交換 nums[i] 和 nums[j]
4. 反轉 i 之後的所有元素：
   - reverse(從 i+1 到結尾)
END
```

### 正確程式碼

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;    
        while(i >= 0 && nums[i] >= nums[i + 1]){
            i--;
        }
        
        if (i >= 0) {
            int j = n - 1;
            while(j >= 0 && nums[j] <= nums[i]){
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 找升冪、找稍大、交換、反轉 |
| 邊際情況 |  | i 會變為 -1，跳過交換直接反轉成 [1, 2, 3] |
| 輸出處理 |  | 正確輸出下一個排列組合 |

### 反思

- 把陣列切成兩半，右半部是「已經達到極限的遞減後綴」，而我們要找的 Pivot，就是緊貼在這個極限區左邊的那個「還有變大空間的數字」，這種尋找「局部遞減/遞增極限」的思維，在很多高難度的陣列題中都非常受用