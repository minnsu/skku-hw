package example1;

public class Circle extends TwoDimensionalShape{
	
	static final String CLASS_NAME = "Circle";
	
	public Circle(String name, double radius) {
		super(name, radius, radius);
	}

	public static String getClassName() {
		return CLASS_NAME;
	}
	
	public double getRadius() {
		return super.getDimension1();
	}
	public void setRadius(double radius) {
		super.setDimension1(radius);
		super.setDimension2(radius);
	}
	
	public double getDiameter() {
		return this.getRadius() * 2;
	}
	public void setDiameter(double diameter) {
		this.setRadius(diameter/2);
		this.setRadius(diameter/2);
	}
	
	@Override
	public double getArea() {
//		return Math.PI * super.getDimension1() * super.getDimension1();
		return Math.PI * Math.pow(super.getDimension1(), 2);
	}

	@Override
	public String toString() {
		return "Circle [Radius=" + this.getRadius() + "]";
	}

}