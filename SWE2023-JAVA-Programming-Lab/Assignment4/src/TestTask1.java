
public class TestTask1 {

	public static void main(String[] args) {
		// make object with initial values of instance
		Company company = new Company("Samsung Electronics",
				100, "Seoul", 2000, 1000000.00, 20); // Samsung's Income is what???
		University university = new University("SKKU",
				200, "Suwon", 89, 100000, 2000);
		
		System.out.println(company);
		System.out.println("========================"); // how many of '='?
		System.out.println(university);
		
	}

}
