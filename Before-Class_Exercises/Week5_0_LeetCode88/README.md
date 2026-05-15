# [LeetCode] [88] - [Merge Sorted Array]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 88
- **題目標題:** Merge Sorted Array
- **題目連結:** [Link to problem](https://leetcode.com/problems/merge-sorted-array/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode88-correct.cpp](./src/s1131408-LeetCode88-correct.cpp)

## 2. 題目說明
將兩個已經按非遞減順序(生序排列，可以有相同元素)排序好的整數陣列 nums1 和 nums2 合併成一個單一的排序陣列，並將結果直接儲存在 nums1 中
- **輸入:** 
  1. nums1：長度為 $m + n$ 的陣列，前 $m$ 個元素是有效數字，後 $n$ 個元素為 $0$（預留空間）
  2. m：nums1 中的有效元素數量
  3. nums2：長度為 $n$ 的陣列
  4. n：nums2 中的有效元素數量
- **預期輸出:** 排序好的陣列
- **主要規則或限制**
  1. 不能宣告一個新的陣列來存結果
  2. 利用 nums1 尾部預留的空間
- **核心任務:** 在不覆蓋掉 nums1 原有未排序資料的前提下，將兩陣列的元素按大小依序合併

## 3. 思考邏輯與解題策略

### 初始想法

- 把 nums2 的元素全部塞進 nums1 尾端的 $0$ 裡面，然後直接呼叫 sort(nums1.begin(), nums1.end())
- 沒有利用到「兩個陣列原本就已經排好序」的特性，時間複雜度高達 $O((m+n) \log (m+n))$

### 最終策略

- nums1 的「尾巴」是空的，那我們就從最大的數字（也就是兩個陣列的尾巴）開始比對，把較大的數字從 nums1 的最後面開始往前填
- p1 指向 nums1 有效數字的尾端（$m - 1$）;p2 指向 nums2 的尾端（$n - 1$）;p 指向 nums1 整個陣列的最後一格（$m + n - 1$）
- 只要 nums2 還有數字（p2 >= 0），就繼續比較，如果 nums1 比較大，就放 nums1 的數字；否則放 nums2 的數字

## 4. 虛擬碼

```text
START
1. 初始化三個指標：
   - p1 = m - 1 (nums1 有效區的尾端)
   - p2 = n - 1 (nums2 的尾端)
   - p = m + n - 1 (nums1 實際長度的尾端)
2. 當 p2 >= 0 時執行迴圈 (只要 nums2 還沒搬完就繼續)：
   a. 如果 p1 >= 0 且 nums1[p1] > nums2[p2]：
      - 把 nums1[p1] 放到 nums1[p] 的位置
      - p1 往前移 (p1--)
   b. 否則 (代表 nums2[p2] 較大，或者 nums1 已經搬空了)：
      - 把 nums2[p2] 放到 nums1[p] 的位置
      - p2 往前移 (p2--)
   c. 填入位置往前移 (p--)
END
```

### 正確程式碼

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;         
        int p2 = n - 1;         
        int p = m + n - 1;    
        
        while (p2 >= 0) {
            if(p1 >= 0 && nums1[p1] > nums2[p2]){
                nums1[p] = nums1[p1];
                p1--; 
            }
            else{
                nums1[p] = nums2[p2];
                p2--; 
            }
            p--; 
        }
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用尾部空缺，從最大值開始倒著填 |
| 邊際情況 |  | 判斷 p1 >= 0 完美避開了 m=0 時的越界問題 |
| 輸出處理 |  | 正確依題目規定排序好陣列 |

### 反思

- 很多陣列或字串原地修改（In-place）的問題，只要尾部有足夠空間，逆向遍歷往往就是破局的最佳解
- 這套邏輯可以直接套用到任何「兩個有序數列的合併」場景，只是空間限制不同
