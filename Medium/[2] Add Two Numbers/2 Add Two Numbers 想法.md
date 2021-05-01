### 機制整理
1. List: 1-3-4-5-6 -> number: 65431
2. List: 0 -> number: 0
3. 一定是正數 or 0
4. 輸出的資料也要是list

-----

### 概念彙整
1. 掃描的時候，同一個 node index，對應的位數一樣
	* 1-2-3-4-5 -> 54321
	* 1-2-3 -> 321
	* 上述兩個數列的123有相同node index，對應的位數一樣

2. 每次掃描就可以做疊加

-----

### 規劃
#### 生成一個新的 List
1. 生成一個新的 Node
	1. 兩個list 同時掃描
	2. 每次掃描到一個node，對應的數字 = node value * 10^(node index)
	3. 做數值疊加
2. 當其中一個掃到NULL，他就停止掃描
3. 當兩個都是NULL，回傳結果

-----

#### 把第二個List 的 node，疊加到第一個List，回傳第一個List作爲結果

##### 要點
1. 第一個list用完的時候 -> 把第二個list剩餘的node接到第一個list
2. 接着如果第一個list還是用完了 -> 代表掃描完了

##### 方法1：state machine
1. 初始 state 掃兩個 list
2. 遇到特殊情況就切換 state
3. 最後會跑到一個只掃一個 list 的 state

-----

##### 方法2：依序掃描
1. 先掃兩個 list，其中一個掃完，就break loop
2. 檢查是否掃完
3. 再掃剩餘的 list，掃完就 return