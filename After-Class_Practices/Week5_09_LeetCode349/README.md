# [LeetCode] [349] - [Intersection of Two Arrays]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 349
- **題目標題:** Intersection of Two Arrays
- **題目連結:** [Link to problem](https://leetcode.com/problems/intersection-of-two-arrays/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode349-correct.cpp](./src/s1131408-LeetCode349-correct.cpp)

## 2. 題目說明
給定兩個整數陣列 nums1 和 nums2，回傳它們的交集
- **輸入:** 兩個整數陣列 nums1 和 nums2
- **預期輸出:** 兩個陣列交集元素的陣列
- **主要規則或限制**
  1. 輸出結果中的每個元素都必須是唯一的，不能重複
  2. 輸出結果的順序不限
- **核心任務:** 比對兩個陣列，找出共同擁有的數字，並確保結果不具重複數字

## 3. 思考邏輯與解題策略

### 初始想法

- 用雙層迴圈遍歷，拿 nums1 的每一個數字，去 nums2 裡面從頭到尾掃描一遍看有沒有出現過
- 過於耗時

### 最終策略

- 利用具有自動去除重複功能的 unordered_set
- 讓陣列 2 與已經處理好的陣列 1 做比較，若找的到就推入結果中

## 4. 虛擬碼

```text
START
1. 利用 nums1 初始化一個雜湊集合 set1 (這會自動去除 nums1 的重複元素)
2. 建立一個空的結果陣列 result
3. 遍歷 nums2 中的每一個元素 n：
   a. 如果 n 存在於 set1 中 (set1.count(n) > 0)：
      i.   將 n 加入 result 陣列
      ii.  將 n 從 set1 中刪除 (防止 nums2 裡重複的 n 被重複加入 result)
4. 回傳 result
END
```

### 正確程式碼

```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end());
        vector<int> result;
        
        for(int n : nums2){
            if(set1.count(n)){
                result.push_back(n);
                set1.erase(n);
            }
        }
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用 Hash Set 快速查詢 |
| 邊際情況 |  | set.erase() 完美避開重複加入 |
| 輸出處理 |  | 正確輸出不重複的交集元素 |

### 反思

- unordered_set 在「尋找是否存在」與「確保唯一性」時非常實用
- 若遇到類似題目可基於目前用法再擴充邏輯