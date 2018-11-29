import java.util.ArrayList;

public class CengTreeNodeLeaf extends CengTreeNode
{
	private ArrayList<CengGift> gifts;
	private int order;
	public CengTreeNodeLeaf(CengTreeNode parent) 
	{
		super(parent);
		super.type = CengNodeType.Leaf;
		order = CengTreeNode.order;
		gifts = new ArrayList<CengGift>();
		// TODO: Extra initializations
	}
	// Extra Functions
	public void helper_add(CengGift item){
		
		 //append to appropriate place
		for(int i=0;i< gifts.size();i++){
			if(gifts.get(i).key()>item.key() ){
				gifts.add(i, item);
				return;
			}
		}
		//if size is 0 or need to append to end
		gifts.add(item);
		
		
	}

	public boolean helper_isFull(){
		return gifts.size() == 2*order;
	}
	
	public CengGift helper_remove(){
		return gifts.remove( gifts.size()-1 );
	}
	
	public int helper_getSmallestKey(){
		if(gifts.size()>0){
			return gifts.get(0).key();
		}
		return -1;
	}
	
	public void helper_printGifts(int level){
		for(int j=0;j<level;j++){ System.out.print("\t");}
		System.out.println("<data>");
		for(int i=0;i<gifts.size();i++){
			for(int j=0;j<level;j++){ System.out.print("\t");}
			System.out.print("<record>");
			System.out.print(gifts.get(i).fullName());
			System.out.println("</record>");
		}
		for(int j=0;j<level;j++){ System.out.print("\t");}
		System.out.println("</data>");
	}

	public void helper_printGift(int level,int index){
		for(int j=0;j<level;j++){ System.out.print("\t");}

		System.out.print("<record>");
		System.out.print(gifts.get(index).fullName());
		System.out.println("</record>");

		
	}
	
	public int helper_getIndexOfKey(int key){
		for(int i=0;i<gifts.size();i++){
			if(gifts.get(i).key()==key){
				return i;
			}
		}
	return -1;
	}
	
	
	
	
	
	// GUI Methods - Do not modify
	public int giftCount()
	{
		return gifts.size();
	}
	public Integer giftKeyAtIndex(Integer index)
	{
		if(index >= this.giftCount())
		{
			return -1;
		}
		else
		{
			CengGift gift = this.gifts.get(index);
			
			return gift.key();
		}
	}
	

}
