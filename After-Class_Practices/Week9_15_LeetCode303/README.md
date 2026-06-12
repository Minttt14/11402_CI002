# [LeetCode] [303] - [Range Sum Query - Immutable]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 303
- **題目標題:** Range Sum Query - Immutable
- **題目連結:** [Link to problem](https://leetcode.com/problems/range-sum-query-immutable/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode303-correct.cpp](./src/s1131408-LeetCode303-correct.cpp)

## 2. 題目說明
給一個整數陣列 nums 與索引範圍 [left, right] 計算區間內所有元素的總和（包含 left 與 right）
- **輸入:** 整數陣列 nums 與包含左右區間的 sumRange
- **預期輸出:** sumRange 區間的元素總和
- **主要規則或限制**
  1. sumRange 方法會被呼叫非常多次
  2. nums 陣列的內容一旦給定就不會再改變
- **核心任務:** 實作一個 NumArray 類別，快速計算給定 sumRange 範圍內所有元素的總和

## 3. 思考邏輯與解題策略

### 初始想法

- 直接在 sumRange 中寫 for 迴圈遍歷並加總區間元素的值
- sumRange 被呼叫太多次時可能會超時

### 最終策略

- 前綴和預處理，因為 nums 陣列的內容不會改變，可以在建構子初始化的階段，就先把「從頭加到每個位置的總和」算好並存起來
- 為了避免計算 pre[right] - pre[left-1] 時發生 left = 0 導致的陣列越界錯誤，將 pre 陣列的長度設為 nums.size() + 1，pre[0] 設為 0
- 區間 [left, right] 的總和，只需使用簡單的減法 pre[right + 1] - pre[left] 即可快速算出

## 4. 虛擬碼

```text
START
類別 NumArray:
    屬性: pre (儲存前綴和的陣列)

    建構子 NumArray(nums):
        1. 將 pre 的大小設為 nums.size() + 1，預設全為 0
        2. 遍歷 nums 陣列 (索引 i 從 0 到 nums.size() - 1):
            - pre[i + 1] = pre[i] + nums[i]

    方法 sumRange(left, right):
        1. 直接回傳 pre[right + 1] - pre[left]
END
```

### 正確程式碼

```cpp
class NumArray{
private:
    vector<int> pre;

public:
    NumArray(vector<int>& nums){
        pre.resize(nums.size() + 1, 0);
        
        for(int i=0; i<nums.size(); ++i){
            pre[i + 1] = pre[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right){
        return pre[right + 1] - pre[left];
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 預先算好所有累積總和 |
| 邊際情況 |  | 利用 N+1 長度的陣列避開越界問題 |
| 輸出處理 |  | 正確輸出元素總和 |

### 反思
- 學會了「Padding (填充)」的思想，在處理區間問題時，建立一個大小為 N+1 且第一格為 0 的前綴和陣列，能徹底消滅處理 left - 1 時的各種 IF/ELSE 邊界判斷，使代碼乾淨且不易出錯
- 前綴和的概念能夠延伸到其他的數學或邏輯運算，例如乘法