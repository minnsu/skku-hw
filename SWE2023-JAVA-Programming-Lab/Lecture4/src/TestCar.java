import com.examples.lecture4.Car;

public class TestCar {
	public static void main(String[] args) {
		Car KiaCar = new Car("KIA", 2020, 2000, 12543258);
		
		System.out.println(KiaCar.getMaker());
		System.out.println(KiaCar.getYear());
		System.out.println(KiaCar.getCarEngine());
	}
}