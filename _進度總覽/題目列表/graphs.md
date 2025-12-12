---
LeetCodeSeq: 11
LeetCode150Finish: 13
LeetCode150Num: 13
LeetCode150TestPass: 13
LeetCode150ConceptOk: 13
LeetCode150Review: 13
LeetCode150Rev2: 13
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage|NeetCode 150 MainPage]]"
---
### Concepts
#### 2D Graph Grid
##### Overview： 2D Graph Grid Traverse Recursive DFS 主架構
- TraverseDFS( grid, row, col )
	- 檢查 row / col 是否 valid -> invalid position early return (或是 return false)
	- 檢查 grid\[row\]\[col\] 裡面的數值是否為『traversable』或是『traverse marked』 -> 是的話 early return
	- 當前 grid 標記為 traversed：可以額外一個 Array 記錄，也可以直接標記在 grid 上面
	- for Loop：當前 grid 往上下左右四個方向 traverse
		- `int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} }`
		- TraverseDFS( grid, row + dir\[i\][0], col + dir\[i\][1])

##### 2D Graph 每一格檢查，某種類型格子走過的地方標記起來
- 模板
	- for( each row idx)
		- for( each col idx )
			- TraverseDFS(grid, row, col)
- 題目
	- [[200. Number of Islands - Main]]
	- [[695. Max Area of Island - Main]]
	- [[79. Word Search - Main]]

##### 2D Graph 邊緣擴散到中間：每一格檢查，但有『邊界擴散到中間的意味在』 
- 模板
	- 走上下邊界: for( each col idx) -> 和邊界相連的資訊記錄 + mark special
		- TraverseDFS(grid, 1stRow, col)
		- TraverseDFS(grid, lastRow, col)
	- 走左右邊界: for( each row idx) -> 和邊界相連的資訊記錄 + mark special
		- TraverseDFS(grid, row, 1stCol)
		- TraverseDFS(grid, row, lastCol)
	- 走 Overall
		- for( each row idx )
			- for( each col idx)
				- 統計資訊 or 調整 mark
					- grid\[row\]\[col\] = mark special -> 有和邊界相連
					- other -> 原始的情況
- 題目
	- [[130. Surrounded Regions - Main]]
	- [[417. Pacific Atlantic Water Flow - Main]]

##### 2D Graph 中間擴散到旁邊：每一格檢查，如果是特殊格子，則往旁邊擴散
- 模板
	- TraverseDFS( prevStep, grid, row, col )
		- **執行擴散： grid 記錄Special Point 擴散過來的最短步數**
		- （1）如果當前 grid 無法行走 -> early return
		- （2）如果當前 grid 的步數 = prevStep -> early return
			- **不能走的 grid 要把 step 要記錄為負數**
			- **special start point grid 要記錄為 0**
		- （3）更新當前 grid 的步數 = prevStep + 1
		- （4）traverse 四周的 grid: TraverseDFS( curStep, grid, row + dir_i[0], col + dir_i[1])
	- 主結構
		- PreCondition -> **為了讓整體行走更方便**
			- 把 start point 設定為 0
			- 把 not-pass point 設定為 -1
			- 把 traversable point 設定為 INT_MAX（要是一個超出 grid 最大可能數值的數字）
		- Traverse & Mark Step
			- for( each row idx )
				- for( each col idx )
					- 當前的 grid 不是 start point -> 跳過這個 grid
					- 當前的 grid 是 start point -> 執行 TraverseDFS
						- **prevStep 選擇一個特別數字，讓 TraverseDFS 可以成功踩到 special grid 上面**
						- **如果是最短擴散距離： 通常可以選 (special grid value - 1) **
		- Post Process
			- 檢查所有 grid，看是否有 grid 沒被擴散 -> 檢查 grid = 一開始設定的超出邊界最大值 -> 代表無法擴散完全
			- 檢查所有 grid，記錄最久的擴散時間
- 題目
	- [[994. Rotting Oranges - Main]] - 使用 pre condition
	- [[286. Walls & Gates - Main]] - 不使用 pre condition

#### 2D Graph Node Connection
##### Kahn's Algorithm
- 概念 & 模板
	- 詳見 [[advanced_graphs]]
- 題目
	- [[207. Course Schedule - Main]]
	- [[210. Course Schedule II - Main]]
	- [[269. Alien Dictionary - Main]]
##### Graph Node Clone
- 概念
	- 複製一個交互連結的圖形，要完全複製一樣的交互關係及 node value
	- DFS Traverse + 額外一個 map 記錄已經走過並且生成的 node（避免重複 traverse）
		- DFS visited node -> 做 copy + push to map
		- DFS traverse neighbor: 對每個 neighbor node 做 traverse
- 模板
	- 建立一個 origin node addr -> new node addr 的 mapping
		- unordered_map< node*, node* > originNodeToNewNode;
	- DFS Traverse( node , originNodeToNewNode )
		- 檢查 node 是否記錄在 originNodeToNewNode 裏面
			- 是 -> 已經 traverse 過，不用再走
			- 否 -> 執行後續 copy node
		- 建立 new Node()
		- 記錄 traversed node -> new Node 到 originNodeToNewNode 上面 （避免lone neighbor 的時候 ring 回來重複 traverse）
		- for loop: neighborNode of traversed node
			- new Node 的 neighbor add : DFS Traverse( neighborNode , originNodeToNewNode )
				- -> **因爲上面 traverse 過了之後一定會建立node，這邊就可以 post order 建立 neighbor**
- 題目
	- [[133. Clone Graph - Main]]
	- [[138. Copy List with Random Pointer - Main]]
##### Union Find
- 概念
	- 只給 edge 沒給 node
	- 要自己把 edge 還原成 node 的關係，檢查哪些 node 連成一個 component -> **檢查有幾個 component**
	- 檢查 edge 的時候，設定每個 node 的 connect node 是哪一個
		- **一開始的時候還不知道有哪些 edge，每個 node 的 connect node 設爲它們自己**
		- **連結情況 - 類似 tree： 這邊有可能是 node1 對應 connect node1 = node2，但 node2 本身又對應另外一個 connect node2 = node3**
	- 注意
		- **Valid tree 的意義：是所有 node 『無環形』且『只構成一個 component』**
- 模板 - union find + *path compression*
	- Union Find 演算法 + *path compression* - node UnionFindPivotConnectNode( nodeToPrevNodeInComp, node, &pathNodeCnt )
		- component 最少有 current node
			- pathNodeCnt = 1
				- **如果沒有做 path compress，則會建議回傳 pathNodeCnt 輔助 component merge**
				- **但如果有 path compress，這部分可以省略**
		- union find: 找出這個 node 所在 component 的 pivot connect node
			- travNode = node
			- while: (nodeToConnectNodeInComp(travNode) != travNode)
				- travNode = nodeToConnectNodeInComp(travNode);
				- pathNodeCnt++
			- pivotNode = travNode
		- path compression: 這個 node 路徑上所有 node 全部直接連到 pivot node
			- travNode = node
			- while: (nodeToConnectNodeInComp(travNode) != travNode) 
				- nextTravNode = nodeToConnectNodeInComp(travNode)
				- nodeToConnectNodeInComp(travNode) = pivotNode
				- travNode = nextTravNode
	- 主結構
		- 整理 component
			- 生成一個 unordered_map\<int, int\> nodeToConnectNodeInComp -> 記錄每個 node 對應的 component 的 previous node
				- 如果一開始有給有幾個 node: 建立最初的 node connection -> nodeToConnectNodeInComp[node] = node
			- for: 檢查每個 edge，建立『各個 node 組成哪些 component』
				- 檢查 Node 是否第一次記錄 -> **如果只給 edge，沒給 node 有哪幾個，則一邊檢查 edge 一邊建立 node**
					- node1 -> 如果 nodeToConnectNodeInComp 裏面沒有記錄 node1 -> nodeToConnectNodeInComp[node1] = node1
					- node2 -> 如果 nodeToConnectNodeInComp 裏面沒有記錄 node2 -> nodeToConnectNodeInComp[node2] = node2
				- Component pivot node 查詢
					- node1 -> UnionFindPivotConnectNode( node1 ) 查詢 node1 的 component pivot node1 + compNodeCnt1
					- node2 -> UnionFindPivotConnectNode( node2 ) 查詢 node2 的 component pivot node2 + compNodeCnt2
				- Component 合併前檢查
					- 如果 pivot node1 = pivot node2 -> **不用合併** -> continue
					- 如果 pivot node1 != pivot node2 -> 執行合併
				- Component 合併
					- select merge
						- -> **如果沒做 path node compress 則需要選 path node 比較少的來作爲被 merged comp，但如果有 path node compress 則這步驟可省略**
						- merge pivot node: node 比較多的 component 的 pivot node
						- merged node: node 比較少的 component 的 pivot node
					- do merge: nodeToConnectNodeInComp( merged node ) = merge pivot node
						- **這邊把 『被 merge 的』pivot node 對應的 prev node 指向 『merge 對方的』 pivot node -> 沒有做路徑壓縮**
						- 下一次執行 union find 的時候，會在 nodeToConnectNodeInComp 把這次尚未壓縮的路徑，進行壓縮
							-  -> **但只會壓縮 target node -> pivot node 的路徑，其他尚未壓縮的 component node path 不會進行壓縮**
					- 如果要檢查 component num
						- 一開始有 N 個 component for N nodes
						- 每次 merge 一輪，減少一個 component
			- for: 對每一個 node 和 pivot connect node 的路徑進行壓縮 -> **執行後每個 node 都直接連結到 pivot connect node**
				- nodeToConnectNodeInComp( node )
		- 生成 component set
			- 建立各個 pivot connect node 所對應的 unordered_set: unordered_map( node, unoredred_set ) pivotNodeToSet
			- for: 透過 nodeToConnectNodeInComp 生成各個 component 的資訊
				- nodeToConnectNodeInComp( nodeA ) = nodeB -> 加入 pivot node B 所在的 set
					- unordered_map( nodeB ).insert( nodeB )
					- unordered_map( nodeB ).insert( nodeA )
		- 最後 pivotNodeToSet 就是剩餘的各個 component 及其組成內容

- 模板 - 使用 set (非正規 union find)
	- 生成一個 unordered_map\<node to component\> nodeToComponent; -> 記錄每個 node 對應哪個 component index
	- 生成一個 unordered_map\<component idx to set\> componentToSet; -> 記錄每個 component 裏面有哪些 nodes
	- for: 檢查每個 edge，建立『各個 node 組成哪些 component』
		- edge 兩端點 node1, node2
		- Component idx 查詢
			- node1 -> 查詢 nodeToComponent 檢查是哪一個 component
				- 如果 node1 沒等級到任何 component，則爲 nodeToComponent 新增一個 component
				- 如果 node1 屬於某個 component -> 取得這個 component idx1
			- node2 -> 同樣上面方式檢查 component idx2
		- Component 合併
			- 準備階段
				- node1 -> 查詢 componentToSet( component idx1 ) 檢查裏面有哪些 node
				- node2 -> 查詢 componentToSet( component idx2 ) 檢查裏面有哪些 node
				- 選擇誰合併誰： element 比較多的，合併 element 比較少的
			- 執行合併
				- 假設 A 並掉 B（B 的 element 比較少）
				- 合併前更新 mapping： 『B component 裏面每個 node 更新 nodeToComponent( node of Comp B ) = Component A Idx』
				- A set 合併 B Set：  componentToSet( nodeA ).merge( componentToSet( nodeB ) ) 
					- 語法:  `A.merge(B)`
				- 刪除 B Set： componentToSet.erase( nodeB )
	- 最後 componentToSet 就是剩餘的各個 component 及其組成內容

- 題目
	- [[684. Redundant Connection - Main]]
	- [[323. Number of Connected Components in an Undirected Graph - Main]]
	- [[261. Graph Valid Tree - Main]]

#### Node Connection by Dijkstra
- 概念
	- 檢查 node A 是否可以連到 node B
	- 但 node A 和 node B 相連，traverse 有一些條件
	- **更換一個字 change word 算是這種類型的**
	- **BFS + 更新到中間某個 node 最短路徑 -> 適合用來找最短路徑**
		- **注意：走過的不能再走，否則第二次走一定是比較遠的路徑**
	- **DFS + 各種 try -> 純粹用來看能不能走到**
- 模板: BFS
	- 初始化一個 set 記錄所有的 node: allNodeSet
	- 初始化2個 queue: 記錄下一次 BFS 要走的路徑
		- thisLayerNodes
		- nextLayerNodes
	- Initial Condition
		- thisLayerNodes.push( StartNode )
		- allNodeSet.erase( StartNode )
	- 初始化 TraverseLayer
	- BFS Traverse: while( thisLayerNodes.size() )
		- TraverseLayer++
		- Traverse all this layer nodes: while( thisLayerNodes.size() )
			- fetch node
				- travNode = thisLayerNodes.front()
				- thisLayerNodes.pop();
			- check target node reached
				- if( travNode == targetNode )
			- traverse to next node
				- nextNode = rule_fule( travNode )
				- nextLayerNodes.push( nextNode )
		- swap( thisLayerNodes, nextLayerNodes )
- 題目
	- [[127. Word Ladder - Main]]


### Graphs

| #   | Problem                                                                                                                                            | Difficulty | Solution                                                                                    | Concept | TestPass | Finish | Review | Review 2nd | Note                                                                                    |
| --- | -------------------------------------------------------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------------------------------------------------- | ------- | -------- | ------ | ------ | ---------- | --------------------------------------------------------------------------------------- |
| 80  | [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)                                                                         | Medium     | [Link](https://neetcode.io/solutions/number-of-islands)                                     | 8/17    | 8/17     | 10/19  | 10/19  | 11/20      | [[200. Number of Islands - Main]]                                                       |
| 81  | [133. Clone Graph](https://leetcode.com/problems/clone-graph/)                                                                                     | Medium     | [Link](https://neetcode.io/solutions/clone-graph)                                           | 8/18    | 8/18     | 10/19  | 10/19  | 11/21      | [[133. Clone Graph - Main]] - **很容易錯，必須練(1st)** / *想到不同解法，需要重新思考模板 (2nd)*               |
| 82  | [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)                                                                       | Medium     | [Link](https://neetcode.io/solutions/max-area-of-island)                                    | 8/17    | 8/17     | 10/19  | 10/19  | 11/20      | [[695. Max Area of Island - Main]]                                                      |
| 83  | [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)                                                     | Medium     | [Link](https://neetcode.io/solutions/pacific-atlantic-water-flow)                           | 8/19    | 8/19     | 10/19  | 10/19  | 11/20      | [[417. Pacific Atlantic Water Flow - Main]] - *之後要複習*                                   |
| 84  | [130. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)                                                                       | Medium     | [Link](https://neetcode.io/solutions/surrounded-regions)                                    | 8/19    | 8/19     | 10/19  | 10/19  | 11/20      | [[130. Surrounded Regions - Main]] - *用錯方式的話會很難寫，之後要複習 (1st)* / 模板化寫法 (2nd)             |
| 85  | [994. Rotting Oranges](https://leetcode.com/problems/walls-and-gates/description/)                                                                 | Medium     | [Link](https://neetcode.io/solutions/rotting-oranges)                                       | 8/19    | 8/19     | 10/19  | 10/19  | 11/20      | [[994. Rotting Oranges - Main]] - *number remap 技法，要複習(1st)* / 模板化寫法(2nd)               |
| 86  | [286. Walls & Gates](https://leetcode.com/problems/walls-gates/)                                                                                   | Medium     | [Link](https://neetcode.io/solutions/walls-gates)                                           | 8/18    | 8/18     | 10/20  | 10/20  | 11/20      | [[286. Walls & Gates - Main]]                                                           |
| 87  | [207. Course Schedule](https://leetcode.com/problems/course-schedule/)                                                                             | Medium     | [Link](https://neetcode.io/solutions/course-schedule)                                       | 8/20    | 8/20     | 10/20  | 10/20  | 11/19      | [[207. Course Schedule - Main]] - *double mapping + Greedy 的概念 (這個為主）*                  |
| 88  | [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)                                                                       | Medium     | [Link](https://neetcode.io/solutions/course-schedule-ii)                                    | 8/20    | 8/20     | 10/20  | 10/20  | 11/19      | [[210. Course Schedule II - Main]] - 和前一題解法一樣 / 模板化寫法 (2nd)                             |
| 89  | [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)                                                                   | Medium     | [Link](https://neetcode.io/solutions/redundant-connection)                                  | 8/23    | 8/23     | 10/20  | 10/20  | 11/24      | [[684. Redundant Connection - Main]] - **union find + merge component 之後要複習**           |
| 90  | [323. Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) | Medium     | [Link](https://neetcode.io/solutions/number-of-connected-components-in-an-undirected-graph) | 8/22    | 8/22     | 10/21  | 10/21  | 11/24      | [[323. Number of Connected Components in an Undirected Graph - Main]] - **和前一個類似，但難很多** |
| 91  | [261. Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/)                                                                           | Medium     | [Link](https://neetcode.io/solutions/graph-valid-tree)                                      | 8/23    | 8/23     | 10/21  | 10/21  | 11/24      | [[261. Graph Valid Tree - Main]] - *和前兩個類似，也需要再練習 (1st)* / **valid tree 的意義要釐清 (2nd)**  |
| 92  | [127. Word Ladder](https://leetcode.com/problems/word-ladder/)                                                                                     | Hard       | [Link](https://neetcode.io/solutions/word-ladder)                                           | 8/24    | 8/24     | 10/21  | 10/21  | 11/26      | [[127. Word Ladder - Main]] - **類似 node link 但不太一樣，要複習，不會太複雜(1st)** / *模板化寫法 (2nd)*     |
