package com.phonebook;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class EditDialog extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JTextField NameTextField;
	private JTextField PhoneTextField;
	
	
		/**
	 * Create the dialog.
	 */
	public EditDialog(JFrame parentFrame, String Name, String Phone) {
		super(parentFrame,true);
		setTitle("Edit Conact");
		setBounds(100, 100, 369, 124);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		GridBagLayout gbl_contentPanel = new GridBagLayout();
		gbl_contentPanel.columnWidths = new int[]{0, 0, 0, 0, 0};
		gbl_contentPanel.rowHeights = new int[]{0, 0, 0};
		gbl_contentPanel.columnWeights = new double[]{0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		gbl_contentPanel.rowWeights = new double[]{0.0, 0.0, Double.MIN_VALUE};
		contentPanel.setLayout(gbl_contentPanel);
		{
			JLabel lblNewLabel = new JLabel("Name");
			GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
			gbc_lblNewLabel.anchor = GridBagConstraints.WEST;
			gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
			gbc_lblNewLabel.gridx = 1;
			gbc_lblNewLabel.gridy = 0;
			contentPanel.add(lblNewLabel, gbc_lblNewLabel);
		}
		{
			NameTextField = new JTextField(Name);
			GridBagConstraints gbc_NameTextField = new GridBagConstraints();
			gbc_NameTextField.insets = new Insets(0, 0, 5, 0);
			gbc_NameTextField.fill = GridBagConstraints.HORIZONTAL;
			gbc_NameTextField.gridx = 3;
			gbc_NameTextField.gridy = 0;
			contentPanel.add(NameTextField, gbc_NameTextField);
			NameTextField.setColumns(10);
		}
		{
			JLabel lblNewLabel_1 = new JLabel("Phone Number");
			GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
			gbc_lblNewLabel_1.anchor = GridBagConstraints.WEST;
			gbc_lblNewLabel_1.insets = new Insets(0, 0, 0, 5);
			gbc_lblNewLabel_1.gridx = 1;
			gbc_lblNewLabel_1.gridy = 1;
			contentPanel.add(lblNewLabel_1, gbc_lblNewLabel_1);
		}
		{
			PhoneTextField = new JTextField(Phone);
			GridBagConstraints gbc_PhoneTextField = new GridBagConstraints();
			gbc_PhoneTextField.fill = GridBagConstraints.HORIZONTAL;
			gbc_PhoneTextField.gridx = 3;
			gbc_PhoneTextField.gridy = 1;
			contentPanel.add(PhoneTextField, gbc_PhoneTextField);
			PhoneTextField.setColumns(10);
		}
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				JButton okButton = new JButton("OK");
				okButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
					setVisible(false);
					
					}
				});
				okButton.setActionCommand("OK");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
			{
				JButton cancelButton = new JButton("Cancel");
				cancelButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
					dispose();
					}
				});
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
		
		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}
	public String getName() {
		return NameTextField.getText();
		
	}
	public String getPhone() {
		return PhoneTextField.getText();
	}
}
