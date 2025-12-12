---
LeetCodeSeq: 8
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 3
LeetCode150ConceptOk: 3
LeetCode150TestPass: 3
LeetCode150Finish: 3
LeetCode150Review: 3
LeetCode150Rev2: 3
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 1
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
### Concept
#### 結構
##### 整體概念
- 儲存
	- 把多個 word prefix 相同的部分存在一起，分岔的部分分開儲存 -> **是一個 tree 的結構**
		- **每個 node 可以代表一個 char**
		- 但每個 node 的 char 意義，存在於『parent node 連過來的 link 所對應的數值』，而 node 本身可以不用特別儲存自身對應的 char
		- ex: root -> a -> b
			- root 可以走到 a，代表 root -> next node [a] 是 valid -> 此時 node a 本身不需要儲存 value = a
			- a 可以走到 b，代表 node_a -> next node [b] 是 valid -> 此時 node b 本身不需要儲存 value = b
	- 每個 node 可能有一個 end word 的 flag -> 代表『從 root 走到這個 node，是先前儲存的某個 word』
	- **需要 dummy augmented head -> 用來代表『尚未有任何 word 的起始點』**
- Traverse
	- **可以這樣記： node -> next node [ char_a ] 的意義，就是『從 Node 往後走 char_a 到下一個 node**
	- **可以這樣記：node -> next node [ word[ to_idx ] ] 的意義，就是『從 Node 往後延著 word 走到 to_idx 』**

##### 範例
- root (start point)
	- root -> *child node a 可以走*
		- node a -> *child node b 可以走*
			- node b -> *child node c 可以走*
				- node c -> *child node d 可以走 + end word flag  = true* -> **先前有存 word "abc"**
					- node d -> *child node e 可以走*
						- node e -> *child node 都無法走* + end word flag = true -> **先前有存 word "abcde"
			- node b -> *child node f 可以走*
				- node f -> *child node a 可以走*
					- node a -> *child node 都無法走* + end word flag = true -> **先前有存 word "abfa"
- root (start point / 不包含任何 word)  link[a] valid -> node_a link[b] valid + end word flag -> node_b link[c] valid-> node_c link all invalid + end word flag
	- 對應的 word 爲 "ab" 和 "abc"
	- root -> a -> b (end word) -> c (end word)

#### Traverse
##### Overview
由於 Trie 其實是把多個 word 儲存成 tree 的結構，而使用上通常是需要『延著 word index 進行操作』
- 加入某個word
- 刪除某個word
- 查詢某個word

-> **上面這幾個操作，都是延著 word[ idx ] 進行比對 / 檢查 / 新增 node / 刪除 node -> 可以使用 Iteration 或 Recursive**
**通常來說 Iteration 的操作是正規作法，速度比較快**

##### Recursive Traverse：結構類似 Backtraking / Tree，但速度比較慢（比較不推薦）

###### 基本模板
- DFS Recursive( node )
	- if( Node = nullptr ) return
	- if( Node->end ) -> *代表某個已儲存的 word 是從 first parent child 到這個 node 所有 char 串起來*
		- **這個 node 本身的數值意義，在前一個 parent node 的 child node [ char ] 裏面**
	- for( valid child node )
		- DFS Recursive( child node )

###### Check Word - pre order check
- bool TraverseAndCheckWord( node, word, **to_idx** ) -> **意義：從 node 開始，試著往後走一格 word[ to_idx ] 到下一個 node + Preorder check node**
	- if( !node ) return false -> **代表當前 node 不存在，無法繼續往後走 -> 這個 word 沒有存在 trie 裡面**
	- if( to_idx < 0) || ( to_idx >= word.size() ) return -> **不符合預期的情況：進來的時候 word[ idx ] 一定要是 valid**
		- 檢查 idx 是否 valid -> 和 backtracking 的模板習慣相同 -> 先檢查 idx
	- Get Node of word[to_idx] -> **這邊一定是 node 和 word[idx] 都 valid 的情況**
		- Node* nodeOfChar = node -> child[ word[to_idx] ]
	- if(idx == **(word.size() - 1)** ) -> **代表已經走到 word[end idx] ，則這個 node 對應 word.end() 的 char -> 檢查 end word flag**
		- 如果檢查 prefix：return true
		- 如果檢查 whole word：return nodeOfChar->endWordFlag / endWordCnt
	- return TraverseAndCheckWord( nodeOfChar, word, to_idx+1 )

###### Add Word - pre order add word
- void TraverseAndCreateNode( node, word, **to_idx** ) -> **意義：從 node 開始，往後走一格 word[ to_idx ] 到下一個 node + Preorder create node**
	- if( !node ) return -> **不符合預期的情況: 走進來的時候 node 一定要是 valid**
		- 因爲如果 word 走完，就不用往後走 nullptr，直接 return 即可
		- 而如果 word 還沒走完，則上一層 parent node，一定要先幫前一層的 word[idx-1] 建立這個 node，再走到這個 node
	- if( to_idx < 0) || ( to_idx >= word.size() ) return -> **不符合預期的情況：進來的時候 word[ idx ] 一定要是 valid**
		- 檢查 idx 是否 valid -> 和 backtracking 的模板習慣相同 -> 先檢查 idx
	- Create Node -> **這邊一定是 node 和 word[idx] 都是 valid 的情況 / 使用 ref to pointer 來設定 next node + 視情況建立 new node 並連結上去**
		- Node* &nodeOfChar = node -> child[ word[to_idx] ]
		- if( !nodeOfChar ) nodeOfChar = new Node
	- if(idx == **(word.size() - 1)** ) -> **代表已經走到 word[end idx] ，則這個 node 對應 word.end() 的 char -> 要記錄 end word flag**
		- 如果不能存重複字串 -> end word flag = true
		- 如果可以存重複字串 -> end word cnt ++
		- return
	- TraverseAndCreateNode( node -> child[ word[idx] ], word, to_idx+1 ) -> traverse to next char
- 主結構
	- 建立 augmented root
	- DFS Recursive: Root 開始往下走 + 建立 node
		- TraverseAndCreateNode( root, word, 0) -> **意義：從 root 開始，延著 word[idx = 0] 往後走一格**

###### Delete Word - post order delete word
- bool checkAndDeleteNode( **ref to node** )
	- 檢查 node valid
		- if(!node) return false
	- 檢查 node 被其他 word 當作 endWord 使用
		- if(node->endWord) return false
	- 檢查 node 後續有其他 word 被拿來使用
		- for( each node -> next node[] ) 
			- if( next node[i] valid ) return false
	- finish & delete node
		- delete node
		- node = nullptr
		- return true
- void TraverseAndDeleteNode( **ref to node**, word, to_idx ) -> **意義：從 node 開始，往後走一格 word[ to_idx ] 到下一個 node + Postorder del node**
	- if( !node ) return -> **不符合預期的情況: 走進來的時候 node 一定要是 valid**
		- 因爲如果 word 走完，就不用往後走 nullptr，直接 return 即可
		- 而如果 word 還沒走完，則上一層 parent node，一定要先幫前一層的 word[idx-1] 建立這個 node，再走到這個 node
	- if( to_idx < 0) || ( to_idx >= word.size() ) return -> **不符合預期的情況：進來的時候 word[ idx ] 一定要是 valid**
		- 檢查 idx 是否 valid -> 和 backtracking 的模板習慣相同 -> 先檢查 idx
	- 檢查 word 是否儲存在這個 trie 裡面 + 取得 NextNode
		- Node* &nodeOfChar = node -> child[ word[to_idx] ]
		- if( !nodeOfChar ) return -> **這個情況就是 word[to_idx] 不在 trie 裡面 -> word 不存在 trie 裡面 -> 不可執行 delete node**
	- if( to_idx == **(word.size() - 1)** ) -> *如果走到 word[ end idx ] 則結束 traverse*
		- 更新 word store flag
			- 可存入同樣字串重複存：**end word cnt** -= 1 -> *word 抽掉的時候 end word cnt 減 1* -> **使用 end word cnt 是爲了可以『存入同樣字串 N 個』**
			- 不可存入同樣字串重複：**end word flag = false** -> *word 抽調的時候 end word flag 取消*
		- if( checkAndDeleteNode(&nodeOfChar) == false ) -> 如果 node of word[end] 無法刪除 -> 前面的 node 也不能刪除
			- return false
	- else -> *如果還沒走到 word[ end_idx ] 則繼續 traverse*
		- TraverseAndDeleteNode( nodeOfChar, word, to_idx+1 ) -> traverse to next char + post ord delete next node
	- if( nodeOfChar == nullptr ) -> *PostOrd Delete: word[ to _idx ] 的 node 被刪除，則試著把這個 node 刪除*
		- return checkAndDeleteNode( node )

- **注意：這個 func 之所以不用 return true / false 來決定 parent node 是否 delete word**
	- **是因爲 false 的情況，無法判斷是『word 不在 trie 上面』還是『有其他 word 使用 root -> node 這一段』**(false 的二義性，容易出錯)

##### Iteration Traverse：這個是正規用法

###### 基本模板
- node = &m_root
- for( to_idx = 0 : word.size()-1 )
	- node = TraverseToNextNode( node, word, to_idx )
	- if(!node) break / retur

###### Check Word
- 主結構
	- node = &m_root
	- for( to_idx = 0 : word.size()-1 )
		- node = node->next Node[ word[to_idx] ]
		- if(!node) return false
	- return node->endWord / endWordCnt

###### Create Word
- 主結構
	- node = &m_root
	- for( to_idx = 0 : word.size()-1 )
		- Node* &nodeOfChar = node -> next Node[ word[to_idx] ]
		- if(!nodeOfChar) nodeOfChar = new Node()
		- node = nodeOfChar
	- node->endWord = true

###### Delete Word - 要優化
- bool checkAndDeleteNode( **ref to node** )
	- 檢查 node valid
		- if(!node) return false
	- 檢查 node 被其他 word 當作 endWord 使用
		- if(node->endWord) return false
	- 檢查 node 後續有其他 word 被拿來使用
		- for( each node -> next node[] ) 
			- if( next node[i] valid ) return false
	- finish & delete node
		- delete node
		- node = nullptr
		- return true
- 主結構
	- node = &m_root
	- vector\<Node*\> nodePath; nodePath.reserve(word.size())
	- 記錄 node path
		- for( to_idx = 0 : word.size()-1 )
			- node = node->next Node[ word[to_idx] ]
			- if(!node) return false -> *這邊 return false 代表 word 不存在無法 delete*
			- nodePath.push_back(node) -> *traverse 後才把 node 存到 node path，否則會把 m_root 存到 path 裡面*
	- 取消 endword flag / 減少 endWordCnt
		- nodePath.back()->endWord = false
	- 把 node 刪除
		- while(nodePath.size())
			- if(checkAndDeleteNode( nodePath.back() ) == false) break
				- -> 試著從後面開始往前刪除 node，如果某個 node 無法刪除，則代表這個 node 以前的要保留
			- nodePath.pop_back()
	- return true -> *這邊 return true 代表 word delete 成功*


### Tries

#### LeetCode 150


| #   | Problem                                                                                                                    | Difficulty | Solution                                                                         | Pass | Finish | Review | Review2 | Note                                                                                    |
| --- | -------------------------------------------------------------------------------------------------------------------------- | ---------- | -------------------------------------------------------------------------------- | ---- | ------ | ------ | ------- | --------------------------------------------------------------------------------------- |
| 61  | [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)                             | Medium     | [Link](https://neetcode.io/solutions/implement-trie-prefix-tree)                 | 7/05 | 9/21   | 9/21   | 12/09   | [[208. Implement Trie (Prefix Tree) - Main]]<br>Recursive / **Iteration** 各練習一次 (2nd)   |
| 62  | [211. Design Add & Search Words DS](https://leetcode.com/problems/design-add-and-search-words-data-structure/description/) | Medium     | [Link](https://neetcode.io/solutions/design-add-and-search-words-data-structure) | 7/06 | 9/21   | 9/21   | 12/10   | [[211. Design Add & Search Words DS - Main]]<br>*Recursive + Iteration 混合 - 模板練習 (2nd)* |
| 63  | [212. Word Search II](https://leetcode.com/problems/word-search-ii/)                                                       | Hard       | [Link](https://neetcode.io/solutions/word-search-ii)                             | 7/07 | 9/21   | 9/21   | 12/11   | [[212. Word Search II - Main]]<br>**Backtracking + Trie 模板練習 (2nd)**                    |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 2707 | [2707. Extra Characters in a String](https://leetcode.com/problems/extra-characters-in-a-string/) | Medium | [Link](https://neetcode.io/solutions/extra-characters-in-a-string) | | | | | |