import java.util.Scanner;

public class InvoiceTest {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);

		// input for variables to enter Invoice class's instance
		System.out.print("Product name: ");
		String ProductName = input.nextLine(); // Product Name
		System.out.print("Quantity: ");
		int Quantity = input.nextInt(); // Quantity
		System.out.print("Price ($): ");
		double Price = input.nextDouble(); // Price

		input.close(); // Scanner close

		Invoice inv = new Invoice(ProductName, Quantity, Price); // make Invoice class variable inv 
		// call constructor, parameter: ProductName, Quantity, Price
		System.out.printf("Total invoice amount: $%f", inv.getInvoiceAmount()); // int cast for same as example.
		// print "Total invoice amount: $InvoiceAmount", InvoiceAmount is return by inv's getInvoiceAmount method
	}

}
