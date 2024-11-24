
public class University extends Place {
	
	public int rank;
	public int nStudents;
	public int nTeachers;
	
	public University(String title, int nRooms, String location,
			int rank, int nStudents, int nTeachers) { // constructor(String, int, String, int, int, int)
		super(title, nRooms, location); // call super class's constructor, paramter: String title, int nRooms, String location
		// use set functions of instance variable
		this.setRank(rank);
		this.setnStudents(nStudents);
		this.setnTeachers(nTeachers);
	}
	// get&set functions of rank
	public int getRank() {
		return rank;
	}
	public void setRank(int rank) {
		this.rank = rank;
	}
	// get&set functions of nStudents
	public int getnStudents() {
		return nStudents;
	}
	public void setnStudents(int nStudents) {
		this.nStudents = nStudents;
	}
	// get&set functions of nTeachers
	public int getnTeachers() {
		return nTeachers;
	}
	public void setnTeachers(int nTeachers) {
		this.nTeachers = nTeachers;
	}
	
	
	@Override
	public String toString() {
		return String.format("%s %s\n%s %d\n%s %s\n%s %d\n%s %d\n%s %d"
			, "University:", this.getTitle() // University: title
			, "Number of rooms:", this.getnRooms() // Number of rooms: nRooms
			, "Location:", this.getLocation() // Location: location
			, "Rank:", this.getRank() // Rank: rank
			, "Number of Students:", this.getnStudents() // Number of Students: nStudents
			, "Number of Teachers:", this.getnTeachers()); // Number of Teachers: nTeachers
	}
		
}
