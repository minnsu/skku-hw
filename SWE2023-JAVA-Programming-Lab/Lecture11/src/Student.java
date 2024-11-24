import java.io.Serializable;

public class Student implements Serializable {
	private String Name;
	private String SSN;
	private int age;
	public Student(String name, String sSN, int age) {
		super();
		Name = name;
		SSN = sSN;
		this.age = age;
	}
	public String getName() {
		return Name;
	}
	public void setName(String name) {
		Name = name;
	}
	public String getSSN() {
		return SSN;
	}
	public void setSSN(String sSN) {
		SSN = sSN;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	
	
}
