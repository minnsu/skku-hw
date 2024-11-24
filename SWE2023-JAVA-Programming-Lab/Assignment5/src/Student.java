
import java.util.Scanner;

public abstract class Student extends Person implements Authentication {
	private String username;
	private String password;
	
	// get, set functions of username
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}

	// get, set functions of password
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	
	public void register() {
		// System.out.printf("=================================\nRegister (Student):\n"); // = * 33
		Scanner input = new Scanner(System.in);
		// input fullname, username, password
		System.out.printf("Full name: ");
		String fullname = input.nextLine();
		System.out.printf("Username: ");
		String username = input.nextLine();
		System.out.printf("Password: ");
		String password = input.nextLine();

		super.setFullname(fullname);
		this.setUsername(username);
		this.setPassword(password);
	}

	public boolean login() {
		System.out.printf("=================================\nLogin:\n"); // = * 33
		Scanner input = new Scanner(System.in);
		// input username, password
		System.out.printf("Username: ");
		String username = input.nextLine();
		System.out.printf("Password: ");
		String password = input.nextLine();
		// If username and password are correct at the same time
		if (this.getUsername().equals(username) && this.getPassword().equals(password)) {
			System.out.printf("=================================\n"); // = * 33
			System.out.println("Welcome to SKKU grade calculator!");
			return true;
		} 
		System.out.println("Incorrect username or password");
		return false;
	}

	// make abstract method
	public abstract void getGrades();
	public abstract void calculateGPA(String Grade, int Credits);
	public abstract void scholarship();
}
