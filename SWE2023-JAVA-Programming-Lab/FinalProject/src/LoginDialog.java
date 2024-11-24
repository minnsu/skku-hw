import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
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

public class LoginDialog extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JPanel contentPane;
	private JPanel inputPane;
	private JLabel idLabel;
	private JTextField idTextField;
	private JLabel passwordLabel;
	private JPasswordField passwordTextField;
	private JPanel buttonPane;
	private JButton loginButton;
	public String userTag;

	/**
	 * Create the dialog.
	 */
	public LoginDialog(JFrame parentFrame) {
		super(parentFrame, true);
		setTitle("Login");
		setBounds(100, 100, 450, 140);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new GridLayout(2, 1, 0, 0));
		// add input pane
		inputPane = new JPanel();
		inputPane.setBorder(new EmptyBorder(10, 5, 10, 5));
		contentPane.add(inputPane);
		GridBagLayout gbl_inputPane = new GridBagLayout();
		gbl_inputPane.columnWidths = new int[] { 208, 208, 0 };
		gbl_inputPane.rowHeights = new int[] { 33, 33, 0 };
		gbl_inputPane.columnWeights = new double[] { 0.0, 0.0, Double.MIN_VALUE };
		gbl_inputPane.rowWeights = new double[] { 0.0, 0.0, Double.MIN_VALUE };
		inputPane.setLayout(gbl_inputPane);
		// add id label
		idLabel = new JLabel("ID");
		GridBagConstraints gbc_idLabel = new GridBagConstraints();
		gbc_idLabel.fill = GridBagConstraints.BOTH;
		gbc_idLabel.insets = new Insets(0, 0, 5, 5);
		gbc_idLabel.gridx = 0;
		gbc_idLabel.gridy = 0;
		inputPane.add(idLabel, gbc_idLabel);
		idLabel.setHorizontalAlignment(SwingConstants.CENTER);
		// add id textfield
		idTextField = new JTextField();
		GridBagConstraints gbc_idTextField = new GridBagConstraints();
		gbc_idTextField.fill = GridBagConstraints.BOTH;
		gbc_idTextField.insets = new Insets(0, 0, 5, 0);
		gbc_idTextField.gridx = 1;
		gbc_idTextField.gridy = 0;
		inputPane.add(idTextField, gbc_idTextField);
		idTextField.setColumns(10);
		// add password label
		passwordLabel = new JLabel("Password");
		GridBagConstraints gbc_passwordLabel = new GridBagConstraints();
		gbc_passwordLabel.fill = GridBagConstraints.BOTH;
		gbc_passwordLabel.insets = new Insets(0, 0, 0, 5);
		gbc_passwordLabel.gridx = 0;
		gbc_passwordLabel.gridy = 1;
		inputPane.add(passwordLabel, gbc_passwordLabel);
		passwordLabel.setHorizontalAlignment(SwingConstants.CENTER);
		// add password text field
		passwordTextField = new JPasswordField();
		GridBagConstraints gbc_passwordTextField = new GridBagConstraints();
		gbc_passwordTextField.fill = GridBagConstraints.HORIZONTAL;
		gbc_passwordTextField.gridx = 1;
		gbc_passwordTextField.gridy = 1;
		inputPane.add(passwordTextField, gbc_passwordTextField);
		passwordTextField.setColumns(10);

		buttonPane = new JPanel();
		buttonPane.setBorder(new EmptyBorder(15, 5, 5, 5));
		contentPane.add(buttonPane);
		// add login button
		loginButton = new JButton("Login");
		loginButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				User loginObj = new UserFunction(null, idTextField.getText(), passwordTextField.getText()); // make User object and call contructor
				userTag = loginObj.login(); // call login method of User class with id, password text
				if(userTag.equals("-1")) { // password value error
					JOptionPane.showMessageDialog(null, "Please check your password");
					passwordTextField.setText("");
					userTag = null;
				}
				else if(userTag.equals("-2")) { // ID exist error
					JOptionPane.showMessageDialog(null, "ID does not exist.");
					idTextField.setText("");
					passwordTextField.setText("");
					userTag = null;
				}
				else { // if error doesn't occur
					JOptionPane.showMessageDialog(null, "Login Success!"); // id && password matched -> success
					dispose();
				}
			}
		});
		buttonPane.setLayout(new BorderLayout(0, 0));
		buttonPane.add(loginButton);

		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}

}