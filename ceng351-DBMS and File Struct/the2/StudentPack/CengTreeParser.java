import java.io.IOException;

import java.util.ArrayList;

public class CengTreeParser 
{	
	public static ArrayList<CengGift> parseGiftsFromFile(String filename)
	{
		ArrayList<CengGift> giftList = new ArrayList<CengGift>();
				
		// You need to parse the input file in order to use GUI tables.
		// TODO: Parse the input file, and convert them into CengGifts
		
		return giftList;
	}
	
	public static void startParsingCommandLine() throws IOException
	{
		// TODO: Start listening and parsing command line -System.in-.
		// There are 4 commands:
		// 1) quit : End the app, gracefully. Print nothing, call nothing, just break off your command line loop.
		// 2) add : Parse and create the gift, and call CengChristmasList.addGift(newlyCreatedGift).
		// 3) search : Parse the key, and call CengChristmasList.searchGift(parsedKey).
		// 4) print : Print the whole tree, call CengChristmasList.printTree().

		// Commands (quit, add, search, print) are case-insensitive.
	}
}
