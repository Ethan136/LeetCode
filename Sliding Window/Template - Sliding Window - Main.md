# Problem
[Title](URL)

# Window 定義
- 窗口區間定義：左閉右閉 [l, r] 或 (l, r]
- 有效條件（不變量）：何時視為包含所有需求（matchCnt 定義固定其一）
  - 方案 A：matchCnt 代表字元「總數量」是否達標
  - 方案 B：matchCnt 代表「字元種類」是否達標

# Answer（模板）
## V1 - HashMap 實作
```Cpp
class Solution {
public:
    // TODO: s, t 兩側移動骨架：擴張 r -> 滿足 -> while 收縮 l -> 更新答案
};
```

## V2 - 固定長度陣列（256）最佳化
- 與 V1 差異：常數因子更小，避免 map 插入成本
```Cpp
class Solution {
public:
    // TODO: 陣列計數 + matchCnt 驅動
};
```

# 常錯點
- 擴張時機與收縮時機寫反；更新答案的時點
- 無解處理：提前判斷 |s| < |t|
- 陣列大小統一用 256

# 邊界測資
- t 含重複字元、s 無解、s==t、t 為空

# 複雜度
- 時間：O(n)
- 空間：O(1) / O(字元集)

# 二刷差異
- 本題二刷要檢查的條件與錯誤縮減案例：
