
public class Cab extends PublicTransport {
	
	public double baseFare;
	public double farePerKm;
	public double distance;
	
	public Cab(String model, double baseFare, double farePerKm, double distance) { // constructor(String, double, double, double)
		super(model); // call super class's constructor, parameter: String model
		// use set functions of instance variable
		this.setBaseFare(baseFare);
		this.setFarePerKm(farePerKm);
		this.setDistance(distance);
	}
	
	// get&set functions of baseFare
	public double getBaseFare() {
		return baseFare;
	}
	public void setBaseFare(double baseFare) {
		this.baseFare = baseFare;
	}
	// get&set functions of farePerKm
	public double getFarePerKm() {
		return farePerKm;
	}
	public void setFarePerKm(double farePerKm) {
		this.farePerKm = farePerKm;
	}
	// get&set functions of distance
	public double getDistance() {
		return distance;
	}
	public void setDistance(double distance) {
		this.distance = distance;
	}

	@Override
	public double calculatePayment() {
		return this.getBaseFare() + (this.getDistance() * this.getFarePerKm());
	}
	
	public void getDetail() {
		System.out.println("========================="); // '=' * 25
		System.out.println("Transport type: Cab");
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method 
				+ "\nBase Fare: " + this.getBaseFare() // Base Fare: baseFare
				+ "\nFare per km: " + this.getFarePerKm() // Fare per km: farePerKm
				+ "\nDistance: " + this.getDistance() // Distance: distance
				+ "\nTotal Fare: " + this.calculatePayment(); // Total Fare: baseFare + (distance * farePerKm)
	}
	
}
