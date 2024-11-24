package com.sync;

import java.util.Date;

public class Waiter implements Runnable {

	Message message;

	public Waiter(Message message) {
		this.message = message;
	}

	@Override
	public void run() {
		synchronized (message) {
			try {
				System.out.println("Waiter is waiting for the notifier at " + new Date());
				message.wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println("Waiter is done waiting at " + new Date());
		System.out.println("Waiter got the message: " + message.getText());
	}

}