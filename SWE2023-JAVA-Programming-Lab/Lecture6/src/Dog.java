
public class Dog implements Animal, Draw{
	private String type;
	private int age;
	
	public void print() {
		System.out.println("print info of Dog class");

	}
	public void method() {
		 

	}
	@Override
	public String toString() {
		 
		return "dog class toString";
	}
	@Override
	public void SetName(String Name) {	
		
		
	}
	@Override
	public void DrawAnimal() {
		// TODO Auto-generated method stub
		
	}
	
}

class PetDog extends Dog{
	private String owner;
	private String FoodType;
	@Override
	public String toString() {
		 
		return "PetDog class toString";
	}
	
}

class PoliceDog extends PetDog{
	
	private String PoliceID;
	@Override
	public String toString() {
		 
		return "PoliceDog class toString";
	}
	
	public void method() {
		System.out.println("Method of PoliceDog class");

	}
}
