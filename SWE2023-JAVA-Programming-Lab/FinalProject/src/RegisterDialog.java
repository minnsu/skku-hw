import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

public class RegisterDialog extends JDialog {

	private JPasswordField passwordTextField;
	private JLabel passwordLabel;
	private JLabel retypePasswordLabel;
	private JPasswordField retypePasswordTextField;
	private JLabel emailLabel;
	private JTextField emailTextField;
	private JPanel panel_1;
	private JButton registerButton;

	/**
	 * Create the dialog.
	 */
	public RegisterDialog(JFrame parentFrame) {
		super(parentFrame, true);
		setTitle("Register");
		setBounds(100, 100, 450, 220);
		JPanel contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));

		JPanel panel = new JPanel();
		panel.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.add(panel, BorderLayout.CENTER);
		GridBagLayout gbl_panel = new GridBagLayout();
		gbl_panel.columnWidths = new int[] { 208, 208, 0 };
		gbl_panel.rowHeights = new int[] { 26, 26, 26, 26, 26, 0 };
		gbl_panel.columnWeights = new double[] { 0.0, 0.0, Double.MIN_VALUE };
		gbl_panel.rowWeights = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE };
		panel.setLayout(gbl_panel);
		// add name label
		JLabel NameLabel = new JLabel("Name");
		GridBagConstraints gbc_NameLabel = new GridBagConstraints();
		gbc_NameLabel.fill = GridBagConstraints.BOTH;
		gbc_NameLabel.insets = new Insets(0, 0, 5, 5);
		gbc_NameLabel.gridx = 0;
		gbc_NameLabel.gridy = 0;
		panel.add(NameLabel, gbc_NameLabel);
		NameLabel.setHorizontalAlignment(SwingConstants.CENTER);
		// add name text field
		JTextField nameTextField = new JTextField();
		GridBagConstraints gbc_nameTextField = new GridBagConstraints();
		gbc_nameTextField.fill = GridBagConstraints.BOTH;
		gbc_nameTextField.insets = new Insets(0, 0, 5, 0);
		gbc_nameTextField.gridx = 1;
		gbc_nameTextField.gridy = 0;
		panel.add(nameTextField, gbc_nameTextField);
		nameTextField.setColumns(10);
		// add id label
		JLabel idLabel = new JLabel("ID");
		GridBagConstraints gbc_idLabel = new GridBagConstraints();
		gbc_idLabel.fill = GridBagConstraints.BOTH;
		gbc_idLabel.insets = new Insets(0, 0, 5, 5);
		gbc_idLabel.gridx = 0;
		gbc_idLabel.gridy = 1;
		panel.add(idLabel, gbc_idLabel);
		idLabel.setHorizontalAlignment(SwingConstants.CENTER);
		// add id text field
		JTextField idTextField = new JTextField();
		GridBagConstraints gbc_idTextField = new GridBagConstraints();
		gbc_idTextField.fill = GridBagConstraints.BOTH;
		gbc_idTextField.insets = new Insets(0, 0, 5, 0);
		gbc_idTextField.gridx = 1;
		gbc_idTextField.gridy = 1;
		panel.add(idTextField, gbc_idTextField);
		idTextField.setColumns(10);
		// add password label
		passwordLabel = new JLabel("Password");
		GridBagConstraints gbc_passwordLabel = new GridBagConstraints();
		gbc_passwordLabel.fill = GridBagConstraints.BOTH;
		gbc_passwordLabel.insets = new Insets(0, 0, 5, 5);
		gbc_passwordLabel.gridx = 0;
		gbc_passwordLabel.gridy = 2;
		panel.add(passwordLabel, gbc_passwordLabel);
		passwordLabel.setHorizontalAlignment(SwingConstants.CENTER);
		// add password text field
		passwordTextField = new JPasswordField();
		GridBagConstraints gbc_passwordTextField = new GridBagConstraints();
		gbc_passwordTextField.fill = GridBagConstraints.BOTH;
		gbc_passwordTextField.insets = new Insets(0, 0, 5, 0);
		gbc_passwordTextField.gridx = 1;
		gbc_passwordTextField.gridy = 2;
		panel.add(passwordTextField, gbc_passwordTextField);
		passwordTextField.setColumns(10);
		// add retype password label
		retypePasswordLabel = new JLabel("Retype the password");
		retypePasswordLabel.setHorizontalAlignment(SwingConstants.CENTER);
		GridBagConstraints gbc_retypePasswordLabel = new GridBagConstraints();
		gbc_retypePasswordLabel.fill = GridBagConstraints.BOTH;
		gbc_retypePasswordLabel.insets = new Insets(0, 0, 5, 5);
		gbc_retypePasswordLabel.gridx = 0;
		gbc_retypePasswordLabel.gridy = 3;
		panel.add(retypePasswordLabel, gbc_retypePasswordLabel);
		// add retype password text field
		retypePasswordTextField = new JPasswordField();
		GridBagConstraints gbc_retypePasswordTextField = new GridBagConstraints();
		gbc_retypePasswordTextField.fill = GridBagConstraints.BOTH;
		gbc_retypePasswordTextField.insets = new Insets(0, 0, 5, 0);
		gbc_retypePasswordTextField.gridx = 1;
		gbc_retypePasswordTextField.gridy = 3;
		panel.add(retypePasswordTextField, gbc_retypePasswordTextField);
		retypePasswordTextField.setColumns(10);
		// add email label
		emailLabel = new JLabel("E-mail");
		GridBagConstraints gbc_emailLabel = new GridBagConstraints();
		gbc_emailLabel.fill = GridBagConstraints.BOTH;
		gbc_emailLabel.insets = new Insets(0, 0, 0, 5);
		gbc_emailLabel.gridx = 0;
		gbc_emailLabel.gridy = 4;
		panel.add(emailLabel, gbc_emailLabel);
		emailLabel.setHorizontalAlignment(SwingConstants.CENTER);
		// add email text field
		emailTextField = new JTextField();
		GridBagConstraints gbc_emailTextField = new GridBagConstraints();
		gbc_emailTextField.fill = GridBagConstraints.HORIZONTAL;
		gbc_emailTextField.gridx = 1;
		gbc_emailTextField.gridy = 4;
		panel.add(emailTextField, gbc_emailTextField);
		emailTextField.setColumns(10);

		panel_1 = new JPanel();
		panel_1.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.add(panel_1, BorderLayout.SOUTH);
		GridBagLayout gbl_panel_1 = new GridBagLayout();
		gbl_panel_1.columnWidths = new int[] { 416, 0 };
		gbl_panel_1.rowHeights = new int[] { 23, 0 };
		gbl_panel_1.columnWeights = new double[] { 0.0, Double.MIN_VALUE };
		gbl_panel_1.rowWeights = new double[] { 0.0, Double.MIN_VALUE };
		panel_1.setLayout(gbl_panel_1);
		// add register button
		registerButton = new JButton("Register");
		GridBagConstraints gbc_registerButton = new GridBagConstraints();
		gbc_registerButton.fill = GridBagConstraints.BOTH;
		gbc_registerButton.gridx = 0;
		gbc_registerButton.gridy = 0;
		registerButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if register button is clicked
				User registerObj = new UserFunction(null, nameTextField.getText(), idTextField.getText(), passwordTextField.getText(), emailTextField.getText());
				// make User class and call constructor
				boolean isSuccess;
				isSuccess = registerObj.register(retypePasswordTextField.getText()); // call User class's register method with text field's string
				if(isSuccess) { // and get boolean value
					JOptionPane.showMessageDialog(null, "Register Success!");
					dispose();
				}
				else { // register situation can occur password != retype password error
					JOptionPane.showMessageDialog(null, "Please recheck password");
				}
			}
		});
		panel_1.add(registerButton, gbc_registerButton);

		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}

}