import java.util.ArrayList;

public class CengTreeNodeInternal extends CengTreeNode
{
	private int order;
	private ArrayList<Integer> keys;
	private ArrayList<CengTreeNode> children;	
	
	public CengTreeNodeInternal(CengTreeNode parent) 
	{
		super(parent);
		order = CengTreeNode.order;
		super.type = CengNodeType.Internal;
		keys= new ArrayList<Integer>();
		children=new ArrayList<CengTreeNode>();
		// TODO: Extra initializations, if necessary.
	}
	// Extra Functions
	
	public void helper_addKey(int key){
		
		//int key = item.key();

		 //append to appropriate place
		for(int i=0;i< keys.size();i++){
			if(keys.get(i) > key ){
				keys.add(i, key);
				return;
			}
		}
		//if size is 0 or need to append at end
		keys.add(key);
	}
	
	public int helper_removeKey(){
		return keys.remove(keys.size()-1);
	}
	public void helper_insertChild(int pos,CengTreeNode child){
		children.add(pos,child);
	}
	public int helper_getChildPos(CengTreeNode child){
		return children.indexOf(child);
	}
	public CengTreeNode helper_removeChild(){
		return children.remove( children.size()-1 );
	}
		
	
	public void helper_copyUp(){
		keys.clear();
		for(int i=1;i<children.size();i++){
			keys.add( ((CengTreeNodeLeaf)children.get(i)).helper_getSmallestKey()  );
			
		}
	}
	
	public void helper_copyUpInternal(){
		keys.clear();
		for(int i=1;i<children.size();i++){
			keys.add( ((CengTreeNodeInternal)children.get(i)).helper_getSmallestKey()  );
			
		}
	}
	
	public boolean helper_isBelowLeaf(){
		return children.get(0).helper_isLeaf();
	}
	
	public int helper_getSmallestKey(){
		if(keys.size()>0){
			return keys.get(0);
		}
		return -1;
	}
	
	public void helper_printKeys(int level){
		for(int j=0;j<level;j++){ System.out.print("\t");}
		System.out.println("<index>");
		
		for(int i=0;i<keys.size();i++){
			for(int j=0;j<level;j++){ System.out.print("\t");}
			System.out.println(keys.get(i) );
		}
		for(int j=0;j<level;j++){ System.out.print("\t");}
		System.out.println("</index>");
	}
	
	public int helper_childCount(){
		return children.size();
	}
	
	public boolean helper_isFull(){
		return keys.size() >= 2*order;
	}
	public boolean helper_isOverflow(){
		return keys.size() > 2*order;
	}
	
	public CengTreeNode helper_getChildAt(int pos){
		return children.get(pos);
	}
	
	public CengTreeNode helper_getPtr(int key){
		for(int i=0;i<keys.size();i++){
			if(keys.get(i)>key){
				return children.get(i);
			}
		}
		return children.get(children.size()-1);
	}
	
	public void helper_setChildsParents(){
		for(int i=0;i<children.size();i++){
			children.get(i).setParent(this);
		}
		
	}
	
	
	// GUI Methods - Do not modify
	public ArrayList<CengTreeNode> getAllChildren()
	{
		return this.children;
	}
	public Integer keyCount()
	{
		return this.keys.size();
	}
	public Integer keyAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.keys.get(index);			
		}
	}
	
	
}
