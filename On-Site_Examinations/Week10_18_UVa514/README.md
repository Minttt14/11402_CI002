# [UVa] [514] - [Rails]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 514
- **題目標題:** Rails
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=614)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa514-correct.cpp](./src/s1131408-UVa514-correct.cpp)

## 2. 題目說明
火車車廂編號為 $1, 2, \dots, n$，依序進入一個只有單向進出的車站，我們需要判斷火車是否能以指定的編號順序離開車站
- **輸入:** 每組測資開頭為車廂數量 $n$ ，接著是多種車廂排序方法，當 $n=0$ 時結束程式；當，若排列順序第一個數字為 $0$ 時結束該 $n$ 的測試區塊
- **預期輸出:** 若排列可能達成輸出 Yes，否則輸出 No，每組 $n$ 的測試結束後需多印一個換行
- **主要規則或限制**
  1. 車廂進入順序固定為 $1, 2, \dots, n$
  2. 車站內部是一個 「後進先出」(LIFO) 的堆疊結構
- **核心任務:** 模擬進站與出站過程，檢查指定的出站序列是否合法

## 3. 思考邏輯與解題策略

### 初始想法

- 窮舉所有出站可能
- 程式碼工程量會很龐大

### 最終策略

- 使用一個 stack<int> train 代表車站，依序將車廂 $1, 2, \dots, n$ 推入堆疊，每推入一節車廂，就檢查堆疊頂端是否等於目前出站序列所需要的車廂，如果相等，就將該車廂彈出，並將序列索引移向下一個目標，重複檢查直到堆疊為空或頂端不匹配為止
- 因為車廂進入順序是遞增固定的，只要目前車站頂端的車廂是我們需要的，就必須讓它出去，因為之後進來的車廂只會擋住它

## 4. 虛擬碼

```text
START
1. 只要 讀取到的 n 不為 0：
   a. 只要 讀取排列順序的第一個數字 target[0] 不為 0：
      i.   讀取剩餘的排列數字存入 target 陣列
      ii.  初始化 stack<int> train, current_idx = 0
      iii. 對於每一節即將進站的車廂 i (從 1 到 n)：
           - 將 i 推入 train
           - 當 train 不為空 且 train.top() 等於 target[current_idx] 時：
             - 彈出 train.top()
             - current_idx 增加 1
      iv.  若 train 是空的，輸出 "Yes"
      v.   否則輸出 "No"
   b. 輸出一個換行
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n && n!=0){
        while(true){
            vector<int> target(n);
            cin >> target[0];
            if(target[0] == 0){
                cout << "\n";
                break;
            }

            for(int i=1; i<n; ++i){
                cin >> target[i];
            }
            stack<int> train;
            int current = 0;

            for(int i=1; i<=n; ++i){
                train.push(i);

                while(!train.empty() && train.top() == target[current]){
                    train.pop();
                    current ++;
                }
            }
            if(train.empty()) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 正確處理 LIFO 特性 |
| 輸入處理 |  | 正確使用兩層 while 與 break 處理格式 |
| 擴充性 |  | $O(n)$ 的時間複雜度，即使 $n$ 很大也能應付 |

### 反思

- 當問題具有「最後進入的必須先處理」或是「順序受限的進出」特點時，堆疊就是最合適的工具
- 此題輸入格式相對繁瑣（多層 $0$ 結尾），這題練習了如何處理分段輸入
