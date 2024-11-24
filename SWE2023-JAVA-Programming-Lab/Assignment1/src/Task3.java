import java.util.Scanner;
import java.util.Random;
public class Task3{
	
	public static int RandomInt() {
		Random rangen = new Random();
		int randomint = rangen.nextInt(9) + 1; // positive one-digit integer : 1 ~ 9 => 0 ~ 8 + 1
		return randomint;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in); // for input answer
		int NoCA = 0; // Number of correct answers
		for(int i = 1; i <= 5; i++) {
			int randomint = RandomInt(); // Random integer generate
			System.out.printf("Question %d: Square of %d: ", i, randomint); // print
			int answer = input.nextInt(); // input
			if(answer == randomint*randomint) { // if answer is correct, then add 1 to NoCA
				NoCA = NoCA + 1;
			}
		}
		input.close(); // Scanner close
		
		System.out.printf("Number of correct answers: %d\n", NoCA); // print NoCA
		switch(NoCA) { // print different feedback using switch
		case 0:
			System.out.print("Try again.");
			break;
		case 1:
			System.out.print("Very bad.");
			break;
		case 2:
			System.out.print("Not Bad.");
			break;
		case 3:
			System.out.print("Good.");
			break;
		case 4:
			System.out.print("Very good!");
			break;
		case 5:
			System.out.print("Excellent!");
			break;
		}
	}

}
