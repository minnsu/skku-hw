
public class Undergraduate extends Student {

	public String year;
	
	public Undergraduate(String fullname, int age, String major, double tuitionFee,
			String year) { // constructor(String, int, String, double, String)
		super(fullname, age, major, tuitionFee); // call super class's constructor, parameter: String fullname, int age, String major, double tuitionFee
		// use set functions of instance variable
		this.setYear(year);
	}

	// get&set functions of year
	public String getYear() {
		return year;
	}
	public void setYear(String year) {
		this.year = year;
	}

	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nYear: " + this.getYear(); // Year: year
	}
	
}
