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
import javax.swing.JTextField;

public class SwingNoWorkerFrame extends JFrame {

	private JLabel countLabel1;
	private JLabel statusLabel;
	private JButton startButton;
	private JTextField textField;

	public SwingNoWorkerFrame(String title) {
		super(title);
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWeights = new double[]{1.0, 0.0, 0.0, 0.0};
		getContentPane().setLayout(gridBagLayout);
		
		textField = new JTextField();
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.gridwidth = 4;
		gbc_textField.insets = new Insets(0, 0, 5, 5);
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 0;
		gbc_textField.gridy = 0;
		getContentPane().add(textField, gbc_textField);
		textField.setColumns(10);

		countLabel1 = new JLabel("0");
		GridBagConstraints gbc_countLabel1 = new GridBagConstraints();
		gbc_countLabel1.gridwidth = 4;
		gbc_countLabel1.insets = new Insets(0, 0, 5, 0);
		gbc_countLabel1.gridx = 0;
		gbc_countLabel1.gridy = 1;
		getContentPane().add(countLabel1, gbc_countLabel1);

		statusLabel = new JLabel("Task not completed.");
		GridBagConstraints gbc_statusLabel = new GridBagConstraints();
		gbc_statusLabel.gridheight = 2;
		gbc_statusLabel.gridwidth = 4;
		gbc_statusLabel.insets = new Insets(0, 0, 5, 0);
		gbc_statusLabel.gridx = 0;
		gbc_statusLabel.gridy = 2;
		getContentPane().add(statusLabel, gbc_statusLabel);

		startButton = new JButton("Start");
		GridBagConstraints gbc_startButton = new GridBagConstraints();
		gbc_startButton.gridwidth = 4;
		gbc_startButton.gridx = 0;
		gbc_startButton.gridy = 4;
		getContentPane().add(startButton, gbc_startButton);
		GridBagConstraints gc = new GridBagConstraints();
		gc.fill = GridBagConstraints.NONE;

		startButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				statusLabel.setText("Task not completed.");
				start();
				

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

		// Simulate useful work
		for (int i = 2; i < 45; i++) {
			int results = fibonacci(i);
			countLabel1.setText("fibonacci of " + i +" = "+results);
			 
		}
		statusLabel.setText("Completed with status: " + true);
		
		
	}

	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new SwingNoWorkerFrame("Demo1");
			}
		});
	}
}