
public class Company extends Place {
	
	public int nEmployees;
	public double annualIncome;
	public int nDepartments;
	
	public Company(String title, int nRooms, String location,
			int nEmployees, double annualIncome, int nDepartments) { // constructor(String, int, String, int, double, int)
		super(title, nRooms, location); // call super class's constructor, paramter: String title, int nRooms, String location
		// use set functions of instance variable
		this.setnEmployees(nEmployees); 
		this.setAnnuallncome(annualIncome);
		this.setnDepartments(nDepartments);
	}
	// get&set functions of nEmployees
	public int getnEmployees() {
		return nEmployees;
	}
	public void setnEmployees(int nEmployees) {
		this.nEmployees = nEmployees;
	}
	// get&set functions of annualIncome
	public double getAnnualIncome() {
		return annualIncome;
	}
	public void setAnnuallncome(double annualIncome) {
		this.annualIncome = annualIncome;
	}
	// get&set functions of nDepartments
	public int getnDepartments() {
		return nDepartments;
	}
	public void setnDepartments(int nDepartments) {
		this.nDepartments = nDepartments;
	}

	@Override
	public String toString() {
		return String.format("%s %s\n%s %d\n%s %s\n%s %d\n%s %.2f\n%s %d"
			, "Company:", this.getTitle() // Company: title
			, "Number of rooms:", this.getnRooms() // Number of rooms: nRooms
			, "Location:", this.getLocation() // Location: location
			, "Number of Employees:", this.getnEmployees() // Number of Employees: nEmployees
			, "Annual Income:", this.getAnnualIncome() // Annual Income: annualIncome
			, "Number of Department:", this.getnDepartments()); // Number of Department: nDepartments
	}
	
}
