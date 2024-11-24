import java.util.Scanner;
public class RectangleTest {
	
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		
		Rectangle Rectangle1 = new Rectangle(2,4,2,2);
		Rectangle Rectangle2 = new Rectangle(3,3,2,2);
		Rectangle union = Rectangle1.Union(Rectangle2);
		Rectangle intersect = Rectangle1.Intersect(Rectangle2);
		
		if(intersect != null) {
			System.out.print(intersect);
		}
		Point checkpoint = new Point(3,5);
		boolean inside = Rectangle1.Contain(checkpoint);
		System.out.print("\n" + inside);
		
	} // end main

	// prints a menu and returns a value corresponding to the menu choice
	private static int getMenuChoice() {
		Scanner input = new Scanner(System.in);

		System.out.println("1. Set Length");
		System.out.println("2. Set Width");
		System.out.println("3. Exit");
		System.out.print("Choice: ");

		return input.nextInt();
	} // end method getMenuChoice
} // end class RectangleTest

