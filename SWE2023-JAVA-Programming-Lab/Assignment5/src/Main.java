
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int iter = 3;
		String recalculate;
		
		while (iter != 0) {
			recalculate = "Y"; // initial value of recalculate loop as Y(Yes)
			System.out.println("==========================================================================="); // = * 75
			System.out.printf("Student degree (Enter 1 for Undergraduate, 2 for Graduate, 0 for Cancel): ");
			iter = input.nextInt();
			input.nextLine(); // clean buffer
			switch (iter) {
			case 1:
				Student undergraduate = new Undergraduate(); // upcasting Undergraduate -> Student
				undergraduate.register(); // register
				while (!undergraduate.login()) {} // return value of login() is boolean: until Success
				while (recalculate.equals("Y")) {
					undergraduate.getGrades(); // enter Grade and Credits
					undergraduate.scholarship(); // print GPA and scholarship status
					System.out.printf("=================================\n"); // = * 33
					System.out.printf("Do you want to calculate again(Y/N): ");
					recalculate = input.nextLine();
				}
				break;
			case 2:
				Student graduate = new Graduate(); // upcasting Undergraduate -> Student
				graduate.register(); // register
				while (!graduate.login()) {} // return value of login() is boolean: until Success
				while (recalculate.equals("Y")) {
					graduate.getGrades(); // enter Grade and Credits
					graduate.scholarship(); // print GPA and scholarship status
					System.out.printf("=================================\n"); // = * 33
					System.out.printf("Do you want to calculate again(Y/N): ");
					recalculate = input.nextLine();
				}
				break;
			default:
				// Wrong input
			}
		}
		System.out.println("Thank for using our system!");
	}

}
