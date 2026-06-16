# [LeetCode] [110] - [Balanced Binary Tree]

## 1. 題目資訊

- **平台:** LeetCode
- **題目編號:** 110
- **題目標題:** Balanced Binary Tree
- **題目連結:** [Link to problem](https://leetcode.com/problems/balanced-binary-tree/description/)
- **原始程式碼 (正確/通過):** [src/s1131408-LeetCode110-correct.cpp](./src/s1131408-LeetCode110-correct.cpp)

## 2. 題目說明
給一棵二元樹，判斷它是否為一棵「高度平衡」的二元樹，也就是這棵樹上每一個節點的左子樹與右子樹的高度差，不能超過 1
- **輸入:** 一棵二元樹的根節點 root
- **預期輸出:** 布林值 (true/false)
- **主要規則或限制**
  1. 樹的節點數可能從 0 到 5000
  2. 節點的值不影響判斷，純粹只看「樹的結構與高度」
- **核心任務:** 在計算節點深度的同時，檢查左右子樹的深度差，若發現任何一個節點的左右高度差大於 1，就必須把「不平衡」的信號傳遞回根節點

## 3. 思考邏輯與解題策略

### 初始想法

- 由上而下遞迴，寫一個計算樹高的函數 height(node)，然後在主函數 isBalanced 中，對當前節點計算 height(left) 和 height(right)，如果相差大於 1 就回傳 false，否則繼續遞迴呼叫 isBalanced(left) 和 isBalanced(right)
- 每個節點的高度在往下檢查的過程中會被重複計算，效能非常差

### 最終策略

- 由下而上遞迴，為了消滅重複計算，改用「後序遍歷」的思維
- 定義一個 checkHeight 函數，如果這棵子樹是平衡的，就回傳這棵樹的實際高度；如果這棵子樹不平衡，它就回傳 -1 

## 4. 虛擬碼

```text
START
方法 isBalanced(root):
    回傳 checkHeight(root) != -1

方法 checkHeight(node):
    1. 邊界防禦：如果 node 是空的 (nullptr)，代表高度為 0，回傳 0
    
    2. 檢查左子樹：
       leftHeight = checkHeight(node.left)
       如果 leftHeight 是 -1 (代表左子樹不平衡)，直接提早中斷並回傳 -1
       
    3. 檢查右子樹：
       rightHeight = checkHeight(node.right)
       如果 rightHeight 是 -1 (代表右子樹不平衡)，直接提早中斷並回傳 -1
       
    4. 結算當前節點：
       如果左右子樹高度差的絕對值大於 1 (abs(leftHeight - rightHeight) > 1)：
           代表當前節點不平衡，回傳 -1
           
    5. 皆合法：
       回傳當前節點的高度，即 max(leftHeight, rightHeight) + 1
END
```

### 正確程式碼

```cpp
class Solution {
public:
    bool isBalanced(TreeNode* root){
        return checkHeight(root) != -1;
    }

private:
    int checkHeight(TreeNode* node){
        if(node == nullptr){
            return 0;
        }

        int leftHeight = checkHeight(node->left);
        if (leftHeight == -1) return -1; 

        int rightHeight = checkHeight(node->right);
        if (rightHeight == -1) return -1;

        if(abs(leftHeight - rightHeight) > 1){
            return -1;
        }
        return max(leftHeight, rightHeight) + 1;
    }
};
```

## 6. 差異與反思

### 關鍵差異

| Item | Fail Code | Correct Code |
|---|---|---|
| 邏輯 |  | 先向子節點要資料，再決定自己是否平衡 |
| 邊際情況 |  | 利用 if (leftHeight == -1) 提早中斷 |
| 輸出處理 |  | 利用 -1 重載回傳值 |

### 反思
- 這題展現了樹的「後序遍歷 (Left -> Right -> Root)」在收集底層資訊時的實用性
- 程式碼中 if (leftHeight == -1) return -1; 可以提早中斷，如果左子樹已經不平衡了，右子樹就不需要檢查，這在龐大的樹狀結構中，能省下許多運算時間