package Example1AbstractClasses;

public class PolymorphismTest {
	public static void main(String[] args) {

		// create four-element Employee array
		Employee[] employees = new Employee[4];

		// Employee xx = new SalariedEmployee("", "", "", 1222);
		// initialize array with Employees
		employees[0] = new SalariedEmployee("John", "Smith", "111-11-1111", 800.00);
		employees[1] = new HourlyEmployee("Karen", "Price", "222-22-2222", 16.75, 40);
		employees[2] = new CommissionEmployee("Sue", "Jones", "333-33-3333", 10000, .06);

		employees[3] = new BasePlusCommissionEmployee("Bob", "Lewis", "444-44-4444", 5000, .04, 300);
		System.out.println("Employees processed polymorphically:\n");

		for (Employee currentEmployee : employees) {
			System.out.println(currentEmployee); // invokes toString
			System.out.printf("earned $%,.2f\n\n", currentEmployee.earnings());
		} // end for

	} // end main

} // end class PayrollSystemTest
