# [LeetCode] [1700] - [Number of Students Unable to Eat Lunch]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1700
- **題目標題:** Number of Students Unable to Eat Lunch
- **題目連結:** [Link to problem](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1700-correct.cpp](./src/s1131408-LeetCode1700-correct.cpp)

## 2. 題目說明
有兩種三明治種類，學生會排成一列隊伍，輪流拿取最上層的三明治，若學生喜歡目前的三明治就拿走並離開隊伍；學生不喜歡目前的三明治則重新回隊伍末端，重複此過程直到沒有任何學生喜歡最上層的三明治為止
- **輸入:** 兩個整數陣列 students (代表學生的偏好佇列) 與 sandwiches (代表三明治的堆疊)
- **預期輸出:** 無法吃到午餐的學生人數
- **主要規則或限制**
  1. 陣列長度 1 <= students.length, sandwiches.length <= 100
  2. 陣列內的數字只會是 0 或 1
- **核心任務:** 模擬排隊取餐的過程，並判斷出何時該停止

## 3. 思考邏輯與解題策略

### 初始想法

- 用一個 while 迴圈配合 queue 模擬，只要前端學生與三明治不匹配，就 pop 出來再 push 到尾端；匹配就移除該學生與三明治
- 如果沒有學生想吃最上層三明治了，學生依然會重複排隊，進入無窮迴圈

### 最終策略

- 使用 queue 模擬並搭配計數器模擬
- 為了知道是不是剩下的所有人都不吃這個三明治，設定一個計數器 dislike 計算「連續被拒絕的次數」，當 dislike 的數量剛好等於總人數 q.size()時即可打破迴圈，回傳佇列剩下的人數

## 4. 虛擬碼

```text
START
1. 宣告一個佇列 q，並將 students 陣列中的所有學生依序推入 q
2. 初始化三明治指標 sandwichIdx = 0，連續拒絕計數器 dislike = 0
3. 當 q 不為空，且連續拒絕次數小於當前佇列人數 (dislike < q.size()) 時，執行迴圈：
   a. 取出佇列最前面的學生 current = q.front()，並將其從佇列移除 (q.pop())
   b. 如果學生喜歡當前最上面的三明治 (current == sandwiches[sandwichIdx])：
      - 三明治被拿走，指標往下移 (sandwichIdx++)
      - 局勢改變，連續拒絕計數器歸零 (dislike = 0)
   c. 否則 (學生不喜歡)：
      - 學生走到佇列尾端重新排隊 (q.push(current))
      - 連續拒絕計數器加一 (dislike++)
4. 迴圈結束 (代表全拿完或發生死結)，回傳佇列剩下的總人數 q.size()
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches){
        queue<int> q;
        for(int i : students){
            q.push(i);
        }
        
        int sandwichIdx = 0;
        int dislike = 0; 
        
        while(!q.empty() && dislike < q.size()){
            int current = q.front();
            q.pop();

            if(current == sandwiches[sandwichIdx]){
                sandwichIdx++;  
                dislike = 0; 
            } 
            else{
                q.push(current);
                dislike++;      
            }
        }
        return q.size();
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 利用 queue 模擬隊伍並搭配計數器偵測 |
| 邊際情況 |  | dislike < q.size() 作為跳出條件 |
| 輸出處理 |  | 正確回傳學生陣列剩餘的人數 |

### 反思
- 遇到這種模擬排隊先進先出的題型時，優先想到可以用 queue 來實作，因為它具有FIFO 的特性
- 其實這題學生排隊順序並不重要，不需要真的使用 queue 來模擬，能夠直接觀察題目將解法改為簡單的數學統計，因此下次再遇到類似題目時可以不用急著下手，觀察題目的規律有時候能大幅精簡程式碼