# [UVa] [11349] - [Symmetric Matrix]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 11349
- **題目標題:** Symmetric Matrix
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2324)
- **原始程式碼 (失敗):** [src/s1131408-UVa11349-fail.cpp](./src/s1131408-UVa11349-fail.cpp)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa11349-correct.cpp](./src/s1131408-UVa11349-correct.cpp)

## 2. 題目說明
判斷一個 $N \times N$ 矩陣是否為「中心對稱矩陣」
- **輸入:** 
  1. 測試案例數量 T
  2. 每組測資開頭會給定矩陣大小，格式為 N = <size>
  3. 接著是 $N \times N$ 個矩陣元素
- **預期輸出:** 輸出 Test #x: Symmetric. 或 Test #x: Non-symmetric.
- **主要規則或限制**
  1. 矩陣內的元素必須為非負數，小於 0 直接判定為不對稱
  2. 矩陣元素的值可能會超過 32-bit 有號整數 (int) 的上限
- **核心任務:** 檢查矩陣是否包含負數，並且完美對應其中心對稱的座標值

## 3. 思考邏輯與解題策略

### 初始想法

- 將資料存入二維陣列中，邊讀邊檢查是否有小於 0 的數值
- 跑一次雙層迴圈，利用對稱公式判斷頭尾是否相等


### 最終策略

- 如果讀取資料時就發現有負數（check = false），就根本不需要進入對稱比對的迴圈，在對稱比對的迴圈中，只要發現有一組不對稱，就立刻觸發 break，跳出內層迴圈以節省運算時間

## 4. 虛擬碼

```text
START
1. 讀取測試案例數量 T
2. 當 T-- > 0 時執行：
   a. 讀取並忽略前兩個字元/字串，讀取矩陣大小 n
   b. 宣告 long long int 的二維陣列 arr[n][n]
   c. 預設 check = true
   d. 雙層迴圈讀取陣列資料：
      - 若讀到的數字 < 0，則 check = false
   e. 如果 check 仍然為 true：
      - 雙層迴圈比對 arr[i][j] 是否等於 arr[n-1-i][n-1-j]
      - 若不相等，check = false 並 break 跳出
   f. 根據 check 的狀態輸出 Symmetric 或 Non-symmetric
END
```

## 5. 錯誤程式碼 vs 正確程式碼


### 錯誤程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    int cnt = 1;
    while(t--){
        char dump;
        int n;
        cin >> dump >> dump >> n;
        int arr[n][n];
        bool check = true;

        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                cin >> arr[i][j];
                if(arr[i][j] < 0) check = false;  
            }
        }
        
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){

				if (arr[i][j] != arr[n-1-i][n-1-j]) check = false;
			}
        }
    
        if(check){
            cout << "Test #" << cnt << ": Symmetric.\n"; 
        }
        else{
            cout << "Test #" << cnt << ": Non-symmetric.\n" ;
        }  
        cnt ++;
    }
}
```

**錯誤原因**

- 題目測資中會出現大於 $2^{31}-1$ 的正整數，當用 int 存取時，會發生溢位變成「負數」，這會導致程式誤觸 if(arr[i][j] < 0) 的條件，把原本對稱的矩陣誤判為不對稱

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    long long int cnt = 1;
    while(t--){
        char dump;
        int n;
        cin >> dump >> dump >> n;
        long long int arr[n][n];
        bool check = true;

        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                cin >> arr[i][j];
                if(arr[i][j] < 0){
                    check = false;
                }
            }
        }
        
        if(check){
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j)
                if (arr[i][j] != arr[n-1-i][n-1-j]){
                    check = false;
                    break;
                }
            }
        }
    
        if(check){
            cout << "Test #" << cnt << ": Symmetric.\n"; 
        }
        else{
            cout << "Test #" << cnt << ": Non-symmetric.\n" ;
        }  
        cnt ++;
    }
}
```

**可運作原因**

- 改用 64-bit 的 long long int 宣告二維陣列，解決溢位問題


## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 | 一項一項跑完全部流程 | 檢查到不符合的條件時就提早中斷 |
| 邊際情況 | 使用 int，大正數會溢位成負數 | 使用 long long int，包容極端數據 |
| 輸出處理 | 因為前面的溢位問題導致錯誤輸出 | 正確判斷並輸出 |

### 反思

- 若某個測資已經不符合條件時，可以提早退出迴圈或略過不需要再檢查的流程，提升程式效能
- 下次遇到類似題目又拿到 WA 時回頭確認題目給的數值範圍，排除溢位可能性


