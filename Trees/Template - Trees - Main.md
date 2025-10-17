# Problem
[Title](URL)

# 模板與不變量
- 遞迴設計：返回值語義（本子樹能提供給父節點的資訊 vs. 全域答案）
- Top-down vs Bottom-up 的選擇
- 邊界：nullptr、INT_MIN/INT_MAX 溢位

# Answer（模板）
## V1 - DFS（遞迴）
```Cpp
struct TreeNode { int val; TreeNode* left; TreeNode* right; };
class Solution {
public:
    // TODO: 明確回傳值語義，必要時使用 pair/struct
};
```

## V2 - 迭代/BFS（若適用）
- 與 V1 差異：序列化/層序/顯式 stack/queue
```Cpp
class Solution {
public:
    // TODO: 迭代解
};
```

# 常錯點
- 忘記帶著上下界（BST 題）；未用 long long 對界
- 混淆「可延伸至父」與「僅在本子樹生效」的值

# 邊界測資
- 空樹/單節點/全負/重複值/退化鏈

# 複雜度
- 時間：
- 空間：

# 二刷差異
- 這題與 98/230/124/297 的共通與差異：