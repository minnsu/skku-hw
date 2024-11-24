import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.EmptyBorder;

public class Notepad extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JMenuBar menuBar;
	private JMenu fileMenu;
	private JMenuItem saveMenuItem;
	private JMenuItem loadMenuItem;
	private JPanel contentPane;
	private JScrollPane scrollPane;
	private JTextArea textArea;

	/**
	 * Create the dialog.
	 */
	public Notepad(JFrame parentFrame, String userTag) {
		super(parentFrame, true);
		setTitle("Notepad");
		setBounds(100, 100, 650, 550);
		// make menu bar : menu bar has save, load menu item
		menuBar = new JMenuBar();
		menuBar.setFont(new Font("Arial", Font.PLAIN, 18));
		setJMenuBar(menuBar);
		// add file menu to menu bar, this has load, save functionalities
		fileMenu = new JMenu("file");
		fileMenu.setFont(new Font("Arial", Font.BOLD, 16));
		menuBar.add(fileMenu);
		// add save menu item to file menu
		saveMenuItem = new JMenuItem("save file");
		saveMenuItem.setFont(new Font("Arial", Font.BOLD, 16));
		saveMenuItem.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if save menu item is clicked
				File f = new File("DATA/usertext/" + userTag + ".txt"); // select file with userTag
				try {
					PrintWriter writer = new PrintWriter(new FileOutputStream("DATA/usertext/" + userTag + ".txt", false)); // write from scratch
					writer.println(textArea.getText()); // save the text of textfield to userTag.txt in DATA/usertext/ folder
					textArea.setText(""); // and erase the textfield
					writer.close(); // close
				} 
				catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		});
		fileMenu.add(saveMenuItem);
		// add load menu item to file menu
		loadMenuItem = new JMenuItem("load file");
		loadMenuItem.setFont(new Font("Arial", Font.BOLD, 16));
		loadMenuItem.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if load menu item is clicked
				try { // read the file
					Scanner reader = new Scanner(new FileInputStream("DATA/usertext/" + userTag + ".txt")); // scan file
					String totalFileContents = "";
					while (reader.hasNext()) { // read
						totalFileContents += reader.nextLine() + "\n";

					}
					textArea.setText(totalFileContents); // set text field
				} catch (FileNotFoundException e1) { // if file does not exist
					File Folder = new File("DATA/usertext/"); // folder exist check
					if(!Folder.exists()) { // when folder does not exist
						Folder.mkdir(); // make folder
					}
					// and print error message and make userTag.txt file in DATA/usertext/ folder
        			JOptionPane.showMessageDialog(null, "Your text file does not exist, so we make your file : " + userTag + ".txt");
					File f = new File("DATA/" + userTag + ".txt");
				}

			}
		});
		fileMenu.add(loadMenuItem);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		// add scrollPane, this has text area
		scrollPane = new JScrollPane();
		contentPane.add(scrollPane, BorderLayout.CENTER);
		// add text area
		textArea = new JTextArea();
		scrollPane.setViewportView(textArea);

		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setVisible(true);
	}

}
