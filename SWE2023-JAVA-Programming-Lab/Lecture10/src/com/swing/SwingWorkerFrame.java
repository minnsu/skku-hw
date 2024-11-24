package com.swing;


import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.concurrent.ExecutionException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import java.awt.Insets;

public class SwingWorkerFrame extends JFrame {

	private JLabel countLabel1;
	private JLabel statusLabel;
	private JButton startButton;

	public SwingWorkerFrame(String title) {
		super(title);
		getContentPane().setLayout(new GridBagLayout());

		countLabel1 = new JLabel("0");
		GridBagConstraints gbc_countLabel1 = new GridBagConstraints();
		gbc_countLabel1.gridwidth = 4;
		gbc_countLabel1.insets = new Insets(0, 0, 5, 0);
		gbc_countLabel1.gridx = 0;
		gbc_countLabel1.gridy = 0;
		getContentPane().add(countLabel1, gbc_countLabel1);

		statusLabel = new JLabel("Task not completed.");
		GridBagConstraints gbc_statusLabel = new GridBagConstraints();
		gbc_statusLabel.gridheight = 2;
		gbc_statusLabel.gridwidth = 4;
		gbc_statusLabel.insets = new Insets(0, 0, 5, 0);
		gbc_statusLabel.gridx = 0;
		gbc_statusLabel.gridy = 1;
		getContentPane().add(statusLabel, gbc_statusLabel);

		startButton = new JButton("Start");
		GridBagConstraints gbc_startButton = new GridBagConstraints();
		gbc_startButton.gridwidth = 4;
		gbc_startButton.gridx = 0;
		gbc_startButton.gridy = 3;
		getContentPane().add(startButton, gbc_startButton);
		GridBagConstraints gc = new GridBagConstraints();
		gc.fill = GridBagConstraints.NONE;

		startButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				start();
				statusLabel.setText("Task not completed.");

			}
		});
		setSize(200, 400);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}
	public int fibonacci(int number) {
		  if (number == 1 || number == 2) {
		    return 1;
		  }
		  return fibonacci(number - 1) + fibonacci(number - 2);
		}
	private void start() {

		// Use SwingWorker<Void, Void> and return null from doInBackground if
		// you don't want any final result and you don't want to update the GUI
		// as the thread goes along.
		// First argument is the thread result, returned when processing
		// finished.
		// Second argument is the value to update the GUI with via publish() and
		// process()
		
		
		SwingWorker worker = new SwingWorker<Boolean, Integer>() {

			@Override
			/*
			 * Note: do not update the GUI from within doInBackground.
			 */
			protected Boolean doInBackground() throws Exception {
				// Simulate useful work
				for (int i = 2; i < 40; i++) {
					Thread.sleep(100);
					int results = fibonacci(i);

					// optional: use publish to send values to process(), which
					// you can then use to update the GUI.
					publish(i);
					publish(results);
				}
				return false;
			}

			@Override
			// This will be called if you call publish() from doInBackground()
			// Can safely update the GUI here.
			protected void process(List<Integer> chunks) {
				System.out.println(chunks.toString());
				Integer value = chunks.get(chunks.size() - 2);
				Integer result = chunks.get(chunks.size() - 1);
				countLabel1.setText("fibonacci of " + value+ " = "+ result);
			}

			@Override
			// This is called when the thread finishes.
			// Can safely update GUI here.
			protected void done() {
				try {
					Boolean status = get();
					statusLabel.setText("Completed with status: " + status);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (ExecutionException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		};
		worker.execute(); // thread.start();
	}

	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new SwingWorkerFrame("Demo1");
			}
		});
	}
}