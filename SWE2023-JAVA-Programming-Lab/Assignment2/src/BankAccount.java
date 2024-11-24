
public class BankAccount {
	/*
	 * Instance : FirstName, LastName, Balance
	 * Method : get, set functions, withdraw, transfer, toString
	 * */
	String FirstName;
	String LastName;
	double Balance;
	
	public BankAccount(String FirstName, String LastName, double Balance) { // constructor(String, String, double)
		this.setFirstName(FirstName);
		this.setLastName(LastName);
		this.setBalance(Balance);
	}

	// get, set function of FirstName
	public String getFirstName() {
		return FirstName;
	}
	public void setFirstName(String FirstName) {
		this.FirstName = FirstName;
	}
	
	// get, set function of LastName
	public String getLastName() {
		return LastName;
	}
	public void setLastName(String LastName) {
		this.LastName = LastName;
	}

	// get, set function of Balance
	public double getBalance() {
		return Balance;
	}
	public void setBalance(double Balance) {
		this.Balance = Balance;
	}
	
	// withdraw function
	public void withdraw(double amount) {
		// print Operation
		System.out.println(this.getFirstName() + " " + this.getLastName() + " withdrew " + "$" + amount); // + "$"); 2000$, $60000 ???
		if(this.getBalance() < amount) { // if amount is larger than this.Balance, print error and do not change
			System.out.println("Failed. Withdrawal amount exceeded account balance.");
		}
		else {
			this.setBalance(this.getBalance() - amount); // set Balance as (present Balance - amount)
			System.out.println("Success.");
		}
	}
	
	public void transfer(BankAccount receiverObject, double amount) {
		// print Operation
		System.out.println(this.getFirstName() + " " + this.getLastName() + " transferred $" + amount 
				+ " to " + receiverObject.getFirstName() + " " + receiverObject.getLastName());
		if(this.getBalance() < amount) { // if amount is larger than this.Balance, print error and do not change
			System.out.println("Failed. You have not enough money!");
		}
		else {
			this.setBalance(this.getBalance() - amount); 
			// this : set Balance as (present Balance - amount)
			receiverObject.setBalance(receiverObject.getBalance() + amount); 
			// receiverObject : set Balance as (present Balance + amount)
			System.out.println("Success.");
		}
	}

	
	public String toString() { // return this's name and balance as below format 
		// toString : "firstname lastname's balance: $Balance"
		return this.getFirstName() + " " + this.getLastName() + "'s balance: $" + this.getBalance();
	}
	
}
