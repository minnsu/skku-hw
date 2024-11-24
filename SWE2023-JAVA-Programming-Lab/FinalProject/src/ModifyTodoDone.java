import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTextField;

public class ModifyTodoDone extends JDialog {
	private JTextField textField;

	/**
	 * Create the dialog.
	 */
	public ModifyTodoDone(JDialog parentDialog, String value) {
		super(parentDialog,true);
		setTitle("Modify Todo list");
		setBounds(100, 100, 450, 109);
		getContentPane().setLayout(null);
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setBounds(0, 35, 436, 33);
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane);
			{
				JButton okButton = new JButton("Modify"); // show modify button
				okButton.addActionListener(new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent e) { // if modify button is clicked
						// TODO Auto-generated method stub
						setVisible(false); // set to unvisible
					}
				});
				okButton.setActionCommand("Modify");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
			{
				JButton cancelButton = new JButton("Cancel"); // show cancel button
				cancelButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) { // if cancel button is clicked
						dispose(); // dispose
					}
				});
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
		{
			textField = new JTextField(value);
			textField.setBounds(5, 5, 430, 30);
			getContentPane().add(textField);
			textField.setColumns(10);
		}		
		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}
	
	public String getModifiedText() { // modified text is equal to textfield's string
		return textField.getText();
	}
}
