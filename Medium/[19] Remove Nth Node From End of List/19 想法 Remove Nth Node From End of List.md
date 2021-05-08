### 類似的題目
1. [[3 想法 Longest Substring Without Repeating]]

### 注意
1. Node 數目有限，上限30

### 原則
1. 要把整個List 記錄起來，再快速找到對應的node把它踢掉

-----

### 方法
#### 方法1：用Array記錄每個node
1. 生成一個 Array，size = node 上限
2. 跑一個迴圈，把所有的 node 記錄起來
3. 最後再直接提出 從後往前數第n個node

-----

#### 方法2：用Window
1. 剔除從後往前第n個Node -> 只會需要記錄n個node
2. 用wubdow做記錄，最後再直接踢掉 window 第一個 node
3. 因爲不像方法1要一直調用 Array Position 做儲存，這個方式速度也很快