
public class Student extends Person{

	public String major;
	public double tuitionFee;
	
	public Student(String fullname, int age, String major, double tuitionFee) { // constructor(String, int, String, double)
		super(fullname, age); // call super class's constructor, parameter: String fullname, int age
		// use set functions of instance variable
		this.setMajor(major);
		this.setTuitionFee(tuitionFee);
	}
	
	// get&set functions of major
	public String getMajor() {
		return major;
	}
	public void setMajor(String major) {
		this.major = major;
	}
	// get&set functions of tuitionFee
	public double getTuitionFee() {
		return tuitionFee;
	}
	public void setTuitionFee(double tuitionFee) {
		this.tuitionFee = tuitionFee;
	}
	
	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nMajor: " + this.getMajor() // Major: major
				+ "\nTuition Fee: " + this.getTuitionFee(); // Tuition Fee: tuitionFee
	}
	
}
