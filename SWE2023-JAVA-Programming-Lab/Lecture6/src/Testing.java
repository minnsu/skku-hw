
public class Testing {
	public static void main(String[] args) {
		Dog dog1 = new Dog(); //upcasting 
		Dog dog2, dog3, dog4 ;
		
		int a = (int) 3.2; // casting
		dog2 =  new PoliceDog();  //upcasting 
		
		dog2.print();
		dog2.method(); 
		System.out.println(dog2.toString());
		
		dog3 = (Dog) new PetDog(); //upcasting 
		
		dog4 = dog3; // upcasting 
		
		// Dog dogobj = new Dog();
		
		// PoliceDog dog5 = (PoliceDog) dogobj;  //invalide downcasting
		
		Dog dog5 = new PoliceDog();
		
		PoliceDog dog6 = (PoliceDog)dog5; //valide downcasting
		dog6.method();
	}
}