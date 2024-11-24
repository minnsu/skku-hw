
public class Staff extends Person{
	
	public String department;
	public double salary;
	
	public Staff(String fullname, int age, double salary, String department) { // constructor(String, int, double, String)
		super(fullname, age); // call super class's constructor, parameter: String fullname, int age
		// use set functions of instance variable
		this.setDepartment(department);
		this.setSalary(salary);
	}
	
	// get&set functions of department
	public String getDepartment() {
		return department;
	}
	public void setDepartment(String department) {
		this.department = department;
	}
	// get&set functions of salary
	public double getSalary() {
		return salary;
	}
	public void setSalary(double salary) {
		this.salary = salary;
	}
	
	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nSalary: " + this.getSalary() // Salary: salary
				+ "\nDepartment: " + this.getDepartment(); // Department: department
	}
	
}
