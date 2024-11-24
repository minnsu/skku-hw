
public class Bus extends PublicTransport {
	
	public int nStations;
	public double farePerStation;
	
	public Bus(String model, int nStations, double farePerStation) { // constructor(String, int, double)
		super(model); // call super class's constructor, parameter: String model
		// use set functions of instance variable
		this.setnStations(nStations);
		this.setFarePerStation(farePerStation);
	}
	
	// get&set functions of nStations
	public int getnStations() {
		return nStations;
	}
	public void setnStations(int nStations) {
		this.nStations = nStations;
	}
	// get&set functions of farePerStation
	public double getFarePerStation() {
		return farePerStation;
	}
	public void setFarePerStation(double farePerStation) {
		this.farePerStation = farePerStation;
	}

	@Override
	public double calculatePayment() {
		return this.getnStations() * this.getFarePerStation();
	}
	
	public void getDetail() {
		System.out.println("========================="); // '=' * 25
		System.out.println("Transport type: Bus");
		System.out.println(this);
	}

	@Override
	public String toString() {
		return super.toString() // call super class's toString method
				+ "\nFare per stations: " + this.getFarePerStation() // Fare per stations: farePerStation
				+ "\nNumber of stations: " + this.getnStations() // Number of stations: nStations
				+ "\nTotal Fare: " + this.calculatePayment(); // Total Fare: nStations * farePerStation
	}
	
}
