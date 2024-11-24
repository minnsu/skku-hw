
import java.util.Scanner;

public class Undergraduate extends Student {

	private String javaGrade;
	private int javaCredits;
	private String dataStructureGrade;
	private int dataStructureCredits;
	private String algorithmGrade;
	private int algorithmCredits;
	private float gpa;
	
	// get, set functions of javaGrade, javaCredits
	public String getJavaGrade() {
		return javaGrade;
	}
	public void setJavaGrade(String javaGrade) {
		this.javaGrade = javaGrade;
	}
	public int getJavaCredits() {
		return javaCredits;
	}
	public void setJavaCredits(int javaCredits) {
		this.javaCredits = javaCredits;
	}
	// get, set functions of dataStructureGrade, dataStructureCredits
	public String getDataStructureGrade() {
		return dataStructureGrade;
	}
	public void setDataStructureGrade(String dataStructureGrade) {
		this.dataStructureGrade = dataStructureGrade;
	}
	public int getDataStructureCredits() {
		return dataStructureCredits;
	}
	public void setDataStructureCredits(int dataStructureCredits) {
		this.dataStructureCredits = dataStructureCredits;
	}
	// get, set functions of algorithmGrade, algorithmCredits
	public String getAlgorithmGrade() {
		return algorithmGrade;
	}
	public void setAlgorithmGrade(String algorithmGrade) {
		this.algorithmGrade = algorithmGrade;
	}
	public int getAlgorithmCredits() {
		return algorithmCredits;
	}
	public void setAlgorithmCredits(int algorithmCredits) {
		this.algorithmCredits = algorithmCredits;
	}
	// get, set functions of gpa
	public float getGpa() {
		return gpa;
	}
	public void setGpa(float gpa) {
		this.gpa = gpa;
	}
	
	@Override
	public void register() {
		System.out.printf("=================================\nRegister (Undergraduate):\n"); // = * 33
		super.register();
	}
	@Override
	public boolean login() {
		return super.login();
	}
	
	@Override
	public void getGrades() {
		Scanner input = new Scanner(System.in);
		
		// get JAVA Programming Grade and Credits
		System.out.printf("Grade from JAVA Programming: ");
		String javaGrade = input.nextLine();
		System.out.printf("Credits from JAVA Programming: ");
		int javaCredits = input.nextInt();
		this.setJavaGrade(javaGrade);
		this.setJavaCredits(javaCredits);
		input.nextLine(); // clean buffer
		
		// get Data Structure Grade and Credits
		System.out.printf("Grade from Data Structure: ");
		String dataStructureGrade = input.nextLine();
		System.out.printf("Credits from Data Structure: ");
		int dataStructureCredits = input.nextInt();
		this.setDataStructureGrade(dataStructureGrade);
		this.setDataStructureCredits(dataStructureCredits);
		input.nextLine(); // clean buffer
		
		// get Algorithms Grade and Credits
		System.out.printf("Grade from Algorithms: ");
		String algorithmGrade = input.nextLine();
		System.out.printf("Credits from Algorithms: "); // Algorithms? Algorithm?
		int algorithmCredits = input.nextInt();
		this.setAlgorithmGrade(algorithmGrade);
		this.setAlgorithmCredits(algorithmCredits);
		input.nextLine(); // clean buffer
	}

	@Override
	public void calculateGPA(String Grade, int Credits) {
		float tmp = 0;
		// check Grade using equals
		// tmp = present gpa + GradeScore * Credits
		// set gpa as tmp
		if(Grade.equals("A+")) {
			tmp = (float) (this.getGpa() + 4.5 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("A") || Grade.equals("A0")) {
			tmp = (float) (this.getGpa() + 4.0 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("B+")) {
			tmp = (float) (this.getGpa() + 3.5 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("B") || Grade.equals("B0")) {
			tmp = (float) (this.getGpa() + 3.0 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("C+")) {
			tmp = (float) (this.getGpa() + 2.5 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("C") || Grade.equals("C0")) {
			tmp = (float) (this.getGpa() + 2.0 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("D+")) {
			tmp = (float) (this.getGpa() + 1.5 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("D") || Grade.equals("D0")) {
			tmp = (float) (this.getGpa() + 1.0 * Credits);
			this.setGpa(tmp);
		}
		else if(Grade.equals("F")) {
			tmp = (float) (this.getGpa() + 0);
			this.setGpa(tmp);
		}
	}

	@Override
	public void scholarship() {
		this.setGpa(0);
		this.calculateGPA(this.getJavaGrade(), this.getJavaCredits());
		this.calculateGPA(this.getDataStructureGrade(), this.getDataStructureCredits());
		this.calculateGPA(this.getAlgorithmGrade(), this.getAlgorithmCredits());
		// gpa in this line is sum of every course's grade, therefore we should divide with sum of Credits
		this.setGpa(this.getGpa() / (this.getJavaCredits() + this.getDataStructureCredits() + this.getAlgorithmCredits()));
		
		System.out.printf("=================================\n"); // = * 33
		System.out.printf("Student: %s\n", super.getFullname());
		System.out.printf("Your GPA: %.2f\n", this.getGpa());
		
		// check gpa and print scholarship status
		if(this.getGpa() >= 4.0) {
			// gpa >= 4.0 -> 100% scholarship
			System.out.println("Congratulations! You got 100% scholarship");
		}
		else if(this.getGpa() >= 3.5 && this.getGpa() < 4.0) {
			// 4.0 > gpa >= 3.5 -> 50% scholarship
			System.out.println("Congratulations! You got 50% scholarship.");
		}
		else {
			// 3.5 > gpa -> No scholarship
			System.out.println("You did not get scholarship");
		}
	}

}
