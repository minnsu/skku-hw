
public class TestTask3 {

	public static void main(String[] args) {
		PublicTransport cab = new Cab("BMW", 10, 5.0, 7.0);
		PublicTransport bus = new Bus("Mercedes-Benz", 10, 1.5);
		PublicTransport subway = new Subway("Shinkansen", 80);
		
		cab.getDetail();
		bus.getDetail();
		subway.getDetail();
	}
	
}
