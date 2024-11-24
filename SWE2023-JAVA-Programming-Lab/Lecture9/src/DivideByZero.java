import java.util.InputMismatchException;
import java.util.Scanner;

public class DivideByZero {
	// demonstrates throwing an exception when a divide-by-zero occurs
	public static int quotient(int numerator, int denominator) {
		return numerator / denominator; // possible division by zero
	} // end method quotient

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in); // scanner for input

		int numerator = 0, denominator = 0, result = -1;
		 
			System.out.print("Please enter an integer numerator: ");
			numerator = scanner.nextInt();
			System.out.print("Please enter an integer denominator: ");
			denominator = scanner.nextInt();

			result = quotient(numerator, denominator);
		
		System.out.printf("\nResult: %d / %d = %d\n", numerator, denominator,
				result);
	} // end main
} // end class DivideByZeroNoExceptionHandling
