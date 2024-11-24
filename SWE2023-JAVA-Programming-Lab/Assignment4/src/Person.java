
public class Person {
	
	public String fullname;
	public int age;
	
	public Person(String fullname, int age) { // constructor(String, int)
		// use set functions of instance variable
		this.setFullname(fullname);
		this.setAge(age);
	}
	
	// get&set functions of fullname
	public String getFullname() {
		return fullname;
	}
	public void setFullname(String fullname) {
		this.fullname = fullname;
	}
	// get&set functions of Age
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}

	public void getDetail() {
		System.out.println("==========================="); // '=' * 27
		System.out.println(this);
	}

	@Override
	public String toString() {
		return "Full name: " + this.getFullname() // Full name: fullname
			+ "\nAge: " + this.getAge(); // Age: age
	}
	
}
