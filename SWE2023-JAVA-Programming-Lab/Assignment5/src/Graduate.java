
import java.util.Scanner;

public class Graduate extends Student {
	// instance
	private String mlGrade;
	private int mlCredits;
	private String dataScienceGrade;
	private int dataScienceCredits;
	private String netSecurityGrade;
	private int netSecurityCredits;
	private float gpa;
	private String professorRecommend;
	
	// get, set functions of mlGrade, mlCredits
	public String getMlGrade() {
		return mlGrade;
	}
	public void setMlGrade(String mlGrade) {
		this.mlGrade = mlGrade;
	}
	public int getMlCredits() {
		return mlCredits;
	}
	public void setMlCredits(int mlCredits) {
		this.mlCredits = mlCredits;
	}
	// get, set functions of dataScienceGrade, dataScienceCredits
	public String getDataScienceGrade() {
		return dataScienceGrade;
	}
	public void setDataScienceGrade(String dataScienceGrade) {
		this.dataScienceGrade = dataScienceGrade;
	}
	public int getDataScienceCredits() {
		return dataScienceCredits;
	}
	public void setDataScienceCredits(int dataScienceCredits) {
		this.dataScienceCredits = dataScienceCredits;
	}
	// get, set functions of netSecurityGrade, netSecurityCredits
	public String getNetSecurityGrade() {
		return netSecurityGrade;
	}
	public void setNetSecurityGrade(String netSecurityGrade) {
		this.netSecurityGrade = netSecurityGrade;
	}
	public int getNetSecurityCredits() {
		return netSecurityCredits;
	}
	public void setNetSecurityCredits(int netSecurityCredits) {
		this.netSecurityCredits = netSecurityCredits;
	}
	// get, set functions of gpa
	public float getGpa() {
		return gpa;
	}
	public void setGpa(float gpa) {
		this.gpa = gpa;
	}
	// get, set functions of professorRecommend
	public String getProfessorRecommend() {
		return professorRecommend;
	}
	public void setProfessorRecommend(String professorRecommend) {
		this.professorRecommend = professorRecommend;
	}
	
	@Override
	public void register() {
		System.out.printf("=================================\nRegister (Graduate):\n"); // = * 33
		super.register();
	}
	@Override
	public boolean login() {
		return super.login();
	}
	
	@Override
	public void getGrades() {
		Scanner input = new Scanner(System.in);
		
		// get Machine Learning Grade and Credits
		System.out.printf("Grade from Machine Learning: ");
		String mlGrade = input.nextLine();
		System.out.printf("Credits from Machine Learning: ");
		int mlCredits = input.nextInt();
		this.setMlGrade(mlGrade);
		this.setMlCredits(mlCredits);
		input.nextLine(); // clean buffer
		
		// get Data Science Grade and Credits
		System.out.printf("Grade from Data Science: ");
		String dataScienceGrade = input.nextLine();
		System.out.printf("Credits from Data Science: ");
		int dataScienceCredits = input.nextInt();
		this.setDataScienceGrade(dataScienceGrade);
		this.setDataScienceCredits(dataScienceCredits);
		input.nextLine(); // clean buffer
		
		// get Network Security Grade and Credits
		System.out.printf("Grade from Network Security: ");
		String netSecurityGrade = input.nextLine();
		System.out.printf("Credits from Network Security: ");
		int netSecurityCredits = input.nextInt();
		this.setNetSecurityGrade(netSecurityGrade);
		this.setNetSecurityCredits(netSecurityCredits);
		input.nextLine(); // clean buffer
		
		// get Professor Recommend status
		System.out.println("---------"); // - * 9
		System.out.printf("Did professor recommend you (Y/N): ");
		String professorRecommend = input.nextLine();
		this.setProfessorRecommend(professorRecommend);
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
		this.calculateGPA(this.getMlGrade(), this.getMlCredits());
		this.calculateGPA(this.getDataScienceGrade(), this.getDataScienceCredits());
		this.calculateGPA(this.getNetSecurityGrade(), this.getNetSecurityCredits());
		// gpa in this line is sum of every course's grade, therefore we should divide with sum of Credits
		this.setGpa(this.getGpa() / (this.getMlCredits() + this.getDataScienceCredits() + this.getNetSecurityCredits()));
		
		System.out.printf("=================================\n"); // = * 33
		System.out.printf("Student: %s\n", super.getFullname());
		System.out.printf("Your GPA: %.2f\n", this.getGpa());
		
		// check gpa, professor recommend status and print scholarship status
		if(this.getProfessorRecommend().equals("N")) { // professor recommend status is No -> No scholarship
			System.out.println("You did not get scholarship");
			System.out.println("Reason: Professor did not recommend.");
		}
		else if(this.getGpa() >= 3.8 && this.getProfessorRecommend().equals("Y")) { 
			// gpa >= 3.8 and professor recommend status is Yes -> 100% scholarship
			System.out.println("Congratulations! You got 100% scholarship");
		}
		else if(this.getGpa() >= 3.5 && this.getGpa() < 3.8 && this.getProfessorRecommend().equals("Y")){
			// 3.8 > gpa >= 3.5 and professor recommend status is Yes -> 50% scholarship
			System.out.println("Congratulations! You got 50% scholarship.");
		}
		else if(this.getGpa() < 3.5 && this.getProfessorRecommend().equals("Y")) {
			// 3.5 > gpa and professor recommend status is Yes -> 50% scholarship
			System.out.println("Congratulations! You got 50% scholarship.");
		}
	}

}
