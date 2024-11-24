import java.util.Scanner;

public class Task2{

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in); // for input
		
		System.out.print("Payment for one hour ($): ");
		int PH = input.nextInt(); // input : Payment for one hour
		System.out.print("Payment for one extra hour ($): ");
		int PEH = input.nextInt(); // input : Payment for one extra hour
		System.out.print("Number of hours: ");
		int NoH = input.nextInt(); // input : Number of hours
		
		int RP = (NoH >= 40) ? PH * 40 : PH * NoH; 
		// if Number of hours greater of equal than 40, Regular Payment is PH * 40
		// else, PH * NoH
		int EP = (NoH >= 40) ? PEH * (NoH - 40) : 0;
		// if Number of hours greater of equal than 40, Extra Payment is PEH * (NoH - 40)
		// else, No Extra Payment
		
		System.out.printf("Payment for regular hours ($): %d\n", RP); // print Regular Payment
		System.out.printf("Payment for extra hours($): %d\n", EP); // print Extra Payment
		System.out.printf("Total payment ($): %d", RP + EP); // print Total Payment = Regular Payment + Extra Payment
		
		input.close(); // Scanner close
	}

}
