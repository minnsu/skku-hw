
public class example3 {
	public static void main(String[] args) {
		ThreadGroup threadGroup = new ThreadGroup("Network Threads");

		Thread t1 = new Thread(threadGroup, new Runnable() {

			@Override
			public void run() {
				System.out.println("network task1");

			}
		});

		Thread t2 = new Thread(threadGroup, new Runnable() {

			@Override
			public void run() {
				System.out.println("network task2");

			}
		});
		t1.start();
		t2.start();
		//stop all threads of the network
		threadGroup.interrupt();
		threadGroup.list();
		
		
	}
}
