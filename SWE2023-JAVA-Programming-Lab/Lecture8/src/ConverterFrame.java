import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class ConverterFrame extends JFrame implements ActionListener {
	JLabel distanceLabel; // = new JLabel("Distance in Km");
	JTextField inputKm;
	JButton calculateButton;
	JLabel displayLabel;
	
	public ConverterFrame() {
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setSize(300, 100);
		setLayout(new GridLayout(2, 2));
		setTitle("Convertor");
		
		distanceLabel = new JLabel("Distance in Km");
		inputKm = new JTextField();
		calculateButton = new JButton("Calculate");
		displayLabel = new JLabel();
		
		add(distanceLabel);
		add(inputKm);
		add(calculateButton);
		add(displayLabel);
		
		calculateButton.addActionListener(this);
		
		setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		String inputValue = inputKm.getText();
		// convert string into double value
		double inputkm = Double.parseDouble(inputValue);
		double resultkm = inputkm * 0.621;
		
		displayLabel.setText( String.format("%f miles(s)", resultkm) );
		
	}
}
