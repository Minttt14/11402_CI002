# [LeetCode] [1845] - [Seat Reservation Manager]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1845
- **題目標題:** Seat Reservation Manager
- **題目連結:** [Link to problem](https://leetcode.com/problems/seat-reservation-manager/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1845-correct.cpp](./src/s1131408-LeetCode1845-correct.cpp)

## 2. 題目說明
設計一個管理 $n$ 個座位的系統，座位編號從 $1$ 到 $n$，SeatManager(int n)將所有 $n$ 個座位預設為「可預約」狀態，reserve()取得並回傳當下所有可預約座位中編號最小的座位，並將其狀態設為「已預約」unreserve(int seatNumber)將指定的座位狀態改回「可預約」
- **輸入:** 一連串的 API 呼叫指令
- **預期輸出:** reserve 操作需回傳正確的最小空位號碼
- **主要規則或限制**
  1. $1 \le n \le 10^5$
  2. 總 API 呼叫次數最多為 $10^5$ 次
  3. 保證 unreserve 被呼叫時，該座位一定是處於「已預約」狀態
- **核心任務:** 建立一個能快速尋找「當前可用最小值」且能動態「回收數字」的資料結構

## 3. 思考邏輯與解題策略

### 初始想法

- 初始化時，寫一個 for 迴圈把 $1$ 到 $n$ 全塞進一個 Min-Heap，reserve 就 pop，unreserve 就 push
- 初始化建構 Heap 需要花費 $O(N)$ 的時間與空間，如果 $N$ 很大，但使用者只預約了少數位置，會造成極大的效能浪費

### 最終策略
- 將座位分成兩類「從未被開發過的全新座位」與「被別人退掉的座位」，marker初始化為 1 ，負責發放「全新的座位」，每次發放就遞增， minHeap 專門接收 unreserve 還回來的「二手座位」
- 因為「還回來的二手座位」號碼一定比「尚未開發的全新座位 (marker)」還要小，所以當要 reserve 時，只要 minHeap 裡面有東西，就優先從 Heap 發放最小的；如果 Heap 是空的，才去跟 marker 拿新座位

## 4. 虛擬碼

```text
START
類別 SeatManager:
    屬性:
        marker (整數，紀錄下一個從未被借出的座位)
        minHeap (最小優先佇列，紀錄被歸還的座位)

    建構子 (n):
        1. 初始化 marker = 1
        2. minHeap 保持為空 (不預先塞入任何數字，達成 O(1) 初始化)

    方法 reserve():
        1. 如果 minHeap 不為空 (代表有歸還的較小座位可優先使用)：
           - 取出並移除 minHeap 的最小值 seat
           - 回傳 seat
        2. 如果 minHeap 為空：
           - 拿取全新的座位 seat = marker
           - marker 遞增準備給下一個人 (marker++)
           - 回傳 seat

    方法 unreserve(seatNumber):
        1. 將歸還的座位推入回收池：minHeap.push(seatNumber)
END
```

### 正確程式碼

```cpp
class SeatManager {
private:
    int marker; 
    priority_queue<int, vector<int>, greater<int>> minHeap; 

public:
    SeatManager(int n) marker = 1;
    
    int reserve(){
        if (!minHeap.empty()){
            int seat = minHeap.top();
            minHeap.pop();
            return seat;
        }      
        int seat = marker;
        marker++;
        return seat;
    }
    
    void unreserve(int seatNumber){
        minHeap.push(seatNumber);
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | marker 管理新號碼，Heap 管理被退回的舊號碼 |
| 邊際情況 |  | 防止「極大 $N$ 值卻極少存取」的效能浪費 |
| 輸出處理 |  | 正確執行API 呼叫指令 |

### 反思
- 這題讓我學到「用到再分配」的設計哲學，不需要一開始就為十萬個位子配置記憶體，而是透過一個簡單的 marker 變數來虛擬代表無限的連續資源，這將系統初始化的成本從龐大的 $O(N)$ 直接壓成了 $O(1)$