
public class BankAccount {
	/*
	 * Instance : FirstName, LastName, Balance
	 * Method : get, set functions, withdraw, transfer, toString
	 * */
	String FullName;
	String UserName;
	String Password;
	double Balance;
	String operation;
	
	public BankAccount(String FullName, String UserName, String Password, double Balance) { // constructor(String, String, String, double)
		this.setFullName(FullName);
		this.setUserName(UserName);
		this.setPassword(Password);
		this.setBalance(Balance);
	}
	public BankAccount(String FullName, String UserName, String Password, double Balance, String operation) { // constructor(String, String, String, double, String)
		this.setFullName(FullName);
		this.setUserName(UserName);
		this.setPassword(Password);
		this.setBalance(Balance);
		this.setOperation(operation);
	}

	// get, set function of FullName
	public String getFullName() {
		return FullName;
	}
	public void setFullName(String FullName) {
		this.FullName = FullName;
	}

	// get, set function of UserName
	public String getUserName() {
		return UserName;
	}
	public void setUserName(String UserName) {
		this.UserName = UserName;
	}

	// get, set function of Password
	public String getPassword() {
		return Password;
	}
	public void setPassword(String password) {
		Password = password;
	}
	
	// get, set function of Balance
	public double getBalance() {
		return Balance;
	}
	public void setBalance(double Balance) {
		this.Balance = Balance;
	}
	
	// get, set function of operation
	public String getOperation() {
		return operation;
	}
	public void setOperation(String operation) {
		this.operation = operation;
	}
	
	// withdraw function
	public void withdraw(double amount) {
		if(this.getBalance() < amount) { // if amount is greater than present balance
			System.out.println("Withdrawal amount exceeded account balance."); // print error message
		}
		else { // amount <= present balance
			this.setBalance(this.getBalance() - amount); // set balance as 'present balance - amount'
		}
	}
	
}
