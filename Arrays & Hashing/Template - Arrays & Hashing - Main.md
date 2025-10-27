---
LeetCodeLv: 
Algorithm:
  - Array
  - Hash
  - String
---

# Problem
[Title](URL)

# Concept
- 核心不變量：
  - （例）頻次表/映射如何維護一致性
  - （例）排序鍵或哈希鍵的正規化（如排序字母、固定長度）
- 模板選型：Array/Hash/Sorting/Counting

# Warning / 常錯點
- map.count(key) 與 map[key] 之差異（[] 可能插入鍵）
- 字串/編碼處理避免反覆 substr/拼接（O(1) 更新）
- 大小寫/非 ASCII/空白字元處理策略

# Answer
## V1 - 直觀解
```Cpp
class Solution {
public:
    // TODO: 實作
};
```

## V2 - 最佳化 / 模板化解
- 與 V1 差異：
  - （例）由 map 改為定長陣列 256
  - （例）自訂 key 正規化避免排序成本
```Cpp
class Solution {
public:
    // TODO: 實作
};
```

# 邊界測資（最小集）
- 空輸入/單元素/全部相同/全部不同
- 超長字串或大數量元素
- 非法/稀有字元（若題意允許）

# 複雜度
- 時間：
- 空間：

# 二刷差異
- 本題二刷時要特別檢查：
- 與相似題的可複用片段：