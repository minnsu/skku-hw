import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import java.awt.Color;

public class Calculator extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JPanel contentPane;
	private JTextField textField;
	private JButton clearButton;
	private JButton dec2Bin;
	private JButton dec2Oct;
	private JButton dec2Dec;
	private JButton dec2Hex;
	private JButton eButton;
	private JButton piButton;
	private JButton squaredButton;
	private JButton sqrtButton;
	private JButton logButton;
	private JButton lnButton;
	private JButton bin2Bin;
	private JButton bin2Oct;
	private JButton bin2Dec;
	private JButton bin2Hex;
	private JButton hex2Bin;
	private JButton hex2Oct;
	private JButton hex2Dec;
	private JButton hex2Hex;
	private JButton sevenButton;
	private JButton eightButton;
	private JButton nineButton;
	private JButton divButton;
	private JButton fourButton;
	private JButton fiveButton;
	private JButton sixButton;
	private JButton mulButton;
	private JButton oneButton;
	private JButton twoButton;
	private JButton threeButton;
	private JButton minusButton;
	private JButton dotButton;
	private JButton zeroButton;
	private JButton enterButton;
	private JButton plusButton;

	/**
	 * Create the dialog.
	 */
	public Calculator(JFrame parentFrame) {
		super(parentFrame, true);
		setTitle("Calculator");
		setBounds(100, 100, 500, 490);
		// make content pane
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		// make text field
		textField = new JTextField();
		textField.setBackground(Color.WHITE);
		textField.setEditable(false);
		textField.setHorizontalAlignment(SwingConstants.TRAILING);
		textField.setFont(new Font("Arial", Font.PLAIN, 24));
		textField.setBounds(10, 10, 467, 200);
		contentPane.add(textField);
		textField.setColumns(10);
		// add clear button
		clearButton = new JButton("Clear");
		clearButton.setBounds(10, 219, 91, 30);
		clearButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if clear button is clicked
				textField.setText(""); // clear text field
			}
		});
		contentPane.add(clearButton);
		// add 10 -> 2 button
		dec2Bin = new JButton("10 -> 2");
		dec2Bin.setBounds(104, 219, 91, 30);
		dec2Bin.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 10 -> 2 button is clicked
				try { // change Decimal number to Binary number
					textField.setText(Integer.toBinaryString(Integer.parseInt(textField.getText()))); // parse text field and change to binary string
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : Dec"); // text field cannot translate as number
				}
			}
		});
		contentPane.add(dec2Bin);
		// add 10 -> 8 button
		dec2Oct = new JButton("10 -> 8");
		dec2Oct.setBounds(198, 219, 91, 30);
		dec2Oct.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 10 -> 8 button is clicked
				try { // change Decimal number to Octal number
					textField.setText(Integer.toOctalString(Integer.parseInt(textField.getText()))); // parse text field and change to octal string
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : Dec"); // text field cannot translate as number
				}
			}
		});
		contentPane.add(dec2Oct);
		// add 10 -> 10 button
		dec2Dec = new JButton("10 -> 10");
		dec2Dec.setEnabled(false);
		dec2Dec.setBounds(292, 219, 91, 30);
		contentPane.add(dec2Dec);
		// add 10 -> 16 button
		dec2Hex = new JButton("10 -> 16");
		dec2Hex.setBounds(386, 219, 91, 30);
		dec2Hex.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 10 -> 16 button is clicked
				try { // change Decimal number to Hexadecimal number
					textField.setText(Integer.toHexString(Integer.parseInt(textField.getText()))); // parse text field and change to hex string
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : Dec"); // text field cannot translate as number
				}
			}
		});
		contentPane.add(dec2Hex);
		// add natural number e button
		eButton = new JButton("e");
		eButton.setBounds(10, 252, 91, 30);
		eButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if e button is clicked
				textField.setText("2.71828182846"); // set text as e(natural constant)
			}

		});
		contentPane.add(eButton);
		// add pi button
		piButton = new JButton("\uD835\uDF0B");
		piButton.setBounds(10, 285, 91, 30);
		piButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if pi button is clicked
				textField.setText("3.14159265359"); // set text as pi
			}
		});
		contentPane.add(piButton);
		// add squared button
		squaredButton = new JButton("^2");
		squaredButton.setBounds(10, 318, 91, 30);
		squaredButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if squared button is clicked
				textField.setText(String.format("%f", Math.pow(Float.parseFloat(textField.getText()), 2)));
				// squared the textfield's number
			}

		});
		contentPane.add(squaredButton);
		// add sqrt button
		sqrtButton = new JButton("sqrt");
		sqrtButton.setBounds(10, 351, 91, 30);
		sqrtButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if sqrt button is clicked
				textField.setText(String.format("%f", Math.sqrt(Float.parseFloat(textField.getText()))));
				// sqrt the textfield's number
			}

		});
		contentPane.add(sqrtButton);
		// add log10 button
		logButton = new JButton("log");
		logButton.setBounds(10, 384, 91, 30);
		logButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if log10 button is clicked
				textField.setText(String.format("%f", Math.log10(Float.parseFloat(textField.getText()))));
				// log10 the textfield's number
			}
		});
		contentPane.add(logButton);
		// add natural log button
		lnButton = new JButton("ln");
		lnButton.setBounds(10, 417, 91, 30);
		lnButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if natural log button is clicked
				textField.setText(String.format("%f", Math.log(Float.parseFloat(textField.getText()))));
				// ln the textfield's number
			}
		});
		contentPane.add(lnButton);
		// add 2 -> 2 button
		bin2Bin = new JButton("2 -> 2");
		bin2Bin.setEnabled(false);
		bin2Bin.setBounds(104, 252, 91, 30);
		contentPane.add(bin2Bin);
		// add 2 -> 8 button
		bin2Oct = new JButton("2 -> 8");
		bin2Oct.setBounds(198, 252, 91, 30);
		bin2Oct.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 2 -> 8 button is clicked
				try { // change Binary number to Octal number
					textField.setText(Integer.toOctalString(Integer.parseInt(textField.getText(), 2)));
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : Bin");
					// text field cannot translate as number
				}
			}
		});
		contentPane.add(bin2Oct);
		// add 2 -> 10 buttton
		bin2Dec = new JButton("2 -> 10");
		bin2Dec.setBounds(292, 252, 91, 30);
		bin2Dec.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 2 -> 10 button is clicked
				try { // change Binary number to Decimal number
					textField.setText(String.format("%d", Integer.parseInt(textField.getText(), 2)));
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : Bin");
					// text field cannot translate as number
				}
			}
		});
		contentPane.add(bin2Dec);
		// add 2 -> 16 button
		bin2Hex = new JButton("2 -> 16");
		bin2Hex.setBounds(386, 252, 91, 30);
		bin2Hex.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 2 -> 16 button is clicked
				try { // change Binary number to Hexadecimal number
					textField.setText(Integer.toHexString(Integer.parseInt(textField.getText(), 2)));
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : Bin");
					// text field cannot translate as number
				}
			}
		});
		contentPane.add(bin2Hex);
		// add 16 -> 2 button
		hex2Bin = new JButton("16 -> 2");
		hex2Bin.setBounds(104, 285, 91, 30);
		hex2Bin.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 16 -> 2 button is clicked
				try { // change Hexadecimal number to Binary number
					textField.setText(Integer.toBinaryString(Integer.parseInt(textField.getText(), 16)));
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : hex");
					// text field cannot translate as number
				}
			}

		});
		contentPane.add(hex2Bin);
		// add 16 -> 8 button
		hex2Oct = new JButton("16 -> 8");
		hex2Oct.setBounds(198, 285, 91, 30);
		hex2Oct.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 16 -> 8 button is clicked
				try { // change Hexadecimal number to Octal number
					textField.setText(Integer.toOctalString(Integer.parseInt(textField.getText(), 16)));
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : hex");
					// text field cannot translate as number
				}
			}
		});
		contentPane.add(hex2Oct);
		// add 16 -> 10 button
		hex2Dec = new JButton("16 -> 10");
		hex2Dec.setBounds(292, 285, 91, 30);
		hex2Dec.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if 16 -> 10 button is clicked
				try { // change Hexadecimal number to Decimal number
					textField.setText(String.format("%d", Integer.parseInt(textField.getText(), 16)));
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null, "Please check the string format : hex");
					// text field cannot translate as number
				}
			}

		});
		contentPane.add(hex2Dec);
		// add 16 -> 16 button
		hex2Hex = new JButton("16 -> 16");
		hex2Hex.setEnabled(false);
		hex2Hex.setBounds(386, 285, 91, 30);
		contentPane.add(hex2Hex);

		/*
		 * 0 ~ 9 button is just add the character of present textfield's text
		 */
		
		sevenButton = new JButton("7");
		sevenButton.setBounds(104, 318, 91, 30);
		sevenButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "7");
			}
		});
		contentPane.add(sevenButton);

		eightButton = new JButton("8");
		eightButton.setBounds(198, 318, 91, 30);
		eightButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "8");
			}
		});
		contentPane.add(eightButton);

		nineButton = new JButton("9");
		nineButton.setBounds(292, 318, 91, 30);
		nineButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "9");
			}
		});
		contentPane.add(nineButton);

		divButton = new JButton("\u00F7");
		divButton.setBounds(386, 318, 91, 30);
		divButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + " / ");
			}
		});
		contentPane.add(divButton);

		fourButton = new JButton("4");
		fourButton.setBounds(104, 351, 91, 30);
		fourButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "4");
			}
		});
		contentPane.add(fourButton);

		fiveButton = new JButton("5");
		fiveButton.setBounds(198, 351, 91, 30);
		fiveButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "5");
			}
		});
		contentPane.add(fiveButton);

		sixButton = new JButton("6");
		sixButton.setBounds(292, 351, 91, 30);
		sixButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "6");
			}
		});
		contentPane.add(sixButton);
		// mul button add to text field " x "
		mulButton = new JButton("X");
		mulButton.setBounds(386, 351, 91, 30);
		mulButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + " x ");
			}
		});
		contentPane.add(mulButton);

		oneButton = new JButton("1");
		oneButton.setBounds(104, 384, 91, 30);
		oneButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "1");
			}
		});
		contentPane.add(oneButton);

		twoButton = new JButton("2");
		twoButton.setBounds(198, 384, 91, 30);
		twoButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "2");
			}
		});
		contentPane.add(twoButton);

		threeButton = new JButton("3");
		threeButton.setBounds(292, 384, 91, 30);
		threeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "3");
			}
		});
		contentPane.add(threeButton);
		// minus button add to text field " - "
		minusButton = new JButton("-");
		minusButton.setBounds(386, 384, 91, 30);
		minusButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + " - ");
			}
		});
		contentPane.add(minusButton);
		// add dot button for floating point number
		dotButton = new JButton(".");
		dotButton.setBounds(104, 417, 91, 30);
		dotButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + ".");
			}
		});
		contentPane.add(dotButton);

		zeroButton = new JButton("0");
		zeroButton.setBounds(198, 417, 91, 30);
		zeroButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + "0");
			}
		});
		contentPane.add(zeroButton);
		// add enter button : calculate the text field
		enterButton = new JButton("=");
		enterButton.setBounds(292, 417, 91, 30);
		enterButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// calculate the string expression
				CalculateFunction action = new CalculateFunction();
				action.calc(action.in2Post(textField.getText()));
				// text field : infix, call in2Post : infix -> postfix, call calc : postfix -> calculated value string
				textField.setText(action.answer);
			}
		});
		contentPane.add(enterButton);
		// plus button add to text field " + "
		plusButton = new JButton("+");
		plusButton.setBounds(386, 417, 91, 30);
		plusButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				textField.setText(textField.getText() + " + ");
			}
		});
		contentPane.add(plusButton);

		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}

}