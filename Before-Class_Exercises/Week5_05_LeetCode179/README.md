# [LeetCode] [179] - [Largest Number]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 179
- **題目標題:** Largest Number
- **題目連結:** [Link to problem](https://leetcode.com/problems/largest-number/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode179-correct.cpp](./src/s1131408-LeetCode179-correct.cpp)

## 2. 題目說明
給定一個包含非負整數的陣列 nums，請將這些數字重新排列，使其組合成的數字最大
- **輸入:** 一個非負整數陣列 nums
- **預期輸出:** 能組合出的最大數字
- **主要規則或限制**
  1. 陣列中可能包含多個 0，需要避免回傳 "00" 這種不合法的數字格式
  2. 結果可能非常大，超出整數的範圍，因此必須回傳字串
- **核心任務:** 設計一種排序規則，決定哪一個數字在拼接時應該排在前面

## 3. 思考邏輯與解題策略

### 初始想法

- 降冪排序，數字大的放前面
- 數字大的放前面不一定就能組合出最大輸出

### 最終策略

- 不用去管誰的長度比較長，也不管單獨看誰比較大，直接比較兩種拼接結果
- 如果排序後的第一個字元是 "0"，代表整個陣列中最大的數字就是 0 ，直接回傳 "0"

## 4. 虛擬碼

```text
START
1. 初始化一個字串陣列 s
2. 遍歷 nums 陣列，將所有整數轉為字串並存入 s
3. 對字串陣列 s 進行排序，自訂比較規則：
   - 傳入 a 和 b 兩字串
   - 回傳 (a + b > b + a) 的布林值
4. 排序完成後，檢查 s[0]：
   - 如果 s[0] == "0"，直接回傳 "0"
5. 初始化空字串 result
6. 將 s 中的所有字串依序拼接進 result
7. 回傳 result
END
```

### 正確程式碼

```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> s;
        for(int num : nums){
            s.push_back(to_string(num));
        }
        
        sort(s.begin(), s.end(), [](const string& a, const string& b){
            return a + b > b + a;
        });

        if(s[0] == "0"){
            return "0";
        }

        string result = "";
        for(const string& str : s){
            result += str;
        }
        return result;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 比較 a+b 與 b+a 誰比較大 |
| 邊際情況 |  | 排序後檢查 s[0] == "0" |
| 輸出處理 |  | 使用字串處理，避開了大數溢位問題 |

### 反思

- 排序不一定只能比較單個元素的大小，只要定義的規則滿足「遞移律」，任何自訂邏輯都可以丟進 sort 裡面運作
- a + b > b + a 這個判斷式不僅代碼極短，而且完美避開了所有長短不一數字對齊比較時會遇到的 edge cases
