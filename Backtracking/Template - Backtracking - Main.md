---
ParentTask:
  - "[[backtracking]]"
---

# Problem
[Title](URL)

# 模板與不變量
- 選擇 → 遞迴 → 撤銷（choose → recurse → unchoose）
- 去重策略：排序 + if(i>start && nums[i]==nums[i-1]) continue
- 訪問標記：原地標記 + 回溯還原

# Answer（模板）
## V1 - DFS（遞迴）
```Cpp
class Solution {
public:
    // TODO: 回溯骨架，參數含路徑、索引、剩餘容量/長度等
};
```

## V2 - 迭代/優化（若適用）
- 與 V1 差異：狀態壓縮/位運算/剪枝
```Cpp
class Solution {
public:
    // TODO: 優化版本
};
```

# 常錯點
- 忘記還原狀態（visited/路徑）
- 去重條件寫錯、起始索引管理錯誤

# 邊界測資
- 空集合/全重複/無解/單元素

# 複雜度
- 時間：依分支因子與深度估算
- 空間：遞迴深度與路徑儲存

# 二刷差異
- 最有效的剪枝與遞迴順序：