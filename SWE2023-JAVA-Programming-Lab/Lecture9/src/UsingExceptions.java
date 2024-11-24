import java.io.IOException;
import java.util.Scanner;

public class UsingExceptions {
	public static void main(String[] args) {
		int a;
		Scanner input = new Scanner(System.in);
		a = input.nextInt();
		try {
			if (a > 10) {
				// generate some error if the number is more than 10
				throw new testingExc("number is more than 10");
			}
			else {
				throw new RuntimeException("number is less than 10");
			}
		} catch (testingExc |RuntimeException e) {
			e.printStackTrace();
		}
		
	} // end main
}

//user defined exception
class testingExc extends Exception {
	public testingExc(String message) {
		super(message);
	}
}