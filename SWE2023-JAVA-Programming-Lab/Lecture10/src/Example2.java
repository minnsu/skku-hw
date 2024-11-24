
public class Example2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		task1 object = new task1();
		object.start();
	}

}

class task1 extends Thread{
	@Override
	public void run(){
		System.out.print("Task1");
	}
}