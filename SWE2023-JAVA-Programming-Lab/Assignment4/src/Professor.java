
public class Professor extends Staff {

	public int nResearches;
	public String mainCourse;
	
	public Professor(String fullname, int age, double salary, String department,
			int nResearches, String mainCourse) { // constructor(String, int, double, String, int ,String)
		super(fullname, age, salary, department); // call super class's constructor, parameter: String fullname, int age, double salary, String department
		// use set functions of instance variable
		this.setnResearches(nResearches);
		this.setMainCourse(mainCourse);
	}
	
	// get&set functions of nResearches
	public int getnResearches() {
		return nResearches;
	}
	public void setnResearches(int nResearches) {
		this.nResearches = nResearches;
	}
	// get&set functions of mainCourse
	public String getMainCourse() {
		return mainCourse;
	}
	public void setMainCourse(String mainCourse) {
		this.mainCourse = mainCourse;
	}

	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}
	
	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nNumber of Researches: " + this.getnResearches() // Number of Researches: nResearches
				+ "\nMain Course: " + this.getMainCourse(); // Main Course: mainCourse
	}
	
}
