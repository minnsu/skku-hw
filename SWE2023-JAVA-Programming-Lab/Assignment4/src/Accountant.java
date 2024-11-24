
public class Accountant extends Staff {

	public int officeNo;
	
	public Accountant(String fullname, int age, double salary, String department,
			int officeNo) { // constructor(String, int, double, String, int)
		super(fullname, age, salary, department); // call super class's constructor, parameter: String fullname, int age, double salary, String department
		// use set functions of instance variable
		this.setOfficeNo(officeNo);
	}
	
	// get&set functions of officeNo
	public int getOfficeNo() {
		return officeNo;
	}
	public void setOfficeNo(int officeNo) {
		this.officeNo = officeNo;
	}

	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}
	
	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nOffice Number: " + this.getOfficeNo(); // Office Number: officeNo
	}
	
}
