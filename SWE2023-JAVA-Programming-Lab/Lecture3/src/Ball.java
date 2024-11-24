public class Ball {
	String color;
	float size;
	String shape;
	
	public Ball() {
		color = "white";
		size = 0;
		shape = "None";
	}
	public Ball(String c, float s, String si) {
		color = c;
		size = s;
		shape = si;
	}
	public Ball(String c) {
		color = c;
		size = 0;
		shape = "None";
	}
	
	void Set_Ball_Color(String BallColor) {
		color = BallColor;
	}
	void Set_Ball_Size(float BallSize) {
		size = BallSize;
	}
	void Set_Ball_Shape(String BallShape) {
		shape = BallShape;
	}
}