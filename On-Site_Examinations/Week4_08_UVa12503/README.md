# [UVa] [12503] - [Robot Instructions]

## 1. 題目資訊

- **平台:** UVa
- **題目編號:** 12503
- **題目標題:** Robot Instructions
- **題目連結:** [Link to problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=441&page=show_problem&problem=3947)
- **原始程式碼 (失敗):** [src/s1131408-UVa12503-fail.cpp](./src/s1131408-UVa12503-fail.cpp)
- **原始程式碼 (正確/通過):** [src/s1131408-UVa12503-correct.cpp](./src/s1131408-UVa12503-correct.cpp)

## 2. 題目說明

模擬機器人在直線上的移動過程，從座標 $0$ 出發，完成一連串指令後輸出它的最終位置
- **輸入:** 第一行為測資數量 $T$ ，第二行為每組測資的指令數 $n$，接著是 $n$ 行指令、指令包含 LEFT、RIGHT 或 SAME AS i
- **預期輸出:** 執行完所有指令後，機器人的最終位置（起始位置為 0）
- **主要規則或限制**
  1. LEFT: 位置 $-1$
  2. RIGHT: 位置 $+1$
  3. SAME AS i: 執行與第 $i$ 步完全相同的指令
- **核心任務:** 需要一個陣列來儲存每一步實際的移動量，以便後續 SAME AS 指令調用

## 3. 思考邏輯與解題策略

### 初始想法

- 只要遇到 LEFT 就減 1，RIGHT 就加 1
- 一開始不知道如何抓取SAME AS 後面的數字

### 最終策略

- 使用一個陣列儲存每一步的移動，方便回溯之前的指令
- 把無用的AS用dump讀取掉再去抓取實際需要的指令數字

## 4. 虛擬碼

```text
START
1. 讀取測試案例數 t
2. 當 t-- > 0:
   a. 初始化 record 陣列與位置 cnt = 0
   b. 讀取指令數 n
   c. 迴圈 i 從 1 到 n:
      i.   讀取字串 instruction
      ii.  若 instruction 是 "LEFT": record[i] = -1, cnt = cnt - 1
      iii. 若 instruction 是 "RIGHT": record[i] = 1, cnt = cnt + 1
      iv.  若 instruction 是 "SAME":
           - 讀取掉多餘字串 "AS"
           - 讀取目標編號 num
           - record[i] = record[num] (繼承該步移動)
           - cnt = cnt + record[i]
   d. 輸出最終 cnt 值
END
```

## 5. 錯誤程式碼 vs 正確程式碼


### 錯誤程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int record[] = {0};
        int n;
        int cnt = 0;
        cin >> n;
        string instruction, dump;
        int num;

        for(int i=1; i<=n; ++i){
            cin >> instruction;
            if(instruction[0] == 'R'){
                record[i] = 1;
                cnt ++;
            }
            else if(instruction[0] == 'L'){
                record[i] = -1;
                cnt --;
            }
            else{
                cin >> dump >> num;
                cnt += record[num];
            }
        }
        cout << cnt << "\n";
    }
}
```

**錯誤原因**

- 記憶體溢位: int record[] = {0} 只宣告了一個長度為 1 的陣列，程式執行 record[i] = 1 且 $i > 0$ 時會造成記憶體存取錯誤
- 在執行 SAME AS num 時，沒有將該步的移動量存入當前的 record[i]，後續指令出現 SAME AS i (而 $i$ 本身就是一個 SAME 指令)，就會抓不到正確的移動值

### 正確程式碼

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int record[120] = {0};
        int n;
        int cnt = 0;
        cin >> n;
        string instruction, dump;
        int num;

        for(int i=1; i<=n; ++i){
            cin >> instruction;
            if(instruction[0] == 'R'){
                record[i] = 1;
                cnt ++;
            }
            else if(instruction[0] == 'L'){
                record[i] = -1;
                cnt --;
            }
            else{
                cin >> dump >> num;
                record[i] = record[num];
                cnt += record[i];
            }
        }
        cout << cnt << "\n";
    }
}
```

**可運作原因**

- 正確初始化陣列大小，確保比題目最大的指令數100還大
- 每一步不論是原始指令還是 SAME AS，都將最終位移存入 record[i]，確保了指令的「連鎖參考」邏輯正確


## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 | SAME AS 時只取值不存值，無法處理連鎖的 SAME AS | 將參考的指令值存入當前紀錄，支援多層參考 |
| 邊際情況 | record[] = {0} 空間不足 | record[120] 預留足夠指令空間 |
| 輸出處理 | 抓取第一步移動正確，但後續參考會出錯 | 每步皆有紀錄，確保輸出正確 |

### 反思

- 宣告陣列時沒有正確輸入，且在模擬過程中忽略了當前指令也可能被未來引用的可能性
- 之後宣告陣列大小應根據題目限制來設定
- 下次再遇到要處理「參考先前狀態」的題目時，要確實把每一次的狀態都儲存


