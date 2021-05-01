### 題目需求
1. substring 再這邊的定義：不能有重複字元
2. 字元：char 的所有內容（空格、特殊符號）

-----

### 題目要點
1. 要找『substring的長度』
2. 不用回傳對應的 substring

-----

### 解題

#### 方向
1. 只有在遇到新的 substring 的時候，才進行資料更新

-----

#### 流程
1. 從string最左邊開始掃，掃到 index == length
2. 條件擴充
3. 初始條件
	* max substring 長度 = 0
	* current substring 左端點 index = -1 (-1 代表 index before first)
4. 檢查掃到的字元
	* 沒被包含在目前的 substring 裏面 -> 記錄這個 char 的 index -> continue
	* 已經被包含在目前的 substring 裏面
		1. 先更把現有的substring資訊進行更新及記錄	
			* 計算『現有的 substring 長度』 = 前一個 index - 左端點 index + 1
			* 更新目前蒐集到的最大 substring 長度 = max( current substring 長度, max substring 長度)
		2. 開始新的 substring
			* curent substring 左端點 = 已記錄起來的 『當前重複 char 的前一個 index + 1』
			* 記錄這個 char 的 index

-----

#### 注意
1. 『現有的 substring 長度』 = 前一個 index - 左端點 index + 1 = current index - 左端點 index
2. loop 跑完的時候，『最後一段 substring』可能會沒更新長度
3. 每個字元記錄的 index array，初始化的時候預設每個字元都出現在 index = -1 的地方（-1 代表 index before first）