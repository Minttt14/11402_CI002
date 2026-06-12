# [LeetCode] [304] - [Range Sum Query 2D - Immutable]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 304
- **題目標題:** Range Sum Query 2D - Immutable
- **題目連結:** [Link to problem](https://leetcode.com/problems/range-sum-query-2d-immutable/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode304-correct.cpp](./src/s1131408-LeetCode304-correct.cpp)

## 2. 題目說明
給一個二維整數矩陣 matrix，實作一個 NumMatrix 類別，能夠計算給定矩形範圍內的元素總和。矩形由左上角 (row1, col1) 和右下角 (row2, col2) 定義
- **輸入:** 一個二維整數矩陣 matrix 與 sumRegion(row1, col1, row2, col2) 接收左上角與右下角的座標
- **預期輸出:** 該矩形範圍內的元素總和
- **主要規則或限制**
  1. sumRegion 方法會被頻繁呼叫
  2. matrix 的內容一旦給定就不會再改變
- **核心任務:** 實作一個 NumMatrix 類別，快速計算給定矩形範圍內的元素總和

## 3. 思考邏輯與解題策略

### 初始想法

- 在 sumRegion 裡面寫兩個 for 迴圈，把 row1 到 row2、col1 到 col2 範圍內的數字一個一個加起來
- sumRegion 被呼叫太多次時可能會超時

### 最終策略

- 二維前綴和+排容原理，因為 matrix 陣列的內容不會改變，可以在建構子初始化的階段預先算好「從原點 (0,0) 到每個點 (i,j) 所構成的矩形總和」
- 為了避免計算邊界（第 0 列或第 0 行）時發生越界錯誤，我們宣告一個大小為 (m+1) x (n+1) 的前綴和矩陣 pre，第一列與第一行全補 0
- 任意矩形 (row1, col1) 到 (row2, col2) 的總和，可以利用大矩形扣除不要的區塊：
總和 = (涵蓋到右下角的大矩形) - (上半部不要的矩形) - (左半部不要的矩形) + (多扣了一次的左上角重疊矩形)

## 4. 虛擬碼

```text
START
類別 NumMatrix:
    屬性: pre (儲存二維前綴和的矩陣)

    建構子 NumMatrix(matrix):
        1. 邊界檢查：若 matrix 為空，直接回傳
        2. 取得列數 m 與行數 n
        3. 將 pre 陣列大小設為 (m + 1) x (n + 1)，並全填 0
        4. 雙層迴圈遍歷矩陣 (i 從 1 到 m, j 從 1 到 n):
            - 計算目前矩形總和：
              pre[i][j] = 原矩陣值 matrix[i-1][j-1] 
                          + 上方區塊 pre[i-1][j] 
                          + 左方區塊 pre[i][j-1] 
                          - 重疊區塊 pre[i-1][j-1]

    方法 sumRegion(row1, col1, row2, col2):
        1. 利用容斥原理回傳目標區塊總和：
           return pre[row2+1][col2+1] - pre[row1][col2+1] - pre[row2+1][col1] + pre[row1][col1]
END
```

### 正確程式碼

```cpp
class NumMatrix{
private:
    vector<vector<int>> pre;

public:
    NumMatrix(vector<vector<int>>& matrix){
        if (matrix.empty() || matrix[0].empty()) return;
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        pre.assign(m + 1, vector<int>(n + 1, 0));
        
        for(int i=1; i<=m; ++i){
            for(int j=1; j<=n; ++j) {
                pre[i][j] = matrix[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2){
        return pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1] - pre[row2 + 1][col1] + pre[row1][col1];
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用幾何面積的加減法 (排容原理) 快速求值 |
| 邊際情況 |  | 將外圈補 0 避免越界問題 |
| 輸出處理 |  | 正確輸出矩形範圍內的元素總和 |

### 反思
- 這題是非常經典的「排容原理」應用，本質上都在進行「幾何面積的拼湊」，很多看似複雜的二維問題，只要畫個圖把區塊標示出來，公式自然就會浮現
- 這題是 1D 的擴展，之後若遇到要計算 3D 仍然能套用相同邏輯再進行延伸