package Example1AbstractClasses;

public class HourlyEmployee extends Employee {
	private double wage; // wage per hour
	private double hours; // hours worked for week

	// five-argument constructor
	public HourlyEmployee(String first, String last, String ssn, double hourlyWage, double hoursWorked) {
		super(first, last, ssn);
		setWage(hourlyWage);
		setHours(hoursWorked);
	} // end five-argument HourlyEmployee constructor

	// set wage
	public void setWage(double hourlyWage) {
		if (hourlyWage >= 0.0)
			wage = hourlyWage;
		else
			throw new IllegalArgumentException("Hourly wage must be >= 0.0");
	} // end method setWage

	public double getWage() {
		return wage;
	} // end method getWage

	// set hours worked
	public void setHours(double hoursWorked) {
		if ((hoursWorked >= 0.0) && (hoursWorked <= 168.0))
			hours = hoursWorked;
		else
			throw new IllegalArgumentException("Hours worked must be >= 0.0 and <= 168.0");
	} // end method setHours

	// return hours worked
	public double getHours() {
		return hours;
	} // end method getHours

	// return String representation of HourlyEmployee object
	@Override
	public String toString() {
		return String.format("hourly employee: %s\n%s: $%,.2f; %s: %,.2f", super.toString(), "hourly wage", getWage(),
				"hours worked", getHours());
	} // end method toString

	@Override
	public double earnings() {

		if (getHours() <= 40) // no overtime
			return getWage() * getHours();
		else
			return 40 * getWage() + (getHours() - 40) * getWage() * 1.5;

	}
} // end class HourlyEmployee
