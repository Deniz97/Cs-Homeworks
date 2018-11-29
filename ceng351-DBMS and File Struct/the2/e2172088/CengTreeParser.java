import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

public class CengTreeParser 
{	
	public static ArrayList<CengGift> parseGiftsFromFile(String filename)
	{
		ArrayList<CengGift> giftList = new ArrayList<CengGift>();
				
		
		try {
			for (String line : Files.readAllLines(Paths.get("./"+filename) ) ) {
			    
			    String[] array = line.split("\\|");
			    
			    CengGift temp = new CengGift( Integer.parseInt(array[0]) ,array[1],array[2],array[3] );
			    giftList.add(temp);
			}
		} catch (NumberFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}		
		
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

		Scanner sc = new Scanner(System.in);
		


		while (true){
		    String command = sc.nextLine();
		    if(command.length()==0){
		    	System.out.println("Bad input");
		    	return;
		    }
		    if(command.startsWith("add")){
		    	String array[] = command.split("\\|");
		    	CengGift temp = new CengGift( Integer.parseInt(array[1]) ,array[2],array[3],array[4] );
		    	
		    	CengChristmasList.addGift(temp);
		    }
		    else if(command.startsWith("print")){
		    	CengChristmasList.printTree();
		    }
		    else if(command.startsWith("quit")){
		    	break;
		    }
		    else if(command.startsWith("search")){
		    	String array[] = command.split("\\|");
		    	int key = Integer.parseInt(array[1]);
		    	CengChristmasList.searchGift(key);
		    }
		    else{
			    System.out.println("Bad input");
			    return;
			    
		    }

		}
		sc.close();
		// Commands (quit, add, search, print) are case-insensitive.
	}
}
