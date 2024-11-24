public class Program {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Ball football = new Ball("black");
		
		System.out.println(football.color);
		System.out.println(football.size);
		System.out.println(football.shape);
		
		
		football.Set_Ball_Color("Black");
		football.Set_Ball_Shape("somthing");
		
		Ball tennis = new Ball();
		
		tennis.color = "yellow";
		tennis.shape = "circle";
		tennis.size = 9.12f;
		
	}
}