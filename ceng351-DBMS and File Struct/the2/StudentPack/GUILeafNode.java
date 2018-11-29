import java.awt.Color;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUILeafNode extends GUITreeNode
{	
	public GUILeafNode(CengTreeNode node)
	{		
		super(node);

		this.setBackground(Color.green);

		CengTreeNodeLeaf castNode = (CengTreeNodeLeaf)node;
		
		for(int i = 0; i < castNode.giftCount(); i++)
		{
			if(i >= this.labels.size())
			{
				System.out.println("Gift count is greater than label count.");
				
				return;
			}
			
 			Integer key = castNode.giftKeyAtIndex(i);
			 			
			String keyString = "" + key;
			
			JLabel correspondingLabel = this.labels.get(i);
			
			correspondingLabel.setText(keyString);
			correspondingLabel.repaint();
		}
	}
}
