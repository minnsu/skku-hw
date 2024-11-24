import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
public class AlgorithmsTest {


 
	   public static void main( String[] args )
	   {
	      String[] suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
	      
	      // Create and display a list containing the suits array elements
	      List< String > list = Arrays.asList( suits ); // create List
	      System.out.printf( "Unsorted array elements: %s\n", list );

	      Collections.sort( list ); // sort ArrayList
	      
	      System.out.println("Hollo thore\n".replace('o', 'e')); //returns 
 
	      
	      Collections.shuffle(list);
	      System.out.printf( "Shuffle array elements: %s\n", list );
	      
	      String[] suitsCopy = new String [4];
	      List< String > listCopy = Arrays.asList(suitsCopy);
	      Collections.copy(listCopy, list);
	      System.out.printf( "List Copy elements: %s\n", listCopy );
	      
	      List< String > listFill = Arrays.asList(suitsCopy);
	      Collections.fill(listFill, "R");
	      System.out.printf( "List Fill elements: %s\n", listFill );
	      
	      int index = Collections.binarySearch(list, "Spades");
	      System.out.printf( "Element Spades exists in the List at index: %d\n", index );
	      
	      int frequancy = Collections.frequency(listFill, "R");
	      System.out.printf( "the repetition of R in the listFill is: %d\n", frequancy );
	      
	      
	      boolean disjoint = Collections.disjoint(list, listFill);
	      System.out.printf( "The disjoint of list and listFill is %b\n", disjoint );
	      
	   } // end main
	} // end class  

	
 
