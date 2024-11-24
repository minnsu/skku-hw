import java.util.LinkedList;
// generic class
public class Student<T1 extends Number, T2, T3 extends Number>{
	private T1 StudentID;
	private T2 StudentName;
	private T3 StudentSSN;
	
	public Student() {
		this.StudentID = null;
	}
	public Student(T1 S, T2 Name, T3 SSN){
		this.StudentID = S;
		this.StudentName = Name;
		this.StudentSSN = SSN;
	}
	
	public T1 getStudentID() {
		return StudentID;
	}
	public void setStudentID(T1 studentID) {
		StudentID = studentID;
	}
	public T2 getStudentName() {
		return StudentName;
	}
	public void setStudentName(T2 studentName) {
		StudentName = studentName;
	}
	public T3 getStudentSSN() {
		return StudentSSN;
	}
	public void setStudentSSN(T3 studentSSN) {
		StudentSSN = studentSSN;
	}
	@Override
	public String toString() {
		return "Student\n[ StudentID= " + StudentID + "\n  StudentName= " + StudentName + "\n  StudentSSN= " + StudentSSN + " ]";
	}
	
	public static <T> /* generic 나타냄 */ T /*return type*/ method(T variable) {
		// generic class의 class와는 상관없이 독립적으로 method에서 받아온 T만 사용됨.
		return variable;
	}
}

// generic method only
class Calc{
	
	int var1;
	int var2;
	public Calc() {
		
	}
	
	public static <T> /* generic 나타냄 */ T /*return type*/ method(T variable) {
		return variable;
	}
}

class Test{
	public static void main(String[] args) {
//		LinkedList<Integer> list = new LinkedList<Integer>();
//		Student<Integer> student1 = new Student<Integer>(1234);
//		Student<String> student2 = new Student<String>("abcd");
//		
//		student1.setStudentID(12345678);
//		System.out.println(student1.getStudentID());
//		student2.setStudentID("123456EA");
//		System.out.println(student2.getStudentID());
		
//		// Array of generic Student class
//		Student<Integer>[] array = new Student[100];
		
		// many type of class
//		Student<Integer, String, Integer> student3 = new Student<Integer, String, Integer>(123, "Minsu", 456);
//		System.out.println(student3);
		
//		Student student3 = new Student<Admin, String, Integer>(new Admin(), "Minsu", 456);
//		Student student4 = new Student<Employee, String, Float>(new Employee(), "", 0.4F);
		
//		Student<Person, String, Integer> arr[] = new Student[100];
//		arr[1] = new Student<Person, String, Integer>(new Admin(), "hello", 123); // polymorphism
//		arr[2] = new Student<Person, String, Integer>(new Employee(), "world", 345);
		
		// generic method
		Student st6 = new Student<Integer, String, Integer>(1, "", 2);
		System.out.println(st6);
	}
}
