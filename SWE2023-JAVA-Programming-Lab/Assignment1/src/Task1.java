import java.util.Scanner;

public class Task1{

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in); // for input Radius and Height
		
		System.out.print("Radius (cm): ");
		double rad = input.nextDouble(); // input : Radius
		System.out.print("Height (cm): ");
		double hei = input.nextDouble(); // input : Height
		
		float PI = 3.14f; // set PI value = 3.14f
		
		System.out.printf("Volume of the cylinder: %.1f", PI*rad*rad*hei); 
		// print Volume of cylinder : PI * radius^2 * height
		input.close(); // Scanner close
	}

}
