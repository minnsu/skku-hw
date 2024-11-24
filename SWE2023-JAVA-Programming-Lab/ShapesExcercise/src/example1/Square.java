package example1;

public class Square extends Rectangle{

	static final String CLASS_NAME = "Square";
	
	public Square(String name, double side) {
		super(name, side, side);
	}
	
	public static String getClassName() {
		return CLASS_NAME;
	}
	
	public double getSide() {
		return super.getDimension1();
	}
	public void setSide(double side) {
//		super.setDimension1(side);
//		super.setDimension2(side);
		
//		super.setWidth(side);
//		super.setHeight(side);
		
		super.setSize(side, side);
	}
	
	@Override
	public double getArea() {
//		return super.getWidth() * super.getHeight();
//		return super.getDimension1() * super.getDimension2();
//		return Math.pow(super.getDimension1(), 2);
		return super.getArea();
	}
	
	@Override
	public String toString() {
		return "Square [Side= " + this.getSide() + "]";
	}
	
}
