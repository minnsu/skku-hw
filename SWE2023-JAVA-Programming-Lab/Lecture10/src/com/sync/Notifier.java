package com.sync;

import java.util.Date;

public class Notifier implements Runnable {

	Message message;

	public Notifier(Message message) {
		this.message = message;
	}

	@Override
	public void run() {
		System.out.println("Notifier is sleeping for 3 seconds at " + new Date());
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		}
		synchronized (message) {
			message.setText("Notifier took a nap for 3 seconds");
			System.out.println("Notifier is notifying waiting thread to wake up at " + new Date());
			message.notify();
		}

	}

}