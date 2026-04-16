# [UVa] [10474] - [Where is the Marble?]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10474
- **題目標題:** Where is the Marble?
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10474-correct.cpp](./src/s1131408-UVa10474-correct.cpp)

## 2. 題目說明


- **輸入:** 
- **預期輸出:** 
- **主要規則或限制**
  1. 
  2. 
- **核心任務:** 

## 3. 思考邏輯與解題策略

### 初始想法

- 利用迴圈遍歷所有元素，直到找到或超出範圍
- 遇到大量 query 時效率很低

### 最終策略

- 排序 + lower_bound
- lower_bound 能回傳指向大於或等於目標值的第一個元素的疊代器，符合題目要求找到第一個出現位置的特性

## 4. 虛擬碼

```text
START
1. 初始化 cnt = 1
2. 只要 讀取到 N 與 Q 且兩者不皆為 0：
   a. 讀取 N 個編號存入 vector `marble`
   b. 對 `marble` 進行升序排序
   c. 輸出 "CASE# [cnt]:"
   d. 執行 Q 次詢問：
      i.   讀取目標值 `target`
      ii.  使用 lower_bound 尋找 target 的第一個位置 `it`
      iii. 若 `it` 指向的值剛好等於 `target`：
           - 計算索引 idx = distance(marble.begin(), it) + 1
           - 輸出 "target found at idx"
      iv.  否則：
           - 輸出 "target not found"
   e. cnt 增加 1
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, q;
    int cnt = 1;
    while(cin >> n >> q && (n !=0 || q !=0)){
        vector<int> marble(n);

        for(int i=0; i<n; ++i){
            cin >> marble[i];
        }

        sort(marble.begin(), marble.end());

        cout << "CASE# " << cnt << ":" << "\n";
        cnt++;

        while(q--){
            int target;
            cin >> target;

            auto it = lower_bound(marble.begin(), marble.end(), target);

            if(it != marble.end() && *it == target){
                int idx = distance(marble.begin(), it) + 1;
                cout << target << " found at " << idx << "\n";
            }
            else{
                cout << target << " not found\n";
            }
        }
    }
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用二分搜尋快速縮小範圍 |
| 邊際情況 |  | lower_bound 的特性完美符合找到第一次出現的位置 |
| 輸出處理 |  | 使用 distance 函數處理 Iterator |

### 反思

- lower_bound 找的是第一個 $\ge$ target 的位子，在處理重複數據時非常實用
-  當 $N$ 非常大時，讀取速度會成為瓶頸，可以加上 ios::sync_with_stdio(0); cin.tie(0); 來加速輸入輸出