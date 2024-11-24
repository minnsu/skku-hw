import java.io.IOException;

class testexception extends Exception{}
class testexception0 extends testexception{}
class testexception1 extends testexception0{}
class testexception2 extends testexception0{}
public class ExceptionExample {

	public static void main(String[] args) {

		try {
			int x = 7;
			
			if (x == 5){
				throw  new testexception1();
			}else
				throw  new testexception2();
		} catch ( testexception0 e) {
			int y = 7;
			System.out.println("y = " + y);
		} 
	}

}
