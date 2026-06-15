# [LeetCode] [232] - [Implement Queue using Stacks]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 232
- **題目標題:** Implement Queue using Stacks
- **題目連結:** [Link to problem](https://leetcode.com/problems/implement-queue-using-stacks/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode232-correct.cpp](./src/s1131408-LeetCode232-correct.cpp)

## 2. 題目說明
使用兩個 stack 來實作 queue ，實作的 MyQueue 類別必須支援所有標準佇列的操作：push、pop、peek 與 empty
- **輸入:** push、pop、peek 與 empty等操作
- **預期輸出:** pop 與 peek 必須回傳佇列最前方的元素，empty 回傳布林值
- **主要規則或限制**
  1. 只能使用 Stack 的標準操作
- **核心任務:** 使用兩個 stack 來實作 queue

## 3. 思考邏輯與解題策略

### 初始想法

- 每次要 push 新元素時，先把 Stack 1 裡面的東西全部倒進 Stack 2，把新元素放在 Stack 1 最底部，再把 Stack 2 的東西全部倒回來
- 雖然可以保持 Stack 1 永遠是 FIFO 順序，但每次 push 都要把所有元素搬來搬去兩次，效能極差

### 最終策略

- 準備兩個堆疊，一個專門用來處理「寫入 / 輸入 (in)」，另一個專門處理「讀取 / 輸出 (out)」
- push 將元素推入 in 堆疊；執行 pop 或 peek 時，若 out 堆疊為空，則將 in 堆疊的元素全數倒入 out 中，藉此將 LIFO 完美反轉為 FIFO 後再取出最上層最早進入的元素；而當 in 與 out 雙雙為空時，該佇列即為 empty

## 4. 虛擬碼

```text
START
類別 MyQueue:
    屬性: 
        in (輸入堆疊)
        out (輸出堆疊)

    方法 push(x):
        將 x 推入 in 堆疊

    方法 peek():
        如果 out 堆疊是空的：
            當 in 堆疊不是空的：
                把 in 的頂端元素推入 out
                把 in 的頂端元素彈出
        回傳 out 堆疊的頂端元素

    方法 pop():
        利用 peek() 確保 out 堆疊有東西，並取得該值 (val)
        將 out 的頂端元素彈出
        回傳 val

    方法 empty():
        回傳 in 是否為空 且 out 是否為空
END
```

### 正確程式碼

```cpp
class MyQueue{
    stack<int> in, out;

public:
    void push(int x){
        in.push(x);
    }
    
    int pop(){
        int val = peek(); 
        out.pop();
        return val;
    }

    int peek(){
        if(out.empty()){
            while(!in.empty()){
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }
    
    bool empty(){
        return in.empty() && out.empty();
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 延遲搬移，需要讀取且輸出端空了才搬 |
| 邊際情況 |  | 利用 out.empty() 作為邊界觸發條件，只有在輸出堆疊耗盡時才搬移 |
| 輸出處理 |  | pop() 輸出前直接呼叫 peek() 來處理搬移與取值，取回數值後再執行 out.pop() |

### 反思
- 學到了如何根據 stack 固有的特性來實作 queue
- 下次再遇到類似題目，例如用 queue 實作 stack ，能聯想到這題的「雙容器」與「延遲搬移」核心概念，靈活利用輔助空間來強行反轉資料的進出順序