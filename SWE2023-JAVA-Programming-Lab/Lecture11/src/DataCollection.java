import java.io.Serializable;


public class DataCollection implements Serializable{

 int x;
 int y;
 
 DataCollection(int xpoint, int ypoint){
	 x=xpoint;
	 y=ypoint;
 }
public void setX(int x) {
	this.x = x;
}
public void setY(int y) {
	this.y = y;
}
public int getX() {
	return x;
}
public int getY() {
	return y;
}
@Override
	public String toString() {
		return super.toString();
	}

}
