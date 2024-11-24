import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

public class TodoDoneList extends JDialog {

	private JPanel contentPane;
	private JLabel todoListLabel;
	private JScrollPane todoScrollPane;
	private JList todoJList;
	private JLabel doneListLabel;
	private JScrollPane doneScrollPane;
	private JList doneJList;
	private JButton moveToDoneButton;
	private JButton deleteFromTodo;
	private JButton deleteFromDone;
	private JTextField addTodoTextField;
	private JButton addTodoButton;
	private JButton moveToTodoButton;
	
	private TodoDoneList frame = TodoDoneList.this;
	List<String> todoData = new ArrayList<String>();
	DefaultListModel<String> todoModel = new DefaultListModel<String>();
	List<String> doneData = new ArrayList<String>();
	DefaultListModel<String> doneModel = new DefaultListModel<String>();

	/**
	 * Create the dialog.
	 */
	public TodoDoneList(JFrame parentFrame) {
		super(parentFrame, true);
		setTitle("Todo / Done");
		setBounds(100, 100, 600, 580);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		// add todoList label
		todoListLabel = new JLabel("Todo List");
		todoListLabel.setFont(new Font("Arial", Font.BOLD, 15));
		todoListLabel.setHorizontalAlignment(SwingConstants.CENTER);
		todoListLabel.setBounds(12, 5, 400, 25);
		contentPane.add(todoListLabel);
		// add todoScrollPane, this has Todo JList
		todoScrollPane = new JScrollPane();
		todoScrollPane.setBounds(12, 30, 562, 215);
		contentPane.add(todoScrollPane);
		// add todoJList
		todoJList = new JList(todoModel);
		todoJList.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) { // if element of todoJList is selected
				if (e.getClickCount() == 2) { // if double clicked
					int index = todoJList.getSelectedIndex(); // find selected index
					String value = todoModel.get(index); // and find the string
					ModifyTodoDone modifyDialog = new ModifyTodoDone(frame, value); // call ModifyTodoDone dialog
					String modified = modifyDialog.getModifiedText(); // get modified string by call modifyDialog's getter function
					todoModel.set(index, modified); // and modify the selected JList element
				}
			}
		});
		todoScrollPane.setViewportView(todoJList);
		// add done list label
		doneListLabel = new JLabel("Done List");
		doneListLabel.setFont(new Font("Arial", Font.BOLD, 15));
		doneListLabel.setHorizontalAlignment(SwingConstants.CENTER);
		doneListLabel.setBounds(12, 295, 400, 25);
		contentPane.add(doneListLabel);
		// add doneScrollPane, this has done JList
		doneScrollPane = new JScrollPane();
		doneScrollPane.setBounds(12, 320, 562, 215);
		contentPane.add(doneScrollPane);
		// add doneJList
		doneJList = new JList(doneModel);
		doneJList.addMouseListener(new MouseAdapter() { // if element of doneJList is selected
			@Override
			public void mouseClicked(MouseEvent e) { // if 
				if (e.getClickCount() == 2) { // if double clicked
					int index = doneJList.getSelectedIndex(); // find selected index
					String value = doneModel.get(index); // and find the string
					ModifyTodoDone modifyDialog = new ModifyTodoDone(frame, value); // call ModifyTodoDone dialog
					String modified = modifyDialog.getModifiedText(); // get modified string by call modifyDialog's getter function
					doneModel.set(index, modified); // and modify the selected JList element
				}
			}
		});
		doneScrollPane.setViewportView(doneJList);
		// add move to done button : move element from todo JList to done JList
		moveToDoneButton = new JButton("move to Done");
		moveToDoneButton.setBounds(375, 5, 115, 20);
		moveToDoneButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if button is clicked
				// TODO Auto-generated method stub
				if (todoJList.isSelectionEmpty()) { // there is no selected element
					JOptionPane.showMessageDialog(null, "Please select on todo list's element."); // show error message dialog
					return;
				}
				// else
				int index = todoJList.getSelectedIndex(); // find index
				doneModel.addElement(todoJList.getSelectedValue().toString()); // add to doneModel
				todoModel.removeElementAt(index); // delete from todoModel
			}
		});
		contentPane.add(moveToDoneButton);
		// add delete from todo button
		deleteFromTodo = new JButton("delete");
		deleteFromTodo.setBounds(494, 5, 80, 20);
		deleteFromTodo.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if button is clicked
				// TODO Auto-generated method stub
				if (todoJList.isSelectionEmpty()) { // there is no selected element
					JOptionPane.showMessageDialog(null, "Please select on todo list's element."); // show error message dialog
					return;
				}
				int index = todoJList.getSelectedIndex(); // find index
				todoModel.removeElementAt(index); // delete from todoModel
			}
		});
		contentPane.add(deleteFromTodo);
		// add delete from done button
		deleteFromDone = new JButton("delete");
		deleteFromDone.setBounds(494, 295, 80, 20);
		deleteFromDone.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if button is clicked
				// TODO Auto-generated method stub
				if (doneJList.isSelectionEmpty()) { // there is no selected element
					JOptionPane.showMessageDialog(null, "Please select on done list's element."); // show error message dialog
					return;
				}
				int index = doneJList.getSelectedIndex(); // find index
				doneModel.removeElementAt(index); // delete from doneModel
			}
		});
		contentPane.add(deleteFromDone);
		// add todo text field
		addTodoTextField = new JTextField();
		addTodoTextField.setBounds(124, 255, 450, 25);
		contentPane.add(addTodoTextField);
		addTodoTextField.setColumns(10);
		// add 'add todo element' button
		addTodoButton = new JButton("Add");
		addTodoButton.setBounds(12, 255, 100, 25);
		addTodoButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if button is clicked
				// TODO Auto-generated method stub
				String str = addTodoTextField.getText(); // get text from textfield
				if (str.length() == 0) { // if there is no value
					JOptionPane.showMessageDialog(null, "Fill the text field!"); // show error message dialog
					return;
				}
				// else
				todoModel.addElement(str); // add string to todoModel
				addTodoTextField.setText(""); // and erase the text field
			}
		});
		contentPane.add(addTodoButton);
		// add move to todo button : done JList -> todo JList
		moveToTodoButton = new JButton("move to Todo");
		moveToTodoButton.setBounds(375, 295, 115, 20);
		moveToTodoButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if button is clicked
				// TODO Auto-generated method stub
				if (doneJList.isSelectionEmpty()) { // if there is no selected element in done JList
					JOptionPane.showMessageDialog(null, "Please select on done list's element."); // show error message dialog
					return;
				}
				// else
				int index = doneJList.getSelectedIndex(); // find index
				todoModel.addElement(doneJList.getSelectedValue().toString()); // add to todoModel
				doneModel.removeElementAt(index); // delete from doneModel
			}
			
		});
		contentPane.add(moveToTodoButton);

		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}
}
