# [LeetCode] [1022] - [Sum of Root To Leaf Binary Numbers]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 1022
- **題目標題:** Sum of Root To Leaf Binary Numbers
- **題目連結:** [Link to problem](https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode1022-correct.cpp](./src/s1131408-LeetCode1022-correct.cpp)

## 2. 題目說明
給一棵二元樹的根節點 root，這棵樹上每個節點的值皆為 0 或 1，從根節點走到每一個葉節點的路徑，都能構成一串二進位數字，計算所有「根到葉的二進位數字」轉換為十進位後的總和
- **輸入:** 一棵二元樹的根節點 root
- **預期輸出:** 所有從根到葉的路徑構成的二進位數字轉換為十進位後的總和
- **主要規則或限制**
  1. 樹的節點數介於 $1$ 到 $1000$ 之間
  2. Node.val 保證為 0 或 1
  3. 最終答案落在 32-bit 整數的範圍內
- **核心任務:** 透過深度優先搜尋 (DFS)，將每一層的數值往下傳遞，並在每一層將二進位位數「向左推（乘以 2）」，抵達葉節點時即可取得該路徑的整數值並回傳加總

## 3. 思考邏輯與解題策略

### 初始想法

- 建立一個遞迴函數，帶著一個字串往下走，經過的節點如果是 0 就接上 "0"，是 1 就接上 "1"，到達葉節點時，再利用字串轉整數的函式將二進位字串轉成十進位，最後全部加起來
- 遞迴過程中不斷複製和串接字串非常消耗記憶體，效能不佳

### 最終策略

- DFS 狀態下放 + 即時數學計算
- 其實不需要知道完整的字串，在二進位中，每往下走一個位數，就相當於把先前的數字「往左移一位 (乘以 2)」，然後再加上當前的位元值

## 4. 虛擬碼

```text
START
方法 sumRootToLeaf(root):
    回傳 dfs(root, 0) 的執行結果

方法 dfs(node, currentSum):
    1. 邊界防禦：如果 node 是空的 (nullptr)，回傳 0
    
    2. 狀態更新：
       將先前的總和乘以 2，並加上當前節點的值
       currentSum = currentSum * 2 + node.val
       
    3. 判斷葉節點：
       如果 node 的左右子節點都是空的 (代表這是一條路徑的終點)：
           回傳計算好的 currentSum
           
    4. 遞迴分支：
       將更新後的 currentSum 傳給左子節點進行 dfs 計算
       將更新後的 currentSum 傳給右子節點進行 dfs 計算
       回傳 (左子樹總和 + 右子樹總和)
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int sumRootToLeaf(TreeNode* root){
        return dfs(root, 0);
    }

private:
    int dfs(TreeNode* node, int currentSum){
        if (node == nullptr) {
            return 0;
        }
        
        currentSum = currentSum * 2 + node->val; 

        if(node->left == nullptr && node->right == nullptr){
            return currentSum;
        }

        return dfs(node->left, currentSum) + dfs(node->right, currentSum);
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 邊走邊算，利用 * 2 + val 動態更新十進位值 |
| 邊際情況 |  |  left == null && right == null 防止單子樹被重複計算 |
| 輸出處理 |  | 抵達葉節點即是最終數值，直接回傳累加 |

### 反思
- 學到了「Top-Down DFS (由上而下)」的精髓，只要把上層累積的狀態當作參數傳遞給下層，就能把原本需要在終點才做的大型運算，均攤到每一步的 $O(1)$ 數學操作中
- 下次處理二進位數字時，可以直接替換成位元運算 currentSum = (currentSum << 1) | node->val;把數字向左位移一位（等同於乘2），再透過 OR 運算把 0 或 1 鑲嵌進最低位，這能進一步降低 CPU 指令週期的消耗