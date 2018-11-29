import java.util.ArrayList;

public class CengTreeNodeLeaf extends CengTreeNode
{
	private ArrayList<CengGift> gifts;
	
	public CengTreeNodeLeaf(CengTreeNode parent) 
	{
		super(parent);
		
		// TODO: Extra initializations
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
	
	// Extra Functions
}
