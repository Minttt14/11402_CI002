# [LeetCode] [641] - [Design Circular Deque]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 641
- **題目標題:** Design Circular Deque
- **題目連結:** [Link to problem](https://leetcode.com/problems/design-circular-deque/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode641-correct.cpp](./src/s1131408-LeetCode641-correct.cpp)

## 2. 題目說明
實作一個「雙向環狀佇列」，它是一種允許在前端與後端都能進行插入與刪除操作的線性資料結構，且底層由環狀陣列組成
- **輸入:** 一連串的 API 呼叫，包含建構子 MyCircularDeque(k)，insertFront、insertLast、deleteFront、deleteLast、getFront、getRear等操作
- **預期輸出:** 根據定義回傳布林值或整數
- **主要規則或限制**
  1. 不能使用內建的 deque 函式庫
- **核心任務:** 在固定的陣列大小內，計算指標在「往前進」與「往後退」時的環狀位移，並防範越界錯誤

## 3. 思考邏輯與解題策略

### 初始想法

- 雙指標法維護 head 和 tail 指標，利用餘數讓它們循環
- 當 head == tail 時，這代表佇列是「全空」還是「全滿」，邏輯非常容易寫錯

### 最終策略

- 只維護 head 和 count，所有尾端的位置都靠 head 加減 count 推導出來
- 當指標需要「往後退一格」時，若單純使用 -1 % capacity，在 C++ 中會得到負數索引導致崩潰，因此必須套用公式：(當前索引 - 移動步數 + capacity) % capacity

## 4. 虛擬碼

```text
START
類別 MyCircularDeque:
    屬性: q (陣列), head (頭指標), count (元素數量), capacity (最大容量)

    建構子 (k): 初始化 capacity = k, q 大小為 k, head = 0, count = 0

    方法 insertFront(value):
        若滿了回傳 false
        將 head 往後退一格 (繞回尾端)：head = (head - 1 + capacity) % capacity
        寫入 q[head] = value，count++，回傳 true

    方法 insertLast(value):
        若滿了回傳 false
        計算目前的尾端下一格：tailIndex = (head + count) % capacity
        寫入 q[tailIndex] = value，count++，回傳 true

    方法 deleteFront():
        若空了回傳 false
        將 head 往前推進一格：head = (head + 1) % capacity
        count--，回傳 true

    方法 deleteLast():
        若空了回傳 false
        直接將 count-- (邏輯刪除，捨棄尾端元素)
        回傳 true

    方法 getFront():
        若空了回傳 -1，否則回傳 q[head]

    方法 getRear():
        若空了回傳 -1
        計算當前尾端位置 (注意負數防禦)：tailIndex = (head + count - 1 + capacity) % capacity
        回傳 q[tailIndex]
END
```

### 正確程式碼

```cpp
class MyCircularDeque {
private:
    vector<int> q; 
    int head;        
    int count;       
    int capacity;    

public:
    MyCircularDeque(int k) {
        capacity = k;
        q.assign(k, 0);
        head = 0;
        count = 0;
    }
    
    bool insertFront(int value){
        if(isFull()) return false;
        
        head = (head - 1 + capacity) % capacity;
        q[head] = value;
        count++; 
        
        return true;
    }
    
    bool insertLast(int value){
        if (isFull()) return false;
        
        int tailIndex = (head + count) % capacity;
        q[tailIndex] = value;
        count++; 
        
        return true;
    }

    bool deleteFront(){
        if(isEmpty()) return false;
        
        head = (head + 1) % capacity;
        count--;
        
        return true;
    }

    bool deleteLast(){
        if(isEmpty()) return false;

        count--; 
        
        return true;
    }

    int getFront(){
        if(isEmpty()) return -1;
        return q[head];
    }

    int getRear(){
        if(isEmpty()) return -1;

        int tailIndex = (head + count - 1 + capacity) % capacity;
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
| 邏輯 |  | 只維護開頭指標與數量，位置靠數學運算推導 |
| 邊際情況 |  | 避開了 head == tail 無法分辨滿或空的問題 |
| 輸出處理 |  | 正確執行各操作 |

### 反思
- 在 insertFront (head = (head - 1 + capacity) % capacity) 以及 getRear 中，我學到了防禦負數取餘數的技巧。，只要掌握了底層數學的偏移量原理，再複雜的雙向環狀移動也能用簡短的程式碼解決
- 未來遇到類似的「滑動視窗」或是「雙端佇列求區間極值」等進階演算法題，我會選擇 Deque 作為底層容器，因為它的底層運作穩定且效能極高