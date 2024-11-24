class Counter {
	int count;

	public synchronized void incr() {
		count++;
	}
}

public class Main {
	public static void main(String[] args) throws InterruptedException {

		Counter c = new Counter();

		Thread t1 = new Thread(new Runnable() {
			public void run() {
				for (int i = 0; i < 1000; i++)
					c.incr();
			}
		});

		Thread t2 = new Thread(new Runnable() {
			public void run() {
				for (int i = 0; i < 1000; i++)
					c.incr();
			}
		});

		t1.start();
		t2.start();

		t1.join();
		t2.join();

		System.out.println("Count = " + c.count);
	}
}
