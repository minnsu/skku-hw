
public class example {
	static void RunMethod(int a, int b) {
		System.out.println("Executed RunMethod .. ");
		
		System.out.println("Finished RunMethod .. ");
	}
	public static void main(String[] args) {
		int variable1 = 10;
		double variable2 = 2.5;
		float variable3 = 2.4f;
		long variable4 = 2;
		boolean variable5 = true;
		String string1 = "Hello, welcome to ";
		String string2 = "Java programming";
		String string3 = string1 + string2;
//		System.out.println(variable1 + " " + variable2 + " " + variable3);
//		System.out.println(variable4 + " " + variable5 + " " + string3);
		
		int [] array1 = new int [10];
		int array2[] = new int [10];
		int [][] array3 = {{1,2,3,4}, {5,6,7,8}};
		int array4 [][] = new int [10][5];
		System.out.println(array1[5]);
		System.out.println(array2[9]);
		System.out.println(array3[0][2]);
		
		example object = new example();
		object.RunMethod(10, 20);
	}

}