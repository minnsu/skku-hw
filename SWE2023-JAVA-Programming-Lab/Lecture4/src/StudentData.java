public class StudentData {

	private String StudentName;
	private int StudentID;
	private int StudentAge;
	private static String college = "";
	
	public static void SetCollege(String College) {
		college = College;
	}
	
	public StudentData() {
//		this.StudentName = "None";
//		this.StudentID = 1000;
//		this.StudentAge = 0;
		this.setStudentName("None");
		this.setStudentID(1000);
		this.setStudentAge(0);
	}
	public StudentData(String StudentName, int StudentID, int StudentAge) {
//		this.StudentName = StudentName;
		this.setStudentName(StudentName);
//		this.StudentID = StudentID;
		this.setStudentID(StudentID);
//		this.StudentAge = StudentAge;
		this.setStudentAge(StudentAge);
	}
	public StudentData(String StudentName, int StudentAge) {
//		this.StudentName = StudentName;
		this.setStudentName(StudentName);
//		this.StudentAge = 0;
		this.setStudentID(0);
//		this.StudentAge = StudentAge;
		this.setStudentAge(StudentAge);
	}

	public String getStudentName() {
		return StudentName;
	}
	public void setStudentName(String studentName) {
		StudentName = studentName;
	}

	public int getStudentID() {
		return StudentID;
	}
	public void setStudentID(int studentID) {
		StudentID = studentID;
	}


	public int getStudentAge() {
		return StudentAge;
	}
	public void setStudentAge(int StudentAge) {
		if(StudentAge >= 0) {
			this.StudentAge = StudentAge;
		}
		else {
			System.out.println("Error, you cannot assign negative value");
		}
	}
		
	// create toString method
	public String toString() {
		String info = "";
		info = info + this.StudentName + "  \n"
				    + this.StudentID + " \n " + 
				    + this.StudentAge + "\n" +
				    college +  "\n" +
				    "This info is from toString() method";
		return info;
	}
}