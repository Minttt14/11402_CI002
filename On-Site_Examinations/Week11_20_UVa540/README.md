# [UVa] [540] - [Team Queue]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 540
- **題目標題:** Team Queue
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=481)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa540-correct.cpp](./src/s1131408-UVa540-correct.cpp)

## 2. 題目說明
這是一個特殊的排隊系統，參與者被分成若干個小組
- **輸入:** 
  1. 小組數量 $t$，以及每個小組包含的成員編號
  2. 一系列指令：ENQUEUE x（x 進入隊伍）、DEQUEUE（隊首離開）、STOP（本案結束）
- **預期輸出:** 每個 DEQUEUE 指令對應的成員編號，並標註 Scenario #x
- **主要規則或限制**
  1. 當一個人 ENQUEUE 時，如果隊伍中已經有他的小組成員，他會直接排到該小組最後一個成員的後面
  2. 如果隊伍中沒有他的小組成員，他要排到整個大隊伍的最後面
  3. 永遠是整個大隊伍的最前面的人離開
- **核心任務:** 實作一種能快速定位「小組位置」並支援「組內插入」的資料結構

## 3. 思考邏輯與解題策略

### 初始想法

- 使用 vector ，當 ENQUEUE 時，從後往前找隊友，找到後在該位置後方插入
- 陣列或串列中頻繁尋找與移動，面對大量數據時可能會超時

### 最終策略

- 實作佇列的佇列
- main 佇列儲存目前正在排隊的小組編號，決定了小組與小組之間的先後順序；team[ID] 佇列陣列為每個小組準備一個獨立的佇列，儲存該小組內正在排隊的成員編號
- mp 用來快速查詢某個成員屬於哪一個小組
## 4. 虛擬碼

```text
START
1. 初始化 case_cnt = 1
2. 當 讀取到小組數 t 且 t != 0：
   a. 建立成員對小組的映射表 (Map: Person -> TeamID)
   b. 建立一個 main 佇列 (存 TeamID)
   c. 建立一個佇列陣列 teams_q[1000] (存成員)
   d. 進入指令循環：
      - 若指令為 "ENQUEUE x"：
        - 取得 x 的組別 ID
        - 若 teams_q[ID] 為空：將 ID 推入 main
        - 將 x 推入 teams_q[ID]
      - 若指令為 "DEQUEUE"：
        - 取得 main 隊首的組別 ID
        - 輸出並彈出 teams_q[ID] 的隊首
        - 若 teams_q[ID] 變為空：將 ID 從 main 彈出
      - 若指令為 "STOP"：跳出循環
   e. 輸出空行分隔 Scenario
END
```

### 正確程式碼

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    int cnt = 1;
    while(cin >> t && t != 0){
        cout << "Scenario #" << cnt << "\n";
        cnt ++;
        
        map<int, int> mp;
        for(int i=1; i<=t; ++i){
            int num;
            cin >> num;
            for(int j=0; j<num; ++j){
                int person;
                cin >> person;
                mp[person] = i;
            }
        }
        queue<int> main;
        queue<int> team[1100];
        
        string cmd;
        while(cin >> cmd && cmd != "STOP"){
            if(cmd == "ENQUEUE"){
                int newPerson;
                cin >> newPerson;
                int teamId = mp[newPerson];
                
                if(team[teamId].empty()) main.push(teamId);
                team[teamId].push(newPerson);
            }
            else if(cmd == "DEQUEUE"){
                int frontTeam = main.front();
                cout << team[frontTeam].front() << "\n";
                
                team[frontTeam].pop();
                
                if(team[frontTeam].empty()) main.pop();
            }
        }
        cout << "\n";
    }
}
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 模組化管理，小組有序，組內也有序 |
| 效率 |  | $O(N)$ENQUEUE 與 DEQUEUE 皆為 $O(1)$ |
| 空間處理 |  | 需維護多個佇列，但邏輯清晰 |

### 反思

- 有時候單一容器無法解決問題時，將多個 queue 組合起來（大隊排小隊）能產生強大的效果
- 雖然 map 很方便，但如果成員編號範圍已知且不大，改用陣列做映射表速度會更快
