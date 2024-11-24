import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.FlowLayout;

import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;


public class FilesProcessing extends JFrame {

	private JPanel contentPane;
	private JTextField textField;
	JPanel panel;
	JScrollPane scrollPane;
	JLabel lblData;
	JTextArea readData;
	JButton btnSave;
	private JButton btnRead;
	private JPanel panel_1;
	private JButton btnBSave;
	private JButton btnBread;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					FilesProcessing frame = new FilesProcessing();
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
	public FilesProcessing() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		 panel = new JPanel();
		contentPane.add(panel, BorderLayout.NORTH);
		
		lblData = new JLabel("Data");
		panel.add(lblData);
		
		textField = new JTextField();
		panel.add(textField);
		textField.setColumns(10);
		
		btnSave = new JButton("Save");
		btnSave.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				DoWrite();
			}

			private void DoWrite() {
			
				try {
					//FileWriter fileObject =new FileWriter("data.txt",true);
					FileOutputStream fileObject =new FileOutputStream("data.txt",true);
					 
					PrintWriter x = new PrintWriter(fileObject);
					x.println(textField.getText()+"\n");
					x.close();
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				 
			}
		});
		panel.add(btnSave);
		
		btnRead = new JButton("Read");
		btnRead.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				doRead();
			}

			private void doRead() {
				
				try {
					FileInputStream fileObject = new FileInputStream("data.txt");
					Scanner x = new Scanner(fileObject);
					String s =new String();
					while(x.hasNext()){
						s = s+""+x.nextLine();
					}
					JOptionPane.showMessageDialog(null, s);
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
			}
		});
		panel.add(btnRead);
		
		readData = new JTextArea();scrollPane = new JScrollPane(readData);
		contentPane.add(scrollPane, BorderLayout.CENTER);
		
		panel_1 = new JPanel();
		contentPane.add(panel_1, BorderLayout.SOUTH);
		
		btnBSave = new JButton("BSave");
		btnBSave.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				doBWrite();
				
			}

			private void doBWrite() {
				ArrayList<DataCollection> list = new ArrayList<DataCollection>();
				list.add(new DataCollection(0, 0));
				list.add(new DataCollection(0, 1));
				list.add(new DataCollection(0, 2));
				list.add(new DataCollection(0, 3));
				list.add(new DataCollection(1, 0));
				list.add(new DataCollection(2, 0));
				list.add(new DataCollection(3, 0));
				//send this list to Binary file
				File f = new File("file.dat");
				ObjectOutputStream objectToStream;
				FileOutputStream BinaryOutFileStream;
				try {
					 BinaryOutFileStream = new FileOutputStream(f);
					 objectToStream = new ObjectOutputStream(BinaryOutFileStream);
					
					for (DataCollection d : list){
						objectToStream.writeObject(d);
					}
					BinaryOutFileStream.close();
					objectToStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		});
		panel_1.add(btnBSave);
		
		btnBread = new JButton("BRead");
		btnBread.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
			
			doBRead();
			
			}

			private void doBRead()  {
				File f = new File("file.dat");
				FileInputStream BinaryInFileStream;
				ObjectInputStream objectToStream;
				try {
					 BinaryInFileStream = new FileInputStream(f);
					 objectToStream = new ObjectInputStream(BinaryInFileStream);
					DataCollection obj =(DataCollection)objectToStream.readObject();;
					while (obj!=null){
						readData.append("("+obj.getX()+","+obj.getY()+")\n");
						obj = (DataCollection)objectToStream.readObject();
					}
					BinaryInFileStream.close();
					objectToStream.close();
					
				} catch (Exception e) {
					// TODO Auto-generated catch block
					//e.printStackTrace();
				}
				
			}
		});
		panel_1.add(btnBread);
		
		 
		 
		//contentPane.add(textArea, BorderLayout.SOUTH);
	}

}
