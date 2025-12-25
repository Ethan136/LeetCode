---
LeetCodeSeq: 12
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 6
LeetCode150ConceptOk: 6
LeetCode150TestPass: 6
LeetCode150Finish: 6
LeetCode150Review: 6
LeetCode150Rev2: 6
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 4
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
### Concept
Heap 相關
- **盡量在 push 前先用一些方式 trim branch（如果當前要 push 的條件更差，則不 push）**
- Prime：連結剩餘的點到某個很多點相連的 component，先找路徑最短的 -> **連結點時候無方向性限制**
	- 概念
		- **所選擇的點，是終點**
		- forward trim branch： push heap 前檢查『un-connected point 如果先前有 push 其他連到 component 更短的路徑，則這次可以不 push』
			- 已經連結的點，連結當下已確定是最短連結距離
		- backward trim branch：pop heap 時如果『selected point 不在 component 連結裡面』才可採用並視為有效連結
		- **preview connect dist 和 recorded connected dist 要分開記錄，避免混淆**
	- 模板化流程
		- forward trim branch：初始化一個 min reach dist preview -> 用來預看傳遞到某個路徑先前 push min heap 的最小值
		- 初始化一個 vector / map / set 記錄已經連結的 point
		- 初始化一個 min heap 記錄『尚未連接的 edge 並排序」
		- 視情況整理一個『有哪些以 selected point 為終點的 link info 2D array (selected point -> link info with dest = selected point)』
		- initial condition
			- **min heap.push(任選『一個』最初連結的點)**
			- 更新 preview min reach dist of origin point
			- **不在這邊記錄 min reach dist of origin point -> 更新 min reach dist 一律在 while 裡面 pop heap 後記錄**
		- while loop
			- min heap pop + check pop valid
				- 檢查：popped point 必須要是 un-connected 的狀態
			- **更新 min connection to selected point**
			- 從 selected point 找出『所有連結到 selected point 的路徑並且放到 min heap 裡面』：這邊選用 forward trim branch 加速
				- **point dist：只看 popped point 和連結點之間的距離** 
				- **使用 min connect dist preview 記錄先前 push heap 的 un-connected point 的路徑最小隻=值**
	- 題目
		- [[1584. Min Cost to Connect All Points - Main]]
- Dijkstra：從某個點開始傳遞擴散到剩下的點，找最短傳遞路徑 -> **傳遞的時候有方向性限制**
	- 概念
		- **所選擇的點，是起點**
		- forward trim branch：push heap 前只選『un-reached point 比先前已到達的更短』且『同一輪 push 中如果有重複的 un-reached point，選最短的』
			- 已經走到的點，如果有更近的走法，則更新走法
		- backward trim branch：pop heap 時必須『當前到達路徑比已記錄的到達路徑短』才可採用並且視為有效傳遞
		- **preview reach dist 和 recorded connected dist 要分開記錄，避免混淆**
	- 模板化流程
		- forward trim branch：初始化一個 min reach dist preview -> 用來預看傳遞到某個路徑先前 push min heap 的最小值
		- 初始化一個 vector / map / set 記錄已經到達的 point + reach dist
		- 初始化一個 min heap 記錄『尚未連接的 edge 並排序」
		- 視情況整理一個『有哪些以 selected point 為出發點的 link info 2D array (selected point -> link info with src = selected point)』
		- initial condition
			- **min heap.push(依照題目設定最初到達的點)**
			- 更新 preview min reach dist of origin point
			- **不在這邊記錄 min reach dist of origin point -> 更新 min reach dist 一律在 while 裡面 pop heap 後記錄**
		- while loop
			- min heap pop + check pop valid
				- 檢查：這邊必須要 popped reached point 如果先前已經記錄過 reach dist，則必須距離更短
			- **更新 min path to selected point**
			- 從 selected point 找出『所有連結到 selected point 的路徑並且放到 min heap 裡面』：這邊選用 forward trim branch 加速
				- **reach dist：從 popped out poin 到下一個連結點的 overall reach dist -> 要看是不是要從 origin dist 開始計算**
				- **使用 min reach dist preview 記錄先前 push heap 的 un-reachecd point 的路徑最小值（push 後可能還沒 pop）**
	- 延伸
		- 如果需要『路徑上面的 node 限制』
			- 則 heap push data 也要記錄相關資訊
				- push 前先 preview 會不會超過 node num
				- pop 時如果超過 node num 也要跳過
			- recorded reach dist 要依據 stop num 來區分（一個 reach point 用一個 array 記錄各種 stop num 下的 min dist）
			- preview reach dist 也要依據 stop num 來區分（一個 reach point 用一個 array 記錄各種 stop num 下的 min dist）
			- 要注意 initial condition push 進去的 stop node num 如果是 invalid num，則 record reach dist 的時候要跳過
		- 如果 initial start point 需要等 K 時間後才能移動
			- 則 initial point 的 reach time 要設定為 K（視為 K 的時候才移動到這個位置，並且可以馬上往下一個點移動）
	- 題目
		- [[743. Network Delay Time - Main]]
		- [[787. Cheapest Flights Within K Stops - Main]] - K Stop 限制
		- [[778. Swim in Rising Water - Main]] - 起始點限制
- Hierholzer：尤拉環，所有點環形相連，要用某種方式走完全部到點，而且不能跳點走
	- 概念
		- 會指定一個起點
		- 依照題目需要的走法，用 DFS traverse 每個點 -> traverse 的時候可能發生跳點，但沒關係
		- DFS traverse 完一個點的所有 next points，才把這個點記錄起來 -> **方向記錄**
		- DFS 完成後，再把『反序記錄的路徑，反轉回來』 -> *得到正序執行的路徑*
	- 模板
		- init 一個 map 整理各個point 可以往後連到哪些點
			- **依照題目需求排序每個 『start pint 對應的 ending point vector』**
		- init 一個 reversedPathRecord array 記錄『反序路徑』
		- Recursive Func 執行 DFS: 依照題目需求 traverse
			- for loop 檢查這個 start point 可以往後走哪些點
				- 走過的點不能再走 -> **如果是原本的點加上 char_mark / traversed_bit，而且各個點環形相連**
					- **-> 要全部 traverse 完畢才能把 traverse_mark 拿掉**
					- back tracking 不確定能不能走出一個解，走看看 -> traverse branch 完成後馬上把 traverse mark 還原
					- graph traverse 避免走回原來的point -> traverse branch 完成後不能把 traverse mark 還原
				- 沒走過的點依照順序走看看 -> Recursive Func 執行 DFS (to point)
				- **這個和一般 DFS 走到 end point 就記錄起來的情況不一樣，是有可能走完之後重新走回來
			- 走完 start point 後每個 next points 後，在 for loop 後面記錄當前的 start point 到 reversedPathRecord
		- DFS 執行完畢後把反序路徑放轉回來： reverse( reversedPathRecord )
	- 題目
		- [[332. Reconstruct Itinerary - Main]]
- Kahn's Algorithm： 從圖形末端點走回起始點
	- 概念
		- **類似 tree 從 Parent Note BFS 走過所有 childs**，只是這個情況『是有 child 和 parent 交互連結的 graph，但有少數幾個沒有被連回來的 nodes』
		- **從這些『沒有被連回來的 nodes 開始走』**
	- 模板
		- 先整理 relationship
			- 整理一個 map 記錄各個 node **被哪些node連過來** -> child node -> parent node 的連結表
			- 可以用這個格式： nordered_map\<point, unordered_set\<point\>> relationshipMap -> **使用 set 可以避免重複把點加入**
		- BFS traverse
			- **BFS 這邊因為都是走『沒有 parent node 的 nodes』，可以用 queue 記錄一次走多個，也可以一次挑一個走**
			- 從『沒有後續 parent node 的點開始走』 -> BFS 先走這些點，走完記錄起來
			- 從 relationship 裡面把『走過的點』從『其他點的 parent nodes 裡面拔掉』
			- 走過的點從 relatinshipMap 拔掉（拔掉這個 key + value Pair）
			- 如果BFS執行到一半，發現剩下的點『每個都有 parent nodes』 -> **代表有相互連結點環型j結構** -> 無法 traverse 完畢，提前結束
	- 題目
		- [[207. Course Schedule - Main]]
		- [[210. Course Schedule II - Main]]
		- [[269. Alien Dictionary - Main]]

### Advanced Graphs3

#### LeetCode 150


| #   | Problem                                                                                                | Difficulty | Solution                                                              | Concept | TestPass | Review | Finish | Review2 | Note                                                                                                               |
| --- | ------------------------------------------------------------------------------------------------------ | ---------- | --------------------------------------------------------------------- | ------- | -------- | ------ | ------ | ------- | ------------------------------------------------------------------------------------------------------------------ |
| 93  | [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)                     | Hard       | [Link](https://neetcode.io/solutions/reconstruct-itinerary)           | 8/29    | 8/29     | 10/22  | 10/22  | 11/18   | [[332. Reconstruct Itinerary - Main]] - **尤拉環，之後要再複習，容易忘記**                                                        |
| 94  | [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)  | Medium     | [Link](https://neetcode.io/solutions/min-cost-to-connect-all-points)  | 8/28    | 8/28     | 10/21  | 10/21  | 11/16   | [[1584. Min Cost to Connect All Points - Main]] - *要再複習，搭配 heap (1st)* / 模板化寫法 (2nd)                               |
| 95  | [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)                           | Medium     | [Link](https://neetcode.io/solutions/network-delay-time)              | 8/27    | 8/27     | 10/22  | 10/22  | 11/17   | [[743. Network Delay Time - Main]] - *Dijkstra 基本題型，要再複習(1st)* / 模板化寫法 (2nd)                                       |
| 96  | [778. Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/)                       | Hard       | [Link](https://neetcode.io/solutions/swim-in-rising-water)            | 8/27    | 8/27     | 10/23  | 10/23  | 11/21   | [[778. Swim in Rising Water - Main]] - **Dijkstra 變體，要能夠判斷出題目的模態(1st)**                                            |
| 97  | [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)                               | Hard       | [Link](https://neetcode.io/solutions/alien-dictionary)                | 8/30    | 8/30     | 10/23  | 10/23  | 11/18   | [[269. Alien Dictionary - Main]] - **Kahn 變體，難在建圖和實作量偏大(1st)** / *模板寫法減少很多實作內容 (2nd)*                              |
| 98  | [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) | Medium     | [Link](https://neetcode.io/solutions/cheapest-flights-within-k-stops) | 8/28    | 8/28     | 10/22  | 10/22  | 11/18   | [[787. Cheapest Flights Within K Stops - Main]] - **Dijkstra 變化型難題，很容易錯，邊界條件很多，要再複習(1st)** / **第二次寫還是寫錯很多次 (2nd)** |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 1631 | [1631. Path with Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) | Medium | [Link](https://neetcode.io/solutions/path-with-minimum-effort) | | | | | [[1631. Path with Minimum Effort - Main]] |
| 1489 | [1489. Find Critical and Pseudo Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) | Hard | [Link](https://neetcode.io/solutions/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree) | | | | | [[1489. Find Critical and Pseudo Critical Edges in Minimum Spanning Tree - Main]] |
| 2392 | [2392. Build a Matrix With Conditions](https://leetcode.com/problems/build-a-matrix-with-conditions/) | Hard | [Link](https://neetcode.io/solutions/build-a-matrix-with-conditions) | | | | | [[2392. Build a Matrix With Conditions - Main]] |
| 2709 | [2709. Greatest Common Divisor Traversal](https://leetcode.com/problems/greatest-common-divisor-traversal/) | Hard | [Link](https://neetcode.io/solutions/greatest-common-divisor-traversal) | | | | | [[2709. Greatest Common Divisor Traversal - Main]] |
