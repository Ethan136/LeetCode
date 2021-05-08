## teration 記憶體 + 速度超優化

### Code 實踐
[[111 題目 Minimum Depth of Binary Tree]]

-----

### 實作方式
1. Iteration 的時候，可以把分叉點的Node拆下來，當作Stack Node操作
2. 把Left Link 當作Stack Link List 的 Link
3. Node存放兩個資料
	- Right Link：尚需搜索的Node Branch
	- Value：儲存執行到這個Node的時候的一些當下資訊

-----

### 風險
 2. Mem Leak
     - Left 原本連接的 Node，會失去 Link，造成mem leak
     - 拔下來當作Stack的Node，本身也有可能會Mem Leak
         - 如果拆下來的分叉包含Top Root，則把它拆下來組成Stack後，這個Stack連在Root上，
         - 如果拆下來的分叉不包含Top Root，則他沒有和Top Root相連，會Mem Leak
 3. 這個mem leak 在 Leet Code 不會被測出來
 4. 甚至在Leet Code執行的時候，因為Tree 變短，執行時間 & Mem Cost 還會降低
 
 
 -----
 
 ### Iteration & Garbage Collect 簡介
要把遺失的Node接回來，分兩部分
1. 拆分叉Node下來的時候，分叉Node左邊的Node會失去連結，要把它抓回來
2. 如果分叉Node組成的Stack不包含Top Root，則這個Stack裡面的東西會遺失

-----

### Garbage Collect 實作
#### Part1：分叉Node拆下來做Stack的時候，Node左邊的部分
##### 想法
1. 需要馬上連回主要的Tree
2. 假設：分叉Node的『前一個Node還是接在主要的Tree上面』
3. 處理：分叉Node拆下來的時候，要把『分叉Node左邊的Node，接到【分叉Node的前一個Node】』

##### 實作
1. 當分叉Node出現的時候，『分叉Node左邊的Node』要『往上接到 Prev Main Tree Link』
2. 每次向下搜索Tree的時候：如果沒有經過分叉Node
	當下經過的Link』連接到Main Tree
		-> 要更新 『 Prev Main Tree 的 Link 』爲『當下經過的Link』
3. 每次向下搜索Tree的時候：如果經過分叉Node
	因爲分叉Node本身會拆下來，所『走到分叉Node的那個Link不連結到 Main Tree』
		-> 『Prev Main Tree Link』不進行更新
		
##### 備註
1. 在Link List 只需要記住『上一個接到Root 的Node即可達成此需求』
2. 但在Tree的時候每個Node有兩個Link，會不知道要接哪個Link，所以要把『link本身』記錄起來

-----

#### Part2：分叉Node拆下來做成的Stack
##### 想法
1. 如果這個Stack完全只有『一次push疊滿』然後『一次pop到底』
	那麼這個Stack操pop的時候，如果『只移動top指標，不把連結斷開』，則作完的時候，可以保持完整的單向相連
2. 如果這個Stack在操作的時候，有『push』和『pop』交替使用
	則操作後 『會有很多幹List匯聚到某一個Node』
	- 因爲Pop的時候只移動Head指標，原本的連結還在
	- 但Push的時候會有新的Node連到 Head，變成這個Head的位置被一個以上的Node連結）
3. 所以要確保Stack 的 Node Pop 之後有正確連結

##### 實作
1. 要再用一個Stack，叫做UsedStack，把Pop out 的Node接上去
2. 分叉Node Stack Pop 的時候，要確實把連結斷開

-----

#### Part3：從『分叉Node Stack取出Node』，並檢索『分叉Node』右邊時
##### 想法
1. 因爲分叉Node本身已從Tree拆除，所以分叉Node的『右邊的Node』，不會連結到Main Tree
2. 執行分叉Node的順序
	- 一定是『先』執行到某個branch 的 end node
	- 再『回溯到分叉Node的情況』
	- 然後開始檢索『分叉Node的右邊』
3. 執行分叉Node前的 end node 分析
	- 找前面的做法，這個Node 一定可以接回Main Tree
	- 所以這個Node的Link（目前接到null 要記錄起來），要設爲 Main Tree Link

##### 實作
1. 當『回溯到分叉Node的情況』，並開始檢索『分叉Node的右邊Node』的時候
	分叉Node的右邊Node，要用 Part 1 的方式，判斷是否接回 『Prev Main Tree Link』

-----

#### Part4：初始條件 & 邊界條件
##### 想法 - 兩個情況
1. 【情況1】：如果Top Root 就是『分叉Node』，那這個Node
	- Part1相關：沒有一個初始的Prev Main Tree Link 來保證哪個Node可以接回Main Tree，因爲Root本身就被拆掉了
	- Part2相關：會被儲存到Stack操作，Root 會是 UsedStack的 Head
2. 【情況2】：如果Top Root 不是『分叉Node』，那這個Node
	- Part1相關：存在 Prev Main Tree Link 來保證後續遇到分叉Node的時候，分叉Node的左邊可以接回Main Tree
	- Part2相關：UsedStack 會完全和 Root 分離

##### 實作 - 處理情況1 - 如果Top Root 就是『分叉Node』
1. 針對Part1：
	- 此時不存在『第一個 Prev Main Tree Node』
		- 所以先記錄 Top Root，存成 『Top Root Backup』這樣最後才能連回來
		- 並且生成一個『Node指標，Node \*pLinkToFirstDetachNode』
		- 讓 『Prev Main Tree Link』指向『 Node \*pLinkToFirstDetachNode 』
		-> 這樣在搜索Tree的時候，『Node \*pLinkToFirstDetachNode』 
			就會儲存『第一個分叉node左邊的 Detach Node 的位置』
		- 在搜索完Tree的時候，Used Stack Node 的 Head 一定是 Top Root，且Top Root 一段會接到 null
		- 這時候就把『Node \*pLinkToFirstDetachNode』接到Top Root 指向 null 的那一側
2. 針對Part2：
	- 在完全搜索完Tree之後，『Top Root』會接到 『Used Stack Link List』
	- 所以不用特別處理『Used Stack』

##### 實作 - 處理情況2 - 如果Top Root 不是『分叉Node』
1. 針對Part1:
	- 此時Top Root 的左邊 or 右邊，都可以視爲 Prev Main Tree Link
	- 所以不用特別針對 Prev Mail Tree Link 做處理，這時候
		- 『Top Root Backup』可以是 null
		- 『Node \*pLinkToFirstDetachNode』 可以是 null
		- 這兩個等於 null 和 不等於 null，剛好可以用來區別【情況1】和【情況2】
2. 針對Part2:
	- 在完全檢索完Tree之後，『Top Root』不會接到『Used Stack Link List』
	- 所以需要特別把『Used Stack Link List』接回Top Root
	- 這時候Top Root 因爲不是『分叉Node』，所以一定符合
		- 一邊接到Ndoe
		- 一邊接到null，接到null的這一邊，改接到 『Used Stack Link List】