# [UVa] [299] - [Train Swapping]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 299
- **題目標題:** Train Swapping
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=235)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa299-correct.cpp](./src/s1131408-UVa299-correct.cpp)

## 2. 題目說明

一列火車的車廂編號是亂序的，只能透過交換相鄰兩節車廂的方式來重新排列，目標是將車廂按編號由小到大排好
- **輸入:** 測試案例數 $N$，每個案例包含車廂總數 $L$ 及各車廂的初始編號順序
- **預期輸出:** 格式為 Optimal train swapping takes S swaps.，$S$ 為達成排序所需的最少交換次數
- **主要規則或限制**
  1. 只能交換相鄰的元素
  2. 必須求出最少交換次數
- **核心任務:** 實作泡沫排序並在每次執行交換 (swap) 時累加計數

## 3. 思考邏輯與解題策略

### 初始想法

- 題目要求相鄰交換來排序，聯想到泡沫排序法

### 最終策略

- 採用雙層迴圈的泡沫排序。外層控制掃描次數，內層進行相鄰比對與交換
- 在只能相鄰交換的限制下，泡沫排序的交換次數正好就是數列排好所需的最少次數

## 4. 虛擬碼

```text
START
1. 讀取測試案例數 N
2. 當 N-- > 0:
   a. 讀取車廂長度 L
   b. 讀取 L 個數字存入陣列 arr
   c. 初始化計數器 cnt = 0
   d. 泡沫排序邏輯 (i 從 0 到 L-2):
      i. 內層比對 (j 從 0 到 L-i-2):
         - 若 arr[j] > arr[j+1]:
           - 交換 arr[j] 與 arr[j+1]
           - cnt = cnt + 1
   e. 輸出 "Optimal train swapping takes [cnt] swaps."
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    int L;
    while(N--){
        cin >> L;
        int arr[L];
        for(int i=0; i<L; ++i){
            cin >> arr[i];
        }

        int cnt = 0;
        for(int i = 0; i < L-1; ++i){
            for(int j = 0; j < L-i-1; ++j){
                if(arr[j]>arr[j+1]){
                    swap(arr[j], arr[j+1]);
                    cnt++;
                }
            }
        }
        cout<<"Optimal train swapping takes " << cnt <<" swaps.\n";
    }
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 相鄰交換 |
| 輸出處理 |  | 遵守 Optimal train swapping takes X swaps. 格式 |

### 反思

- 在第一次提交時忽略了輸出最後的句號而錯誤，之後應該更小心檢查題目輸出要求
-  $L$ 增加到 $10^5$，可以使用合併排序的分治法來統計逆序對，將時間複雜度從 $O(N^2)$ 優化到 $O(N \log N)$