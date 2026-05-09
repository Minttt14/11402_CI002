# [UVa] [10935] - [Throwing cards away I]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 10935
- **題目標題:** Throwing cards away I
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1876)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa10935-correct.cpp](./src/s1131408-UVa10935-correct.cpp)

## 2. 題目說明
有一疊牌編號為 $1$ 到 $n$，按照 $1$ 在頂端、$n$ 在底部的順序排列，手中還有超過一張的牌時重複執行，將頂端的牌丟棄，將頂端的牌移到底端
- **輸入:** 多個整數 $n$ ($1 \le n \le 50$)，當 $n=0$ 時結束
- **預期輸出:** 丟棄牌的順序與最後剩下的牌編號
- **主要規則或限制**
  1. 如果 $n=1$，就不能繼續丟牌
- **核心任務:** 模擬牌堆的變動並紀錄丟棄順序

## 3. 思考邏輯與解題策略

### 初始想法

- 用陣列來處理
- 要將第二張牌移到尾端很麻煩

### 最終策略

- 使用 queue<int> 模擬牌堆變化
- 丟牌就是出隊，移到後面就是先出隊再重新入隊

## 4. 虛擬碼

```text
START
1. 只要 讀取到的 n 不為 0：
   a. 初始化 queue q，並將 1 到 n 依序存入
   b. 輸出 "Discarded cards:"
   c. 當 q 的長度 > 1 時：
      i.   輸出目前隊首 q.front()
      ii.  將 q.front() 彈出 (丟棄)
      iii. 將現在的隊首 q.front() 加入隊尾 (q.push)
      iv.  再次彈出隊首
      v.   若 q 內還有超過 1 張牌，輸出逗點 ","
   d. 換行
   e. 輸出 "Remaining card: " 以及最後剩下的 q.front()
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    while(cin >> n && n != 0){
        queue<int> q;
        for(int i=1; i<=n; ++i){
            q.push(i);
        }
        
        cout << "Discarded cards:";
        while(q.size() > 1){
            cout << " " << q.front();
            q.pop();
            q.push(q.front());
            q.pop();
            
            if(q.size() > 1) cout << ",";
        }
        cout << "\n";
        if(q.size() == 1) cout << "Remaining card: " << q.front() << "\n";
    }
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 直觀模擬，符合 FIFO 特性 |
| 輸出處理 |  | 利用 q.size() > 1 動態判斷逗點 |

### 反思

- 練習了 queue 的基本操作（push, pop, front, size）
- 這題的 Discarded cards: 後面是否有空格、逗點後的空格，都需要精確對齊。使用 q.size() > 1 可以正確判斷是否印逗點
- 這種「循環處理」的問題，除了佇列，也可以考慮使用 雙向佇列 (Deque) 或 環形鏈表 (Circular Linked List)