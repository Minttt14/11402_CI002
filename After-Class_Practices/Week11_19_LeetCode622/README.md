# [LeetCode] [622] - [Design Circular Queue]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 622
- **題目標題:** Design Circular Queue
- **題目連結:** [Link to problem](https://leetcode.com/problems/design-circular-queue/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode622-correct.cpp](./src/s1131408-LeetCode622-correct.cpp)

## 2. 題目說明
實作一個環狀佇列，它是一種線性資料結構，其操作表現基於 FIFO 原則，且最後一個位置與第一個位置相連，形成一個環狀結構
- **輸入:** 一連串的 API 呼叫，包含建構子 MyCircularQueue(k)，以及 enQueue, deQueue, Front, Rear, isEmpty, isFull
- **預期輸出:** 根據定義回傳布林值或整數
- **主要規則或限制**
  1. 不能使用語言內建的普通 queue 函式庫，必須自己手刻
- **核心任務:** 利用固定大小的陣列，搭配「取餘數 (%)」的技巧，讓指標可以在陣列尾端無縫接軌回到陣列開頭，達成空間的重複利用

## 3. 思考邏輯與解題策略

### 初始想法

- 雙指標法維護 head 和 tail 指標，利用餘數讓它們循環。
- 當 head == tail 時，這代表佇列是「全空」還是「全滿」，傳統解法必須浪費一個陣列空間或是額外增加布林值標記，邏輯非常容易寫錯

### 最終策略

- 不再紀錄 tail 在哪裡，而是單純紀錄「起點 (head)」和「目前有幾個元素 (count)」，所有需要的資訊都能透過這兩個變數推導出來
- isEmpty 是 count == 0， isFull 是 count == capacity， enQueue 是 (head + count) % capacity， Rear 是 (head + count - 1) % capacity ，deQueue 是 head = (head + 1) % capacity，然後 count--

## 4. 虛擬碼

```text
START
類別 MyCircularQueue:
    屬性:
        q (固定大小的陣列)
        head (佇列頭部的索引)
        count (佇列中目前的元素數量)
        capacity (佇列的最大容量)

    建構子 (k):
        將 capacity 設為 k，初始化大小為 k 的陣列 q
        head = 0, count = 0

    方法 isEmpty(): 回傳 count == 0
    方法 isFull(): 回傳 count == capacity

    方法 enQueue(value):
        若 isFull() 為真，回傳 false
        計算目標索引: tailIndex = (head + count) % capacity
        將 value 寫入 q[tailIndex]
        count 增加 1，回傳 true

    方法 deQueue():
        若 isEmpty() 為真，回傳 false
        將頭部指標前進: head = (head + 1) % capacity
        count 減少 1，回傳 true

    方法 Front():
        若 isEmpty() 為真，回傳 -1
        回傳 q[head]

    方法 Rear():
        若 isEmpty() 為真，回傳 -1
        計算尾部索引: tailIndex = (head + count - 1) % capacity
        回傳 q[tailIndex]
END
```

### 正確程式碼

```cpp
class MyCircularQueue {
private:
    vector<int> q;   
    int head;        
    int count;       
    int capacity;    

public:
    MyCircularQueue(int k){
        capacity = k;
        q.assign(k, 0); 
        head = 0;      
        count = 0;     
    }
    
    bool enQueue(int value){
        if (isFull()) return false; 

        int tailIndex = (head + count) % capacity;
        q[tailIndex] = value;
        count++; 
        
        return true;
    }
    
    bool deQueue(){
        if(isEmpty()) return false; 
        
        head = (head + 1) % capacity;
        count--; 
        
        return true;
    }
    
    int Front(){
        if(isEmpty()) return -1;
        return q[head];
    }
    
    int Rear(){
        if(isEmpty()) return -1;
        int tailIndex = (head + count - 1) % capacity;
        return q[tailIndex];
    }
    
    bool isEmpty(){
        return count == 0;
    }
    
    bool isFull(){
        return count == capacity;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 只維護開頭指標與數量，所有位置靠加法與模除推導 |
| 邊際情況 |  | 避開了 head == tail 無法分辨滿或空的問題 |
| 輸出處理 |  | 正確執行各操作 |

### 反思
- 這題讓我到模除運算 % 在設計「環狀資料結構」時的實用性，它能把一條直線的陣列首尾相接模擬出環狀陣列
- 再遇到類似題目需要實作環狀陣列時，仍然可以使用跟這題依樣取模的技巧，避免需要額外撰寫多餘的位置判斷