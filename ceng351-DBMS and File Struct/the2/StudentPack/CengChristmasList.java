import java.awt.EventQueue;
import java.util.ArrayList;

public class CengChristmasList
{
	private static Integer order;
	
	private static String fileName;
	
	private static Boolean guiEnabled;
	
	private static CengTree christmasTree;
	private static CengGUI window;
	
	 // If you want to see the nodes always next to each other, change this to false.
	private static Boolean wrapNodes = true;
	
	// If you want to have a static window, change this to false
	private static Boolean packFrame = true;
	
	public static void main(String[] args) throws Exception
	{		
		if(args.length != 3)
		{
			throw new Exception("Usage : java CengChristmasList -order- -inputFileName- -guiEnabled (True or False)- ");			
		}
		
		order = Integer.parseInt(args[0]);
		fileName = args[1];
		guiEnabled = Boolean.parseBoolean(args[2]);
		
		christmasTree = new CengTree(order); 
				
		Integer orderN = 2 * order + 1; // N-based order, for GUI purposes only.

		CengGUI.orderN = orderN;
		
		if(guiEnabled)
		{
			EventQueue.invokeLater(new Runnable()
			{
				public void run() 
				{
					try 
					{
						window = new CengGUI();
						window.show();
					} 
					catch (Exception e) 
					{
						e.printStackTrace();
					}
				}
			});
		}

		/* A way of bulk loading, but not really. Useful for big tree print testing.
		for(int i = 1; i < 100; i++)
		{
			CengGift testGift = new CengGift(i, "test" + i, "test", "test");

			CengChristmasList.addGift(testGift);
		}
		*/
		
		CengTreeParser.startParsingCommandLine();
	}
	
	public static void addGift(CengGift gift)
	{
		christmasTree.addGift(gift);
		
		if(guiEnabled)
		{
			if(window == null)
			{
				System.out.println("Err: Window is not initialized yet.");
				
				return;
			}
			
			window.modelNeedsUpdate(christmasTree.root);
		}
	}

	public static void searchGift(Integer key)
	{
		ArrayList<CengTreeNode> visitedNodes = christmasTree.searchGift(key);
		
		if(guiEnabled)
		{
			window.modelNeedsUpdate(christmasTree.root);

			if(visitedNodes != null)
			{
				window.updateWithSearchResult(visitedNodes, key);
			}
		}
	}
	
	public static void printTree()
	{
		christmasTree.printTree();
		
		if(guiEnabled)
		{
			window.modelNeedsUpdate(christmasTree.root);
		}
	}
	
	public static String getFilenameToParse()
	{
		return CengChristmasList.fileName;
	}
	
	public static Boolean shouldWrap()
	{
		return CengChristmasList.wrapNodes;
	}
	
	public static Boolean shouldPack()
	{
		return CengChristmasList.packFrame;
	}
}
