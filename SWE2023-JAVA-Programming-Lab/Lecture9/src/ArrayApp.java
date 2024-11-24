import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import java.awt.GridBagLayout;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.SwingConstants;

public class ArrayApp extends JFrame {
	private int[] array = new int[10];
	private int index = 0;
	private JPanel contentPane;
	private JLabel insertLabel;
	private JTextField insertTextfield;
	private JLabel arrayDisplayLabel;
	private JPanel panel;
	private JLabel array_name;
	private JTextField indexTextfield;
	private JLabel lblNewLabel_1;
	private JTextField valueTextfield;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ArrayApp frame = new ArrayApp();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public ArrayApp() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 131);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 1.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		insertLabel = new JLabel("Insert Number ");
		insertLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		GridBagConstraints gbc_insertLabel = new GridBagConstraints();
		gbc_insertLabel.gridwidth = 7;
		gbc_insertLabel.insets = new Insets(0, 0, 5, 5);
		gbc_insertLabel.gridx = 1;
		gbc_insertLabel.gridy = 0;
		contentPane.add(insertLabel, gbc_insertLabel);
		
		insertTextfield = new JTextField();
		insertTextfield.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					int tmpInt = Integer.parseInt(insertTextfield.getText());
					if(index >= 10) {
						throw new ArrayIndexOutOfBoundsException();
					}
					for(int i = 0; i < index; i++) {
						if(tmpInt == array[i]) {
							throw new DuplicateException("Duplicate Value");
						}
					}
					array[index++] = tmpInt;
					String tmp = "";
					for(int i = 0; i < index; i++) {
						tmp = tmp + String.format("%d", array[i]);
						if (i != index - 1) {tmp = tmp + ", ";}
					}
					arrayDisplayLabel.setText("a = [" + tmp + "]");
				} catch(ArrayIndexOutOfBoundsException ee) {
					JOptionPane.showMessageDialog(null, "Array's maximum size is 10");
				} catch(NumberFormatException ee) {
					JOptionPane.showMessageDialog(null, "Please enter only integer values");
				} catch(DuplicateException ee) {
					JOptionPane.showMessageDialog(null, "Please enter only unique integers");
				} finally {
					insertTextfield.setText("");
				}
			}
		});
		GridBagConstraints gbc_insertTextfield = new GridBagConstraints();
		gbc_insertTextfield.insets = new Insets(0, 0, 5, 0);
		gbc_insertTextfield.fill = GridBagConstraints.HORIZONTAL;
		gbc_insertTextfield.gridx = 8;
		gbc_insertTextfield.gridy = 0;
		contentPane.add(insertTextfield, gbc_insertTextfield);
		insertTextfield.setColumns(10);
		
		arrayDisplayLabel = new JLabel("a = [ ]");
		GridBagConstraints gbc_arrayDisplayLabel = new GridBagConstraints();
		gbc_arrayDisplayLabel.insets = new Insets(0, 0, 5, 0);
		gbc_arrayDisplayLabel.gridwidth = 9;
		gbc_arrayDisplayLabel.gridx = 0;
		gbc_arrayDisplayLabel.gridy = 1;
		contentPane.add(arrayDisplayLabel, gbc_arrayDisplayLabel);
		
		panel = new JPanel();
		GridBagConstraints gbc_panel = new GridBagConstraints();
		gbc_panel.gridwidth = 9;
		gbc_panel.insets = new Insets(0, 0, 0, 5);
		gbc_panel.fill = GridBagConstraints.BOTH;
		gbc_panel.gridx = 0;
		gbc_panel.gridy = 2;
		contentPane.add(panel, gbc_panel);
		
		array_name = new JLabel("a [");
		panel.add(array_name);
		
		indexTextfield = new JTextField();
		indexTextfield.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int getindex = 0;
				try {
					getindex = Integer.parseInt(indexTextfield.getText());
					if(getindex > index) {
						throw new ArrayIndexOutOfBoundsException();
					}
					valueTextfield.setText(String.format("%d", array[getindex]));
				} catch(NumberFormatException ee) {
					JOptionPane.showMessageDialog(null, "Please enter only integer values");
				} catch(ArrayIndexOutOfBoundsException ee) {
					JOptionPane.showMessageDialog(null, "Value not found in a array");
				} finally {
					indexTextfield.setText("");	
				}
			}
		});
		panel.add(indexTextfield);
		indexTextfield.setColumns(10);
		
		lblNewLabel_1 = new JLabel("] = ");
		panel.add(lblNewLabel_1);
		
		valueTextfield = new JTextField();
		valueTextfield.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					int value = Integer.parseInt(valueTextfield.getText());
					for(int i = 0; i < index; i++) {
						if(array[i] == value) {
							indexTextfield.setText(String.format("%d ", i));
							break;
						}
						if(i == index - 1) {
							throw new NumberNotfoundException();
						}
					}
					if(index == 0) {throw new NumberNotfoundException();}
				} catch(NumberFormatException ee) {
					JOptionPane.showMessageDialog(null, "Please enter only integer values");
				} catch(NumberNotfoundException ee) {
					JOptionPane.showMessageDialog(null, "Index Not Found.");
				} finally {
					valueTextfield.setText("");					
				}
			}
		});
		panel.add(valueTextfield);
		valueTextfield.setColumns(10);
	}
}


class NumberNotfoundException extends Exception{
	public NumberNotfoundException(){
		super();
	}
	public NumberNotfoundException(String tmp){
		super(tmp);
	}
}
class DuplicateException extends Exception{
	public DuplicateException() {
		super();
	}
	public DuplicateException(String tmp){
		super(tmp);
	}
}