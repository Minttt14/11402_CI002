# LeetCode 9 - Palindrome Number

## 問題描述
 判斷一個整數是否為迴文數，負號也需要考慮。[Link to problem](https://leetcode.com/problems/palindrome-number/description/)

## 學習目標
- [ ] 練習將數值型態轉換為字串處理
- [ ] 掌握字串比對邏輯

## 解題方法

### 演算法邏輯
1. 利用to_string()將整數轉換為字串
2. 計算字串長度，並決定迴圈只需走訪一半
3. 比較左側索引 i 與右側對應索引 s.length() - 1 - i 的字元是否相同
4. 不對稱立即回傳 false；若全數相同則回傳 true

### 關鍵見解
- 所有負數在轉字串後，首位字元是 -末位是數字，不可能是迴文
- 轉字串後，不需要考慮翻轉運算時造成的數值溢位問題

## 程式結構
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        string s;
        s = to_string(x);
        for(int i=0; i<s.length()/2; ++i){
            if(s[i] != s[s.length() - 1 - i]){
             return false;
            }
        }
        return true;
    }
};
```
[source code](./src/s1131408-LeetCode9.cpp)

## 複雜度分析
- **時間複雜度:** O($\log_{10} N$)
- **空間複雜度:** O($\log_{10} N$)
  - $N$: 輸入的數值

## 筆記與反思
- 改進方向: 可嘗試只翻轉一半的數字，既能維持 $O(1)$ 的空間複雜度，又能透過只翻轉一半來確保數值永遠不會超過 int 的上限
- 學習心得: 一個問題可能會有多種解法，例如此題可直接依照題目所給的整數去解，也可以轉成字串後再處理，轉成字串時能夠方便處理負數與溢位問題，但較耗費空間，因此可依照不同需求找出最適當的解法

## 參考
- [Problem Link](https://leetcode.com/problemset/)