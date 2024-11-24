
public class TestTask2 {

	public static void main(String[] args) {
		// make object with initial values of instance
		Professor professor = new Professor("Frank George", 56, 10000.0, "Computing", 45, "Java");
		Accountant accountant = new Accountant("Jack Sparrow", 25, 2300.0, "International", 305);
		Graduate graduate = new Graduate("Firuz Juraev", 29, "Computing", 16000.0, "Healthcare");
		Undergraduate undergraduate = new Undergraduate("Mike Shinoda", 19, "Computing", 12000.0, "Freshman");

		professor.getDetail();
		accountant.getDetail();
		graduate.getDetail();
		undergraduate.getDetail();
		
	}

}
