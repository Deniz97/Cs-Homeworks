import java.util.ArrayList;

public class CengTree
{
	public CengTreeNode root;
	public int level;
	
	public CengTree(Integer order)
	{
		CengTreeNode.order = order;
		root= null;
		level=0;
		
	}
	
	public void addGift(CengGift gift)
	{		
		//if it is the first item being inserted
		if(root==null){
			root = new CengTreeNodeLeaf(null);
			((CengTreeNodeLeaf)root).helper_add(gift);
			this.level=1;
			return;
		}

		//Normal behavior
		if(level==1){
			//root not full
			if( ! ((CengTreeNodeLeaf)root).helper_isFull()){
				((CengTreeNodeLeaf)root).helper_add(gift);
			}
			//root is full, time to split
			else{
				CengTreeNode new_sibling = new CengTreeNodeLeaf(null);
				CengTreeNode new_sibling_left = new CengTreeNodeLeaf(null);
				((CengTreeNodeLeaf)root).helper_add(gift);
				int middle = CengTreeNode.order;
				for(int i=0;i<middle+1;i++){
					((CengTreeNodeLeaf)new_sibling).helper_add(  ((CengTreeNodeLeaf)root).helper_remove()  );
				}
				for(int i=0;i<middle;i++){
					((CengTreeNodeLeaf)new_sibling_left).helper_add(  ((CengTreeNodeLeaf)root).helper_remove()  );
				}

				root = new CengTreeNodeInternal(null);
				new_sibling.setParent(root);
				new_sibling_left.setParent(root);
				((CengTreeNodeInternal)root).helper_insertChild(0, new_sibling_left);
				((CengTreeNodeInternal)root).helper_insertChild(1, new_sibling);
				((CengTreeNodeInternal)root).helper_copyUp();
				level+=1;
			}
		}
		//level is higher than 1
		else{
			
			CengTreeNodeLeaf proper =  ((CengTreeNodeLeaf)helper_properPlace( gift ));
			//Leaf not full, just add
			if(  !  proper.helper_isFull() ){
				proper.helper_add(gift);
			}
			//Full, need to split
			else{
				CengTreeNode new_sibling = new CengTreeNodeLeaf(null);
				proper.helper_add(gift);
				int middle = CengTreeNode.order;
				for(int i=0;i<middle+1;i++){
					((CengTreeNodeLeaf)new_sibling).helper_add( proper.helper_remove()  );
				}
				

				
				new_sibling.setParent( proper.getParent() );
				
				int pos =((CengTreeNodeInternal)proper.getParent()).helper_getChildPos(proper);
				((CengTreeNodeInternal)proper.getParent()).helper_insertChild(pos+1, new_sibling);
				((CengTreeNodeInternal)proper.getParent()).helper_copyUp();
				if( ((CengTreeNodeInternal)proper.getParent()).helper_isOverflow()  ){
					helper_splitInternal(proper.getParent());
					
				}
				
			}
			
			
		}
	}
	
	public ArrayList<CengTreeNode> searchGift(Integer key)
	{
		
		ArrayList<CengTreeNode> retval = new ArrayList<CengTreeNode>();
		if(root==null){
			System.out.println("Could not found "+key+".");
			return null;	
		}
		

		//level is higher than 1
		
			CengTreeNode tmp = root;
			retval.add(tmp);
			for(int i=1;i<level;i++){
				//((CengTreeNodeInternal)tmp).helper_printKeys();
				tmp = ((CengTreeNodeInternal)tmp).helper_getPtr(key);
				retval.add(tmp);
				
			}
				int index =(((CengTreeNodeLeaf)tmp).helper_getIndexOfKey(key));
				if( index!=-1){
					for(int i=0;i<retval.size();i++){
						CengTreeNode tmp_node = retval.get(i);
						if( tmp_node.helper_isLeaf() ){
							((CengTreeNodeLeaf)tmp_node).helper_printGift(i,index);
						}
						else{
							((CengTreeNodeInternal)tmp_node).helper_printKeys(i);
						}
					}
					return retval;
				}
			System.out.println("Could not found "+key+".");
			return null;	
		
	}
	
	
	
	public void printTree()
	{
		if(root==null){ return; }
		helper_printTraversal(root,0);
	}
	
	
	public void helper_printTraversal(CengTreeNode node,int level){
		if(node.helper_isLeaf()){
			((CengTreeNodeLeaf)node).helper_printGifts(level);
			return;
		}
		((CengTreeNodeInternal)node).helper_printKeys(level);
		
		int len = ((CengTreeNodeInternal)node).helper_childCount();
		for(int i=0;i<len;i++){
			helper_printTraversal( ((CengTreeNodeInternal)node).helper_getChildAt(i),level+1);
		}	
		
	}


	
	
	// Extra Functions
	
	public CengTreeNode helper_properPlace( CengGift gift ){
		CengTreeNode tmp = root;
		
		
		for(int i=1;i<level;i++){
			tmp =((CengTreeNodeInternal)tmp).helper_getPtr(gift.key());
		}
		
		
		return tmp;
		
	}
	
	public void helper_splitInternal(CengTreeNode node){
		//is not root
		if( node.getParent()!=null  ){
			CengTreeNode new_sibling = new CengTreeNodeInternal(null);
			int middle = CengTreeNode.order;
			int key_to_move_up=-1;
			
			for(int i=0;i<middle+1;i++){
				((CengTreeNodeInternal)new_sibling).helper_insertChild(0,  ((CengTreeNodeInternal)node).helper_removeChild()  );
			}
			for(int i=0;i<middle;i++){
				key_to_move_up = ((CengTreeNodeInternal)node).helper_removeKey();
				((CengTreeNodeInternal)new_sibling).helper_addKey(key_to_move_up);
			}
			key_to_move_up = ((CengTreeNodeInternal)node).helper_removeKey();
			
			if(((CengTreeNodeInternal)node).helper_isBelowLeaf()){
				((CengTreeNodeInternal)new_sibling).helper_copyUp();
				((CengTreeNodeInternal)node).helper_copyUp();
			}

			
			
			CengTreeNodeInternal parent = ((CengTreeNodeInternal)node.getParent()); 
	
			new_sibling.setParent((CengTreeNode)parent);
			parent.helper_insertChild(    parent.helper_getChildPos(node)+1   , new_sibling);
			parent.helper_addKey(key_to_move_up);
			//set the parent of new silbling's children
			((CengTreeNodeInternal)new_sibling).helper_setChildsParents();
			if(parent.helper_isOverflow()){
				helper_splitInternal((CengTreeNode)parent);
			}
		}
		//is root
		else{
			CengTreeNode new_sibling = new CengTreeNodeInternal(null);
			int middle = CengTreeNode.order;
			int key_to_move_up=-1;
			
			for(int i=0;i<middle+1;i++){
				((CengTreeNodeInternal)new_sibling).helper_insertChild(0,  ((CengTreeNodeInternal)node).helper_removeChild()  );
			}
			for(int i=0;i<middle;i++){
				key_to_move_up = ((CengTreeNodeInternal)node).helper_removeKey();
				((CengTreeNodeInternal)new_sibling).helper_addKey(key_to_move_up);
			}
			key_to_move_up = ((CengTreeNodeInternal)node).helper_removeKey();
			
			root = new CengTreeNodeInternal(null);
			
			if(((CengTreeNodeInternal)node).helper_isBelowLeaf()){
				((CengTreeNodeInternal)new_sibling).helper_copyUp();
				((CengTreeNodeInternal)node).helper_copyUp();
			}

			
			new_sibling.setParent(root);
			node.setParent(root);
			((CengTreeNodeInternal)root).helper_insertChild(0, node);
			((CengTreeNodeInternal)root).helper_insertChild(1, new_sibling);
			((CengTreeNodeInternal)root).helper_addKey(key_to_move_up);
			((CengTreeNodeInternal)new_sibling).helper_setChildsParents();
			level+=1;
		}
		
	}
	
	
	
	
}
