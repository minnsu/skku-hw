import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;


import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.util.Scanner;
import java.awt.event.ActionEvent;

public class Notepad extends JFrame {

	private JPanel contentPane;
	private JMenuBar menuBar;
	private JMenu mnNewMenu;
	private JMenuItem mntmNewMenuItem;
	private JMenuItem mntmNewMenuItem_1;
	private JMenuItem mntmNewMenuItem_2;
	private JScrollPane scrollPane;
	private JTextArea textArea;
	private JMenuItem mntmNewMenuItem_3;
	private JMenuItem mntmNewMenuItem_4;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Notepad frame = new Notepad();
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
	public Notepad() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 675, 449);
		
		menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		mnNewMenu = new JMenu("File");
		menuBar.add(mnNewMenu);
		
		mntmNewMenuItem = new JMenuItem("Write Txt");
		mntmNewMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			// write to the file 
			
			try {
				//FileOutputStream fileStream = new FileOutputStream("swData\\file.txt",true);
				PrintWriter writer = new PrintWriter(new FileOutputStream("swData\\file.txt",true));
				writer.println(textArea.getText());
				textArea.setText("");
				writer.close();
				//fileStream.close();
			
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
			}
		});
		mnNewMenu.add(mntmNewMenuItem);
		
		mntmNewMenuItem_1 = new JMenuItem("Read Txt");
		mntmNewMenuItem_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					//FileInputStream inputFile = new FileInputStream("swData\\file.txt");
					Scanner reader = new Scanner(new FileInputStream("swData\\file.txt"));
					String totalFileContents = "";
					while (reader.hasNext()) {
						totalFileContents += reader.nextLine()+"\n"; 
						
					}
					textArea.setText(totalFileContents);
					
				} catch (FileNotFoundException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		mnNewMenu.add(mntmNewMenuItem_1);
		
		mntmNewMenuItem_3 = new JMenuItem("Write Object");
		mntmNewMenuItem_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			// Write to binary file a student object
				Student s1 = new Student ("Tam", "123456789",24);
				try {
					FileOutputStream fileStream = new FileOutputStream("swData\\file.data",true);
					ObjectOutputStream BinaryWriter = new ObjectOutputStream(fileStream);
					BinaryWriter.writeObject(s1);
					BinaryWriter.flush(); // write whatever inside the stream into the file
				
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			
			
			}
		});
		mnNewMenu.add(mntmNewMenuItem_3);
		
		mntmNewMenuItem_4 = new JMenuItem("Read Object");
		mntmNewMenuItem_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			try {
				FileInputStream fileReader = new FileInputStream ("swData\\file.data");
				ObjectInputStream BinaryReader = new ObjectInputStream(fileReader);
				String s="";
				while(true) {
				Student rs = (Student) BinaryReader.readObject();
				
				 textArea.append(rs.getName() +"\n"+rs.getSSN()+"\n"+rs.getAge());
				 
				}
				
				 
				
			} catch (IOException | ClassNotFoundException e1) {
				// TODO Auto-generated catch block
				System.out.println("End of the file");
			}
			
			
			}
		});
		mnNewMenu.add(mntmNewMenuItem_4);
		
		mntmNewMenuItem_2 = new JMenuItem("Exit");
		mnNewMenu.add(mntmNewMenuItem_2);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		textArea = new JTextArea();
		scrollPane = new JScrollPane(textArea);
		contentPane.add(scrollPane, BorderLayout.CENTER);
		
		
		//contentPane.add(textArea, BorderLayout.NORTH);
	}

}
