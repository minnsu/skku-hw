package example1;

public class Rectangle extends TwoDimensionalShape{

	static final String CLASS_NAME = "Rectangle";
	
	public Rectangle(String name, double width, double height) {
		super(name, width, height);
	}
	
	public static String getClassName() {
		return CLASS_NAME;
	}
	
	public double getWidth() {
		return super.getDimension1();
	}
	public void setWidth(double width) {
		super.setDimension1(width);
	}
	
	public double getHeight() {
		return super.getDimension2();
	}
	public void setHeight(double height) {
		super.setDimension2(height);
	}
	
	public void setSize(double width, double height) {
		super.setDimension1(width);
		super.setDimension2(height);
	}
	
	
	@Override
	public double getArea() {
		return super.getDimension1() * super.getDimension2();
	}

	@Override
	public String toString() {
		return "Rectangle [Width= " + this.getWidth() + ", Height= " + this.getHeight() + "]";
	}
	
}
