
public class Graduate extends Student {

	public String researchInterest;
	
	public Graduate(String fullname, int age, String major, double tuitionFee,
			String researchInterest) { // constructor(String, int, String, double, String)
		super(fullname, age, major, tuitionFee); // call super class's constructor, parameter: String fullname, int age, String major, double tuitionFee
		// use set functions of instance variable
		this.setResearchInterest(researchInterest);
	}

	// get&set functions of researchInterest
	public String getResearchInterest() {
		return researchInterest;
	}
	public void setResearchInterest(String researchInterest) {
		this.researchInterest = researchInterest;
	}
	
	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nResearch Interest: " + this.getResearchInterest(); // Research Interest: researchInterest
	}
	
}
