# [LeetCode] [222] - [Count Complete Tree Nodes]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 222
- **題目標題:** Count Complete Tree Nodes
- **題目連結:** [Link to problem](https://leetcode.com/problems/count-complete-tree-nodes/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode222-correct.cpp](./src/s1131408-LeetCode222-correct.cpp)

## 2. 題目說明
給一棵「完全二元樹」的根節點 root，回傳這棵樹的節點總數
- **輸入:** 一棵完全二元樹的根節點 root
- **預期輸出:** 樹的節點總數
- **主要規則或限制**
  1. 節點數量範圍在 $[0, 5 \times 10^4]$ 之間
- **核心任務:** 利用完全二元樹的結構特性，透過計算高度與數學公式算出節點數

## 3. 思考邏輯與解題策略

### 初始想法

- DFS 或 BFS遍歷，走過每一個節點並將計數器加 1
- 沒有利用到題目給的「完全二元樹」特性，且時間複雜度較高

### 最終策略

- 高度判斷，分別算出最左側的深度 leftDepth 與最右側的深度 rightDepth
- 如果 leftDepth == rightDepth，觸發捷徑，直接回傳 (1 << leftDepth) - 1，如果不相等，代表最後一層沒有全滿，需要拆成左右兩棵子樹，遞迴呼叫 countNodes，最後回傳 1 (自己) + 左子樹總數 + 右子樹總數

## 4. 虛擬碼

```text
START
方法 countNodes(root):
    1. 邊界防禦：如果 root 是空節點，回傳 0
    
    2. 計算左極限深度：
       宣告指標 l = root，並持續往左走 (l = l.left)
       計算總共走了幾層，存入 leftDepth
       
    3. 計算右極限深度：
       宣告指標 r = root，並持續往右走 (r = r.right)
       計算總共走了幾層，存入 rightDepth
       
    4. 完美二元樹捷徑判斷：
       如果 leftDepth 等於 rightDepth：
           直接回傳 2 的 leftDepth 次方減 1 (即 1 << leftDepth - 1)
           
    5. 遞迴拆解：
       如果左右深度不同，回傳 1 + countNodes(左子樹) + countNodes(右子樹)
END
```

### 正確程式碼

```cpp
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;

        int leftDepth = 0;
        int rightDepth = 0;
        
        TreeNode* l = root;
        TreeNode* r = root;

        while(l != nullptr){
            leftDepth++;
            l = l->left;
        }

        while(r != nullptr){
            rightDepth++;
            r = r->right;
        }

        if(leftDepth == rightDepth){
            return (1 << leftDepth) - 1; 
        }

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 判斷左右極限深度，相等即套用數學公式 |
| 輸出處理 |  | 善用位元左移運算 (1 << depth) 加速 $2^{\text{深度}}$ 計算 |

### 反思
- 學到了完全二元樹的性質以及它可以直接套用的計算節點公式
- 再遇到跟樹有關的題目能先觀察它的深度，藉由比對左右極限深度，來判斷是否具備特定結構，有些特定結構能夠直接套用數學公式