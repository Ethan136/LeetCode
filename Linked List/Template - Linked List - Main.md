# Problem
[Title](URL)

# 常用模板與不變量
- Dummy Head + 三指針（prev/curr/next）
- fast/slow 找中點／環檢測；reverse 區間
- 合併鏈表：穩定性與引用操作順序

# Answer（模板）
## V1 - 指標操作骨架
```Cpp
struct ListNode { int val; ListNode* next; };
class Solution {
public:
    // TODO: 建立 dummy, 初始化 prev/curr/next，按題目需求操作
};
```

## V2 - 優化/分治（若適用）
- 與 V1 差異：如分治合併、就地反轉區間
```Cpp
class Solution {
public:
    // TODO: 優化寫法
};
```

# 常錯點
- 指標更新順序出錯導致遺失鏈
- 忘記連回 dummy 或尾端為 nullptr

# 邊界測資
- 空/單節點/兩節點/全部相等/已排序

# 複雜度
- 時間：
- 空間：

# 二刷差異
- 本題的關鍵步驟順序與易錯點：