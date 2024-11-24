import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*; // JFrame, JButton

public class FirstGUI extends JFrame {
	private JButton button1;
	private JButton button2;
	private JButton button3;
	private JButton button4;
	private JButton button5;
	
	public FirstGUI() {
		super.setSize(300, 300);
		super.setTitle("First GUI");
		super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		button1 = new JButton();
		button2 = new JButton();
		button3 = new JButton("Explore");
		button4 = new JButton("Cancel");
		button5 = new JButton("Send");
		
		button1.setText("Back");
		button1.setBackground(Color.RED);

		button2.setText("Next");
		button2.setBackground(Color.ORANGE);
		
		super.setLayout(new BorderLayout());

		super.add(button1, BorderLayout.EAST);
		super.add(button2, BorderLayout.WEST);
		super.add(button3, BorderLayout.CENTER);
		super.add(button4, BorderLayout.NORTH);
		super.add(button5, BorderLayout.SOUTH);
		
		button1.addActionListener(new changeColor());
		button2.addActionListener(new anotherAction());
		button3.addActionListener(new changeColor());
		button4.addActionListener(new anotherAction());
		button5.addActionListener(new anotherAction());

		super.setVisible(true);
	}
	
	public static void main(String[] args) {
		FirstGUI gui = new FirstGUI();
	}

	private class changeColor implements ActionListener {
		JButton controledButton;

		public void change() {
			controledButton.setBackground(Color.YELLOW);
		}

		public void setControled(JButton obj) {
			// TODO Auto-generated method stub
			controledButton = obj;
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
//		this.setColor((JButton) e.getSource()); // e로 부터 받은 event 대상
//			this.change();
			System.out.println("Clicked");
		}
	}
	private class anotherAction implements ActionListener {
		JButton controledButton;

		public void change() {
			controledButton.setBackground(Color.YELLOW);
		}

		public void setControled(JButton obj) {
			// TODO Auto-generated method stub
			controledButton = obj;
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
//		this.setColor((JButton) e.getSource()); // e로 부터 받은 event 대상
//			this.change();
			System.out.println("Knock!!");
		}
	}
}