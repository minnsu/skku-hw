public class Rectangle {
	private int height; // the length of the rectangle
	private int width; // the width of the rectangle
	private Point TopLeft;

	// constructor without parameters
	public Rectangle() {
		this(0, 0, 1, 1);
	} // end Rectangle no-argument constructor

	// constructor with length and width supplied
	public Rectangle(int pointX, int pointY, int height, int width) {
		setHeight(height);
		setWidth(width);
		TopLeft = new Point(pointX, pointY);

		System.out.println("Rectangle created\n" + "Hight =" + height + " Width =" + width + "\n" + "Top Point ("
				+ TopLeft.getX() + ", " + TopLeft.getY() + ")\n");
	} // end Rectangle two-argument constructor

	public Rectangle(Point Top, int height, int width) {
		setHeight(height);
		setWidth(width);
		TopLeft = Top;

		System.out.println("Rectangle created\n" + "Hight =" + height + " Width =" + width + "\n" + "Top Point ("
				+ TopLeft.getX() + ", " + TopLeft.getY() + ")\n");
	} // end Rectangle two-argument constructor
	
	// validate and set length
	public void setHeight(int theHeight) {
		if (theHeight > 0.0 && theHeight < 20.0) {
			height = theHeight;
		} else {
			System.out.println("height out of range");
		}
	} // end method setLength

	// validate and set width
	public void setWidth(int theWidth) {
		if (theWidth > 0 && theWidth < 20.0) {
			width = theWidth;
		} else {
			System.out.println("width out of range");
		}

	} // end method setWidth

	// get value of length
	public int getHeight() {
		return this.height;
	} // end method getLength

	// get value of width
	public int getWidth() {
		return this.width;
	} // end method getWidth

	// calculate rectangle's perimeter
	public int getPerimeter() {
		return (2 * height + 2 * width);
	} // end method perimeter

	// calculate rectangle's area
	public int getArea() {
		return this.getHeight() * this.getWidth();
	} // end method area

	public boolean Contain(Point checkPoint) {
		boolean flag = false;
		if( ( checkPoint.getX() > this.TopLeft.getX() 
				&& checkPoint.getX() < this.TopLeft.getX() + this.getWidth() )
				&& ( checkPoint.getY() < this.TopLeft.getY()
				&& checkPoint.getY() > this.TopLeft.getY() - this.getHeight() ) ){
			flag = true;
		}
		return flag;
	}
	
	public Rectangle Intersect(Rectangle secondRectangle) {
		Rectangle intersectRectangle = null;
		
		int xTopLeft;
		int yTopLeft;
		int xBotRight;
		int yBotRight;
		xTopLeft = Math.max(this.TopLeft.getX(), secondRectangle.TopLeft.getX());
		yTopLeft = Math.min(this.TopLeft.getY(), secondRectangle.TopLeft.getY());
		xBotRight = Math.min(this.TopLeft.getX() + this.getWidth(),
				secondRectangle.TopLeft.getX() + secondRectangle.getWidth());
		yBotRight = Math.max(this.TopLeft.getY() - this.getHeight(),
				secondRectangle.TopLeft.getY() - secondRectangle.getHeight());
		if(xTopLeft < xBotRight && yTopLeft > yBotRight) {
			intersectRectangle = new Rectangle(xTopLeft, yTopLeft,
					xBotRight - xTopLeft, yTopLeft - yBotRight);
		}
		return intersectRectangle;
	}
	
	public Rectangle Union(Rectangle secondRectangle) {
		Rectangle intersectRectangle = null;
		
		int xTopLeft;
		int yTopLeft;
		int xBotRight;
		int yBotRight;
		xTopLeft = Math.min(this.TopLeft.getX(), secondRectangle.TopLeft.getX());
		yTopLeft = Math.max(this.TopLeft.getY(), secondRectangle.TopLeft.getY());
		xBotRight = Math.max(this.TopLeft.getX() + this.getWidth(),
				secondRectangle.TopLeft.getX() + secondRectangle.getWidth());
		yBotRight = Math.min(this.TopLeft.getY() - this.getHeight(),
				secondRectangle.TopLeft.getY() - secondRectangle.getHeight());
		intersectRectangle = new Rectangle(xTopLeft, yTopLeft,
				xBotRight - xTopLeft, yTopLeft - yBotRight);
		return intersectRectangle;
	}
	
	// convert to String
	public String toString() {
		return String.format("%s\n%s: %d\n%s: %d\n%s: %d\n%s: %d",
				this.TopLeft.toString(),
				"Height", getHeight(),
				"Width", getWidth(),
				"Perimeter", getPerimeter(),
				"Area", getArea());
	} // end method toString
} // end class Rectangle