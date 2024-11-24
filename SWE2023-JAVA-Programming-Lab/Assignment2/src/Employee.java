
public class Employee {
	/*
	 * Instance : FirstName, LastName, M_Salary
	 * Method : get, set functions, toString
	 * */
	String FirstName;
	String LastName;
	double M_Salary;
	
	public Employee(String FirstName, String LastName, double M_Salary){ // constructor(String, String, double)
		this.setFirstName(FirstName);
		this.setLastName(LastName);
		this.setM_Salary(M_Salary);
	}
	public Employee() { // default(empty) constructor
		this("","", 0); // call another constructor, parameter: "", "", 0
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

	// get, set function of monthly salary
	public double getM_Salary() {
		return M_Salary;
	}
	public void setM_Salary(double M_Salary) {
		if(M_Salary > 0) { // if monthly salary is greater than 0, set
			this.M_Salary = M_Salary;
		}
		else { // else do nothing.
			
		}
	}

	public String toString() { // return this's name and monthly salary as below format
		// toString : "fisrtname lastname's salary: $M_Salary"
		return getFirstName() + " " + getLastName() + "'s salary: $" + getM_Salary();
	}
	
}
