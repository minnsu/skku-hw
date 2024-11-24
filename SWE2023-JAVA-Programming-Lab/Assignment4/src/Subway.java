
public class Subway extends PublicTransport {

	public double oneTimePayment;

	public Subway(String model, double oneTimePayment) { // constructor(String, double)
		super(model); // call super class's constructor, parameter: String model
		// use set functions of instance variable
		this.setOneTimePayment(oneTimePayment);
	}
	
	// get&set functions of oneTimePayment	
	public double getOneTimePayment() {
		return oneTimePayment;
	}
	public void setOneTimePayment(double oneTimePayment) {
		this.oneTimePayment = oneTimePayment;
	}

	@Override
	public double calculatePayment() {
		return this.getOneTimePayment();
	}
	
	public void getDetail() {
		System.out.println("========================="); // '=' * 25
		System.out.println("Transport type: Subway");
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nOne-time Payment: " + this.getOneTimePayment() // One-time Payment: oneTimePayment
				+ "\nTotal Fare: " + this.calculatePayment(); // Total Fare: oneTimePayment
	}
	
}
