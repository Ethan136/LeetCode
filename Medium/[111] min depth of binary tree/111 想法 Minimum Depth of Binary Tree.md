### 返回總覽
[[OverallView - Tree]]

-----

### 注意
1. 第一層 node -> depth = 1
2. 每個node的left和right都要檢查一次
3. 檢查完left和right之後，取 min( nLeftDepth , nRightDepth )
4. 取完左右兩邊的min之後，該層深度爲 1 + （左 or 右 深度較小的）
5. 陷阱
	```
		如果 Node->left = null，Node->right != null
		這時候 nLeftDepth = 0，但『實際上左邊根本不能算是有分支』
		兩邊取min的時候會取到左邊的 depth = 0
		即： min( nLeftDepth , nRightDepth ) = 0
	```

-----

### 原則
1. 最小題目分隔
	* 一個 Node 計算『從他開始的深度』
2. 依照Node連接情況來決定後續步驟
	* 連結左邊：return 1 + 左Node深度
	* 連接右邊：return 1 + 右Node深度
	* 連接兩邊：return 左Node深度 + 右Node深度
	* 兩邊不接：returen 1
3. 遇到分叉：
	* 要是真的分叉，不能其中一邊是 null（原因在【注意項目5】）
	* 檢查『左』
	* 檢查『右』
	* 兩邊取max
4. 更新機制
	* 初始條件：min depth = INT_MAX
	* 當『目前的depth 較小』，則更新 min depth

-----

### 方法
#### 方法1：Iteration
1. 初始條件
	* Depth = INT_MAX
	* current depth = 0
1. 從『top node開始』一路往下搜索
	* current depth ++
	* 遇到分叉：把『右邊的Node + 當下深度』記錄到Stack，然後繼續搜索左邊
	* 遇到End：從『stack 取出前一個分叉』重新搜索
		* 回溯 current depth
		* 繼續向下搜索

-----

#### 方法2：Recursive
1. 檢查第一個 Node
	* Null -> 回傳 0
	* 存在 -> 進行 recursive
2. Recursive 函式
	* 定義：當下Node的深度
	* 爲了明確定義Recursive的行爲 + 減少 if 判斷
		* Recursive涵式『預設輸入的node 不爲 null』
		* 並且不檢查 Node == null 的情況
		* null ptr 要在『第一次呼叫』前進行判斷
3. 利用『Recursive 呼叫』進行『向下搜索』
	* 終止條件：node 爲 end point -> return 當下Node的 depth = 1
	* 向下搜索：return 當下Node 的 depth = 1 + Recurvise呼叫
		* 只有左邊連結：return 1 + Recursive( LeftNode )
		* 只有右邊連結：return 1 + Recursive( RightNode )
		* 兩邊邊連結：return 1 + min( Recursive( LeftNode ), Recursive( RightNode ) )
