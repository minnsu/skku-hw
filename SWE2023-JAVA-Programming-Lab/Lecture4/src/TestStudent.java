public class TestStudent {

	public static void main(String[] args) {
		StudentData.SetCollege("Econmics");
		
		StudentData student1 = new StudentData("Tamer", 123456,30);
//		student1.SetCollege("Computing");
		
		StudentData student2 = new StudentData("Kim YoungJae", 452457,22);
//		student2.SetCollege("Physics");
		
		System.out.println(student1);
		System.out.println(student2);
		//System.out.println(student1.getStudentID());
		//System.out.println(student1.getStudentAge());
	}
}