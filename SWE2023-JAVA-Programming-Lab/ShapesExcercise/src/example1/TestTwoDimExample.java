package example1;

public class TestTwoDimExample {
	public static void main(String[] args) {

		TwoDimensionalShape array[] = new TwoDimensionalShape[3];
		array[0] = new Circle("CirObject", 3.0);
		array[1] = new Rectangle("RecObject", 3.5, 4.5);
		array[2] = new Square("SquObject", 4.0);
		
		for(int i = 0; i < array.length; i++) {
			System.out.println(array[i]);
			System.out.println(array[i].getArea());
		}			
	}
}