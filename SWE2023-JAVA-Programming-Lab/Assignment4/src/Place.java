
public class Place {
	
	public String title;
	public int nRooms;
	public String location;
	
	public Place(String title, int nRooms, String location) { // constructor(String, int, String)
		// use set functions of instance variable
		this.setTitle(title);
		this.setnRooms(nRooms);
		this.setLocation(location);
	}
	// get&set functions of title
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	// get&set functions of nRooms
	public int getnRooms() {
		return nRooms;
	}
	public void setnRooms(int nRooms) {
		this.nRooms = nRooms;
	}
	// get&set functions of location
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}

	@Override
	public String toString() {
		return String.format("%s %s\n%s %d\n%s %s"
			, "Place:", this.getTitle() // Place: title
			, "Number of rooms:", this.getnRooms() // Number of rooms: nRooms
			, "Location:", this.getLocation()); // Location: location
	}
}
