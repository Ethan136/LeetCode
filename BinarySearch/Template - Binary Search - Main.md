# Problem
[Title](URL)

# 單調判定與區間定義
- 目標：找第一個/最後一個滿足條件的索引
- 區間：left, right 是否含端點；停止條件
- mid 計算：left + (right-left)/2

# Answer（模板）
## V1 - 找第一個滿足條件的索引
```Cpp
class Solution {
public:
    // bool ok(X): 單調條件判定函數
    // TODO: 二分骨架（偏左收斂）
};
```

## V2 - 特化到本題數學/結構
- 與 V1 差異：條件改寫為單調形式
```Cpp
class Solution {
public:
    // TODO: 問題特化
};
```

# 常錯點
- 無窮迴圈（left/right 更新不對稱）
- 邊界越界、整數溢位
- 多條件判斷未先轉為單調布林

# 邊界測資
- 空/單元素/全部相等/嚴格遞增遞減/目標不存在

# 複雜度
- 時間：O(log n)
- 空間：O(1)

# 二刷差異
- 與 33/153/4 等題的單調化對齊點：