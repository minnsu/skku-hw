import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		BankAccount account1 = new BankAccount("Firuz", "firuz", "p@ssw0rd", 2000.0);
		BankAccount account2 = new BankAccount("Kang Seong", "kang", "p@ssw0rd123", 34000.0);
		BankAccount account3 = new BankAccount("SiHyeon Ryu", "ryu", "p@ssw0rd1234", 10000.0);

		boolean login = true; // while loop condition
		Scanner input = new Scanner(System.in);
		String tmpUsername; // tmp user name variable of login loop
		String tmpPassword; // tmp password variable of login loop
		int currentUsernum = 0; // user number: Firuz 1, Kang Seong 2, SiHyeon Ryu 3
		while (login) {
			// print lines and input tmp user name and tmp password
			System.out.println("Login");
			System.out.print("Username: ");
			tmpUsername = input.nextLine();
			System.out.print("Password: ");
			tmpPassword = input.nextLine();
			
			// compare to account's name and password. set current user number, set login variable as false(escape while loop)
			if (account1.getUserName().equals(tmpUsername) && account1.getPassword().equals(tmpPassword)) {
				login = false;
				currentUsernum = 1;
			} else if (account2.getUserName().equals(tmpUsername) && account2.getPassword().equals(tmpPassword)) {
				login = false;
				currentUsernum = 2;
			} else if (account3.getUserName().equals(tmpUsername) && account3.getPassword().equals(tmpPassword)) {
				login = false;
				currentUsernum = 3;
			}
		}
		
		BankAccount currentAccount = currentUsernum == 1 ? account1 : (currentUsernum == 2 ? account2 : account3);
		// set current account using the ternary operator
		
		int userChoice = 4; // set a positive initial value other than 0 ~ 3
		while (userChoice > 0) {
			mainMenu(); // call menu print function
			userChoice = input.nextInt();
			if (userChoice == 1) {
				checkBalance(currentAccount); // call checkBalance function
			} else if (userChoice == 2) {
				withdrawMoney(currentAccount); // call withdrawMoney function
			} else if (userChoice == 3) {
				lastOperation(currentAccount); // call lastOperation function
			}
		}
		System.out.println("Thank you for banking with us!");

	}

	public static void mainMenu() {
		System.out.printf("%s\n%s\n%s\n%s\n", "1. Check balance (Enter 1);", "2. Withdraw money (Enter 2);",
				"3. Last Operation (Enter 3);", "0. Exit (Enter 0);");
		/*
		 * 1. Check balance (Enter 1);
		 * 2. Withdraw money (Enter 2);
		 * 3. Last Operation (Enter 3);
		 * 0. Exit (Enter 0);
		 * 
		 */
	}

	private static void checkBalance(BankAccount currentAccount) {
		System.out.printf("User: %s\nBalance: %.1f\n", currentAccount.getFullName(), currentAccount.getBalance());
		currentAccount.setOperation("Balance checking"); // set Last Operation as "Balance Checking"
		// print User name and User's balance using get function of BankAccount class
	}

	private static void withdrawMoney(BankAccount currentAccount) {
		// Enter withdraw amount
		System.out.print("Enter amount: ");
		Scanner amount_tmp = new Scanner(System.in);
		double amount = amount_tmp.nextDouble();
		currentAccount.withdraw(amount); // call withdraw function of BankAccount class
		currentAccount.setOperation("Withdrawal"); // set Last Operation as "Withdrawal"
	}

	private static void lastOperation(BankAccount currentAccount) {
		System.out.printf("Name: %s\nCurrent Balance: %.1f\nLast Operation: %s\n",
				currentAccount.getFullName(),
				currentAccount.getBalance(),
				currentAccount.getOperation()
				);
		/*
		 * Name: ~~~
		 * Current Balance: ~~~~.~
		 * Last Operation: ~~~
		 * 
		 */
	}
}
