---
Level: Main
StartDate: ""
FinishDate: ""
LeetCodeLv: 
Algorithm: 
TimeCost:
---
# Hierarchy List
```dataviewjs

function GetPropertyOfDictObj( DiscObj, PropertyStr ) {
	if( DiscObj == null ) return null;

	if( PropertyStr.includes( "." ) == false ) {
		return DiscObj[ PropertyStr ];
	}

	var PropertyElement = PropertyStr.split(".");
	var HeadProperty = PropertyElement.shift();
	return GetPropertyOfDictObj( DiscObj[ HeadProperty ], PropertyElement.join( "." ) );
}

function GetPageDataOfFileLinkAndTargetPropertyInGroup( Pages, TargetPropertyArray ) {

	let PageDataArray = [];//[Pages.map( p => p.file.link )];
	for( let TargetProperty of TargetPropertyArray ) {
		PageDataArray.push( Pages.map( p => GetPropertyOfDictObj( p, TargetProperty ) ) );
	}
	return PageDataArray;
}

function DisplayTableWithPropertyGroupByPath( MainPageFolderPath, Pages, PropertyList ) {

	var PropertyTitleList = ["RelativePath"].concat( PropertyList );

	var PageGroups = Pages.groupBy( p => p.file.folder );
	var PageDataArray = [];
	for( let OnePageGroup of PageGroups ) {
		var RelativePath = OnePageGroup.key.substring( MainPageFolderPath.length );
		if( !RelativePath.length ) RelativePath = "Main Folder"
		var HeaderDataRowOfGroup = [ RelativePath ];
		var PageInfoDataRowOfGroup = [""].concat( GetPageDataOfFileLinkAndTargetPropertyInGroup( OnePageGroup.rows, PropertyList ));

		PageDataArray.push( HeaderDataRowOfGroup );
		PageDataArray.push( PageInfoDataRowOfGroup );
	}

	dv.table( PropertyTitleList, PageDataArray);
	// new Notice(PageDataArray.length);
}

var MainPageFolderPath = dv.current().file.folder;
var NotePages = dv.pages( '"'+MainPageFolderPath+'"' ).filter( p => p.file.path != dv.current().file.path);

// dv.span("## Lower Level Notes");
// DisplayTableWithPropertyGroupByPath( MainPageFolderPath, NotePages, ["file.link"] );


function CreateStringOfTestInListForm( ListLevel, Text ) {
	var Result = "";
	while( ListLevel-- ) Result += "\t";

	Result += (" - " + Text + "\n");
	return Result;
}

function GetPageHierarchyInfo( TargetPage ) {
	var PageParentFolders = TargetPage.file.folder.split("/");
	var isMainPage = ( TargetPage.Level && TargetPage.Level == "Main" ) || ( PageParentFolders.slice(-1)[0] == TargetPage.file.name );
	if( isMainPage ) PageParentFolders.pop();

	return {    isMainPage: isMainPage, 
				ParentFolders: PageParentFolders };
}

function CheckExtendPointOnHierarchy( Hierarchy, ParentSequenceArray ) {

	if( ParentSequenceArray.length == 0 ) {
		return [ Hierarchy,  ParentSequenceArray ];
	}

	var CheckSequenceIndex = 0;
	for( let i = 0; i < Hierarchy.length; i++ ) {
		if( Hierarchy[i].Name != ParentSequenceArray[ CheckSequenceIndex ] ) continue;

		ParentSequenceArray.shift();
		return CheckExtendPointOnHierarchy( Hierarchy[i].Child, ParentSequenceArray );
	}

	// [ DivertPointOnHierarchy, DivertDifferenceSequence ]
	return [ Hierarchy, ParentSequenceArray ];
}

function AddPageToHierarchy( Hierarchy, TargetPage ) {

	// get page hierarchy info
	var PageHierarchyInfo = GetPageHierarchyInfo( TargetPage );

	// check the dirvert position on Hierarchy
	var [ ExtendPointOnHierarchy, RemainedNotMatchedPageParents ] = CheckExtendPointOnHierarchy( Hierarchy, PageHierarchyInfo.ParentFolders );

	// extend hierarchy from extend point
	for( let ParentFolder of RemainedNotMatchedPageParents ) {
		let NewHierarchyNode = HierarchyAddNewNode( ExtendPointOnHierarchy, ParentFolder, "" );
		ExtendPointOnHierarchy = NewHierarchyNode.Child;
	}

	HierarchyAddNewNode( ExtendPointOnHierarchy, TargetPage.file.name, TargetPage.file.link );
}

function StructuralizePageInfoByPathHierarchy( InputPages ) {

	var Result = [];
	for( let Page of InputPages ) {
		AddPageToHierarchy( Result, Page );
	}
	return Result;
}

function ConvertHierarchyStructurizedPagesToTextList( HierarchyStructurizedPages, StartLevel = 0 ) {
	var Result = "";
	for( let HierarchyNode of HierarchyStructurizedPages ) {
		var ListText = ( HierarchyNode.Link ) ? ( HierarchyNode.Link ) : ( HierarchyNode.Name );
		Result += CreateStringOfTestInListForm( StartLevel, ListText );

		if( HierarchyNode.Child.length ) {
			Result += ConvertHierarchyStructurizedPagesToTextList( HierarchyNode.Child, (StartLevel + 1) );
		}
	}
	return Result;
}

function HierarchyAddNewNode( Hierarchy, NodeName, NodeLink ) {

	var MatchedNodeOnCurrentLevel = null;
	for( let NodeOnCurrentLevel of Hierarchy ) {
		if( NodeOnCurrentLevel.Name != NodeName ) continue;

		MatchedNodeOnCurrentLevel = NodeOnCurrentLevel;
		break;
	}

	if( MatchedNodeOnCurrentLevel ) {
		MatchedNodeOnCurrentLevel.Link = NodeLink;
		return MatchedNodeOnCurrentLevel;
	}

	var NewNode = { Name: NodeName, Link: NodeLink, Child : null };
	NewNode.Child = [];

	Hierarchy.push( NewNode );
	return NewNode;
}


function compare_func(propName) {
    return function(a,b) {
        if (a[propName] < b[propName])
            return -1;
        if (a[propName] > b[propName])
            return 1;
        return 0;
    };
}

function HierarchySortNodeByName( Hierarchy ) {

	if( !Hierarchy.length ) return;

	Hierarchy = Hierarchy.sort( compare_func("Name") );
	for( let Node of Hierarchy ) {
		if( !Node.Child.length ) continue;
		HierarchySortNodeByName( Node.Child );
	}
}

var HierarchyStructurizedPageInfo = StructuralizePageInfoByPathHierarchy( NotePages );
HierarchySortNodeByName( HierarchyStructurizedPageInfo );
var HierarchyText = ConvertHierarchyStructurizedPagesToTextList( HierarchyStructurizedPageInfo );

dv.span(HierarchyText);
```

# Process Record
- [ ] [[(N) Name - Ans 1 - Method - Complexity]]：（時間花費）
	- [ ] 題目解析
	- [ ] 想法筆記
	- [ ] 實作解題