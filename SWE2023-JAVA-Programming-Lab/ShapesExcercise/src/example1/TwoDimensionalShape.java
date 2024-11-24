package example1;

public abstract class TwoDimensionalShape {

	static final String CLASS_NAME = "2D Shape";
	private String name;
	private double dimension1;
	private double dimension2;
	public TwoDimensionalShape(String name, double dimension1, double dimension2) {
		super();
		this.setName(name);
		this.setDimension1(dimension1);
		this.setDimension2(dimension2);
	}
	public static String getClassName() {
		return CLASS_NAME;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public double getDimension1() {
		return dimension1;
	}
	public void setDimension1(double dimension1) {
		this.dimension1 = dimension1;
	}
	public double getDimension2() {
		return dimension2;
	}
	public void setDimension2(double dimension2) {
		this.dimension2 = dimension2;
	}
	
	@Override
	public String toString() {
		return "TwoDimensionalShape [name=" + name + ", dimension1=" + dimension1 + ", dimension2=" + dimension2 + "]";
	}
	
	public abstract double getArea();

	
}
