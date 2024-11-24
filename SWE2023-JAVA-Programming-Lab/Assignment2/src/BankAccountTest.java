
public class BankAccountTest {

	public static void main(String[] args) {
		BankAccount h1 = new BankAccount("John", "Ewing", 14000); // human1 : John Ewing, 14,000 as balance
		BankAccount h2 = new BankAccount("Jack", "Sparrow", 100000); // human2 : Jack Sparrow, 100,000 as balance

		// print "Balance ->" and h1, h2's name, balance
		System.out.println("Balance ->");
		System.out.println(h1);
		System.out.println(h2);

		// print "Operation ->" and call h1's withdraw function: parameter: 2,000
		System.out.println("Operation ->");
		h1.withdraw(2000);

		// print "Balance ->" and h1, h2's name, balance
		System.out.println("Balance ->");
		System.out.println(h1);
		System.out.println(h2);

		// print "Operation ->" and call h2's transfer function: parameter: h1, 50,000
		System.out.println("Operation ->");
		h2.transfer(h1, 50000);

		// print "Balance ->" and h1, h2's name, balance
		System.out.println("Balance ->");
		System.out.println(h1);
		System.out.println(h2);

		// print "Operation ->" and call h2's withdraw function: parameter: 60,000
		System.out.println("Operation ->");
		h2.withdraw(60000);

		// print "Balance ->" and h1, h2's name, balance
		System.out.println("Balance ->");
		System.out.println(h1);
		System.out.println(h2);

		// print "Operation ->" and call h2's transfer function: parameter: h1, 55,000
		System.out.println("Operation ->");
		h2.transfer(h1, 55000);

		// print "Balance ->" and h1, h2's name, balance
		System.out.println("Balance ->");
		System.out.println(h1);
		System.out.println(h2);
	}

}
