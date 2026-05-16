# [LeetCode] [121] - [Best Time to Buy and Sell Stock]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 121
- **題目標題:** Best Time to Buy and Sell Stock
- **題目連結:** [Link to problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode121-correct.cpp](./src/s1131408-LeetCode121-correct.cpp)

## 2. 題目說明
給定一個陣列 prices，其中 prices[i] 代表某支股票在第 i 天的價格，只能選擇某一天買入，並在未來的某一天賣出，藉此獲取最大利潤
- **輸入:** 一個整數陣列 prices
- **預期輸出:** 能獲取的最大利潤，若無法獲利則回傳 0
- **主要規則或限制**
  1. 必須先買後賣
  2. 最多只能進行一次交易
- **核心任務:** 找出陣列中兩個元素的最大差值 prices[j] - prices[i]，且必須滿足 $j > i$

## 3. 思考邏輯與解題策略

### 初始想法

- 使用雙層迴圈，外層選定買入的日期，內層遍歷之後所有可能的賣出日期，計算所有組合的利潤並找出最大值
- 時間複雜度為 $O(N^2)$ ，測資太多時會超時

### 最終策略

- 準備兩個變數，minPrice 記錄到目前為止看過的最低股價；maxProfit 記錄目前能賺取的最大利潤
- 遍歷每一天的價格。如果今天的價格比 minPrice 還低，就更新 minPrice ，如果今天的價格沒有破新低，嘗試計算今天賣出的利潤是多少，並看這個利潤是否能刷新 maxProfit

## 4. 虛擬碼

```text
START
1. 初始化 minPrice = 無限大 (INT_MAX)
2. 初始化 maxProfit = 0
3. 遍歷 prices 陣列中的每一天價格 price：
   a. 如果 price < minPrice：
      - 找到了更便宜的買點，更新 minPrice = price
   b. 否則如果 (price - minPrice) > maxProfit：
      - 今天的價格賣出能賺更多，更新 maxProfit = price - minPrice
4. 迴圈結束後，回傳 maxProfit
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX; 
        int maxProfit = 0;      
        
        for (int i=0; i<prices.size(); i++){

            if(prices[i] < minPrice){
                minPrice = prices[i];
            } 
            else if(prices[i] - minPrice > maxProfit){
                maxProfit = prices[i] - minPrice;
            }
        }
        return maxProfit;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 邊走邊記錄「歷史最低點」並計算當下最大利潤 |
| 邊際情況 |  | maxProfit 初始為 0，一路下跌不會進入 else if，完美回傳 0 |
| 輸出處理 |  | 正確輸出最大利潤 |

### 反思

- 這題讓我理解了「保留有用歷史狀態」的威力，不需要去回頭找以前的每一天，只要記住以前最便宜的那天是多少錢就足夠了
- 未來如果題目變成可以交易一次以上，就能在這個狀態追蹤的基礎上繼續擴充邏輯了