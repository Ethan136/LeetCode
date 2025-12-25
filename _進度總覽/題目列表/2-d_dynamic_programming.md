---
LeetCodeSeq: 14
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 11
LeetCode150ConceptOk: 11
LeetCode150TestPass: 11
LeetCode150Finish: 11
LeetCode150Review: 11
LeetCode150Rev2: 11
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 5
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
### Concept
- **先寫思路，再解題目**
- **要能夠思考『動作』和『狀態』的差異**
	- DP 需要定義的是狀態，動作不能當作狀態
	- [[121. Best Time to Buy and Sell Stock - Main]]
- **coin 相關題目可能會需要先 sort**
	- [[518. Coin Change II - Main]]
- Brute Force + memo 2D
	- 先思考 back tracking brute force 解法
	- 再加上 memo 2D array 記錄執行情況避免重複運算
	- 通常是 top down
	- **如果是走圖的情況，則只能用用這個形式**
		- [[329. Longest Increasing Path in a Matrix - Main]]
- State Transition 2D Matrix (1D Optimize)
	- 通常會需要先想到 2D State Transition Matrix 計算方式，再優化成 1D DP
		- **State transition matrix 需要設定 initial condition 在某一個格子**
		- **optimize to 1D 的 state transition matrix 要盡量寫完整，即使是 `if(c == 0) method[c] = method[c]` 也要盡量寫下來**
		- **double 1D transition matrix**
			- **每一輪計算前或後要執行swap swap thisRow / NextRow 再做計算**
			- 如果每一輪儲存的數值在 thisRow 裡面 -> 先 swap(thisRow, nextRow (prevRow)) ，再計算 -> **最後回傳 this row**
			- 如果每一輪儲存的數值在 nextRow / prevRow 裡面 -> 先計算，再 swap(thisRow, nextRow (prevRow)) -> **最後回傳this row**
		- 當前的一個 state 有可能是一個 array -> 實際上可以算是 3D DP 的情況 ->  **coin 計算問題**
			- `target amount = expand previous valid amount methods with coin num`
			- 2D DP 的範圍
				- coin 有 1 to n 種
				- 每種硬幣可以是 1 to K 個
			- 但要找的是coin 任意湊到 target amount 的時候，coint 1 to n & count 1 to K 的問題，中間的「一個 state 會變成一個 amount 有幾種湊法」
				- **其實類似一種 tree 的 BFS 題型** -> **使用 this term / next term 的時候，每一輪要把 this term 傳遞到 next term 之外，next term 必須清 0**
					- **如果 coin num 可以是 0 -> 則 this term 要先直接傳遞到 next term，隨後才開始 expand this term to next term**
				- **要注意累加 method cnt 到各個 amount 的時候，是否會發生數值 overflow -> 可能需要把各 amount 的 method cnt 用 unsigned long long 來記錄**
			- 實際上因為可以用「比較小的 amount method cnt 展開延伸到 比較大的 amount method cnt」 amountMethodCnt[ amount + coin ] += amountMethodCnt[ amount ]
				- **這樣 state transition 就可以把 coin cnt 的部分給壓縮掉**
			- coin to target amount methods 的問題，如果要用「this term / next term」的機制
				- 由於「當前的 methods 要全部傳遞到下一個 term，然後在下一個 term 用 expand 展開 method cnt」 
				- **「每一個 term 開始前把 next term 清空」 + 「使用 swap 交替 this term result / next term result」**
			- 排列組合
				- coin type - coin num 在外圈 / target sum 在內圈：組合（只看 coin 組成不看 coin 採用順序）
				- target sum 在外圈 / coin type - coin num 在內圈：排列（coin 採用順序視為不同的）
		- String Matching 的題目通常可以變成 bottom up 走格子的類型
			- **再 2D DP 壓縮成 1D 的時候，要注意「縱軸方向要是不變量的 string（也就是沒有分支情況的string）**
			- **情況複雜的時候，先列出各種情況，看要如何整併，最後再開始解題**
			- **通常會用 matchCondFromIdx / matchCondFromIdx_prev 來作為 1D DP x 2 的計算核心**
				- word1 = 縱軸 / word2 = 橫軸
				- 這個 matchCondFromIdx 會是 size =  word2.size()+1 -> 多擴充一個 index 用於 "ending empty char"
				- 從 word1[end + 1] 開始往前檢查到 word1[0]
					- 每一次檢查 word2[end + 1] 和 word2[end to 0]
				- 起始情況為 word1[end + 1] 的位置 -> 位於 word1 ending empty char 的地方
					- word2[end + 1] -> match cond = 1
					- word2[end to 0] -> match cond **依照題目需求，要看 match word2[j] to word1[i] 有沒有需要依照嚴格順序**
						- 有嚴格順序
							- [[72. Edit Distance - Main]]
							- [[10. Regular Expression Matching - Main]]
						- 無嚴格順序
							- [[115. Distinct Subsequences - Main]]
	- 通常是 bottom up **從 finish point 往前推算**
		- **如果分歧點的行為，會影響後續要檢查的 DP(i, j) 位置 -> 使用 bottom up**
		- [[1143. Longest Common Subsequence - Main]]
		- [[72. Edit Distance - Main]]
		- [[10. Regular Expression Matching - Main]]
		- [[115. Distinct Subsequences - Main]]
	- 也可能是 top down 並且把執行邏輯轉換成 **走格子左上到右下** （這種情況通常也可以 bottom up）
		- [[62. Unique Paths - Main]]
		- [[97. Interleaving String - Main]]
	- **還有一種是 N 個各自意義的 transition matrix 互相交錯** -> **通常會是『選了某個，就要 CD 跳過一個，這種 branch operation 相關的題目』**
		- forward Induction： 採用多個 Action 作為 DP
			- 每個 action DP 要能反應當下的 state -> 可能 4 種 action （有->無 / 無->有 / 有->有 / 無->無）反應出兩種 state（有/無）
			- 可能前 n 個 index 是 initial cond 要先處理
			- 然後再從 index n+1 開始，檢查到 index end
			- **state transition -> idx i 當前的各個 DP 情況，可以做哪些操作轉換到 idx i+1**
		- backward Induction：採用多個 state 作為 DP
			- 每個 state DP 就是最核心的狀態
			- 需要 append n 個 end 之後的 state（假設 DP 會用到 index i + n)
			- 可能需要 append k 個 end 之後的 number array（看 DP 有沒有用到 index i + k）
			- 從 index = end 開始，檢查到 index 0
			- **state transition -> idx i 各個 DP 的情況，有可能做哪些行為傳遞到 idx i + 1**
		- *ring back 又要間隔 CD 的情況 -> idx0 / idx1 各算一次*
		- [[309. Best Time to Buy and Sell Stock with Cooldown - Main]]
		- [[198. House Robber - Main]]
		- [[213. House Robber II - Main]]
		- [[91. Decode Ways - Main]]
	- **當前「一個 state」本身是一個 array**
		- [[518. Coin Change II - Main]]
		- [[494. Target Sum - Main]]
- 上面兩種方式都可能用到 append row / col of DP array
	- Brue Force + memo 2D: append row / col 不用設值
	- State Transition Matrix
		- 2D Matrix: 需要設定 appended row / col 的 initial state (可能是 0 也可能是 1 也可能是 invalid)
		- 1D Matrix (optz DP): 只需要設定 appended element 的 initial state
		- **要如何設定 initial state -> 可以用初始幾個情況稍微迭代想一下**
		- **針對 matching 的情況 -> 如果append 的 row / col 是 out of range -> 初始化為 zero match**

### 2-D Dynamic Programming

#### LeetCode 150


| #   | Problem                                                                                                                            | Difficulty | Solution                                                                            | Concept | TestPass | Finish | Review | Review2 | Note                                                                                                           |
| --- | ---------------------------------------------------------------------------------------------------------------------------------- | ---------- | ----------------------------------------------------------------------------------- | ------- | -------- | ------ | ------ | ------- | -------------------------------------------------------------------------------------------------------------- |
| 111 | [62. Unique Paths](https://leetcode.com/problems/unique-paths/)                                                                    | Medium     | [Link](https://neetcode.io/solutions/unique-paths)                                  | 8/09    | 8/09     | 10/14  | 10/14  | 11/08   | [[62. Unique Paths - Main]]                                                                                    |
| 112 | [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)                                      | Medium     | [Link](https://neetcode.io/solutions/longest-common-subsequence)                    | 8/10    | 8/10     | 10/15  | 10/15  | 11/08   | [[1143. Longest Common Subsequence - Main]] - *之後要再練習壓縮成 1D DP + 想很久(1st)* / **2D DP 有直接想出來 (2nd)**            |
| 113 | [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) | Medium     | [Link](https://neetcode.io/solutions/best-time-to-buy-and-sell-stock-with-cooldown) | 8/10    | 8/10     | 10/15  | 10/15  | 11/08   | [[309. Best Time to Buy and Sell Stock with Cooldown - Main]] - *之後要再練習壓縮成 1D DP + 想很久* / *先寫思路再解題順很多 (2nd)*   |
| 114 | [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/)                                                               | Medium     | [Link](https://neetcode.io/solutions/coin-change-ii)                                | 8/11    | 8/11     | 10/15  | 10/15  | 11/08   | [[518. Coin Change II - Main]] - *之後要再練習壓縮成 1D DP + 想很久* / **有可能有重複計算的問題，要避免，想很久(2nd)**                        |
| 115 | [494. Target Sum](https://leetcode.com/problems/target-sum/)                                                                       | Medium     | [Link](https://neetcode.io/solutions/target-sum)                                    | 8/11    | 8/11     | 10/15  | 10/15  | 11/08   | [[494. Target Sum - Main]] [[97. Interleaving String - Main]] - *之後要再練習壓縮成 1D DP + 想很久* / **第二次複習還是寫很久 (2nd)** |
| 116 | [97. Interleaving String](https://leetcode.com/problems/interleaving-string/description/)                                          | Medium     | [Link](https://neetcode.io/solutions/interleaving-string)                           | 8/12    | 8/12     | 10/15  | 10/15  | 11/09   | [[97. Interleaving String - Main]] - *之後要再練習壓縮成 1D DP* / **第二次複習還是寫很久 (2nd)**                                  |
| 117 | [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)                     | Hard       | [Link](https://neetcode.io/solutions/longest-increasing-path-in-a-matrix)           | 8/14    | 8/14     | 10/15  | 10/15  | 11/09   | [[329. Longest Increasing Path in a Matrix - Main]]                                                            |
| 118 | [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)                                                 | Hard       | [Link](https://neetcode.io/solutions/distinct-subsequences)                         | 8/15    | 8/15     | 10/17  | 10/17  | 11/09   | [[115. Distinct Subsequences - Main]] - **必寫題，可以練很多資訊** / **注意 DP 中間值是否會 overflow (2nd)**                      |
| 119 | [72. Edit Distance](https://leetcode.com/problems/edit-distance/)                                                                  | Medium     | [Link](https://neetcode.io/solutions/edit-distance)                                 | 8/13    | 8/13     | 10/18  | 10/18  | 11/09   | [[72. Edit Distance - Main]] - **第一次寫很快，複習時候寫很久** / **複習2nd還是完全想不到**                                           |
| 120 | [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)                                                               | Hard       | [Link](https://neetcode.io/solutions/burst-balloons)                                | 8/30    | 8/30     | 10/19  | 10/19  | 11/11   | [[312. Burst Balloons - Main]] - **Divide & Conquer + 特別範圍更新的 DP**                                             |
| 121 | [10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)                                      | Hard       | [Link](https://neetcode.io/solutions/regular-expression-matching)                   | 8/16    | 8/16     | 10/19  | 10/19  | 11/09   | [[10. Regular Expression Matching - Main]] - 太難，之後看看概念即可                                                       |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 63 | [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) | Medium | [Link](https://neetcode.io/solutions/unique-paths-ii) | | | | | [[63. Unique Paths II - Main]] |
| 64 | [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) | Medium | [Link](https://neetcode.io/solutions/minimum-path-sum) | | | | | [[64. Minimum Path Sum - Main]] |
| 1049 | [1049. Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/) | Medium | [Link](https://neetcode.io/solutions/last-stone-weight-ii) | | | | | [[1049. Last Stone Weight II - Main]] |
| 877 | [877. Stone Game](https://leetcode.com/problems/stone-game/) | Medium | [Link](https://neetcode.io/solutions/stone-game) | | | | | [[877. Stone Game - Main]] |
| 1140 | [1140. Stone Game II](https://leetcode.com/problems/stone-game-ii/) | Medium | [Link](https://neetcode.io/solutions/stone-game-ii) | | | | | [[1140. Stone Game II - Main]] |
