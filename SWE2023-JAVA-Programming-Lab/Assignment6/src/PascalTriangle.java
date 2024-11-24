import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import javax.swing.JScrollPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javax.swing.JTextArea;
import javax.swing.JLabel;
import javax.swing.BoxLayout;
import javax.swing.JTextField;
import javax.swing.SwingWorker;
import javax.swing.JButton;
import java.awt.Font;
import javax.swing.JProgressBar;
import java.awt.Component;
import javax.swing.SwingConstants;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;

public class PascalTriangle extends JFrame implements ActionListener{ // implements ActionListener
	
	private JPanel contentPane;
	private JScrollPane scrollPane;
	private JTextArea textArea;
	private JPanel TopPanel;
	private JLabel textLabel;
	private JTextField textField;
	private JButton SumButton;
	private JButton CancelButton;
	private JPanel LowPanel;
	private JProgressBar progressBar;
	private JLabel StatusLabel;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					PascalTriangle frame = new PascalTriangle();
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
	public PascalTriangle() {
		// Main Frame
		setFont(new Font("Arial", Font.BOLD, 12));
		setTitle("Finding Pascal's triangle sum");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 478, 240);
		
		// contentPane > scrollPane > textArea
		// set contentPane option
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(0, 0, 0, 0));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		scrollPane = new JScrollPane();
		contentPane.add(scrollPane);
		// set textArea option
		textArea = new JTextArea();
		textArea.setFont(new Font("Arial", Font.PLAIN, 10));
		scrollPane.setViewportView(textArea);
		
		// TopPanel > label, text field, Buttons
		TopPanel = new JPanel();
		TopPanel.setBorder(new EmptyBorder(1, 5, 1, 8));
		contentPane.add(TopPanel, BorderLayout.NORTH);
		GridBagLayout gbl_TopPanel = new GridBagLayout();
		gbl_TopPanel.columnWidths = new int[]{162, 64, 153, 61, 0};
		gbl_TopPanel.rowHeights = new int[]{21, 0};
		gbl_TopPanel.columnWeights = new double[]{0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_TopPanel.rowWeights = new double[]{0.0, Double.MIN_VALUE};
		TopPanel.setLayout(gbl_TopPanel);
		
		// set textLabel option
		textLabel = new JLabel("Number of row in Pascal's triangle:");
		textLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		textLabel.setFont(new Font("Arial Narrow", Font.BOLD, 11));
		GridBagConstraints gbc_textLabel = new GridBagConstraints();
		gbc_textLabel.insets = new Insets(0, 12, 0, 0);
		gbc_textLabel.anchor = GridBagConstraints.WEST;
		gbc_textLabel.gridx = 0;
		gbc_textLabel.gridy = 0;
		TopPanel.add(textLabel, gbc_textLabel);
		// set textField option
		textField = new JTextField();
		textField.setFont(new Font("Arial", Font.PLAIN, 10));
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.insets = new Insets(5, 14, 1, 2);
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 1;
		gbc_textField.gridy = 0;
		TopPanel.add(textField, gbc_textField);
		textField.setColumns(10);
		// set CancelButton option
		CancelButton = new JButton("Cancel");
		CancelButton.setFont(new Font("Arial Narrow", Font.BOLD, 10));
		CancelButton.setEnabled(false);
		GridBagConstraints gbc_CancelButton = new GridBagConstraints();
		gbc_CancelButton.insets = new Insets(2, 2, 2, 6);
		gbc_CancelButton.anchor = GridBagConstraints.WEST;
		gbc_CancelButton.gridx = 3;
		gbc_CancelButton.gridy = 0;
		TopPanel.add(CancelButton, gbc_CancelButton);
		// set SumButton option
		SumButton = new JButton("Get Sum of Pascal's triangle");
		SumButton.setFont(new Font("Arial Narrow", Font.BOLD, 11));
		SumButton.addActionListener(this);
		GridBagConstraints gbc_SumButton = new GridBagConstraints();
		gbc_SumButton.insets = new Insets(2, 1, 2, 2);
		gbc_SumButton.anchor = GridBagConstraints.WEST;
		gbc_SumButton.gridx = 2;
		gbc_SumButton.gridy = 0;
		TopPanel.add(SumButton, gbc_SumButton);
		
		// LowPanel > progress bar, status label(print error or sum value)
		LowPanel = new JPanel();
		contentPane.add(LowPanel, BorderLayout.SOUTH);
		LowPanel.setLayout(new BoxLayout(LowPanel, BoxLayout.X_AXIS));
		// set progress option
		progressBar = new JProgressBar();
		progressBar.setFont(new Font("Arial", Font.PLAIN, 11));
		progressBar.setAlignmentX(Component.LEFT_ALIGNMENT);
		progressBar.setStringPainted(true);
		LowPanel.add(progressBar);
		// set statusLabel option
		StatusLabel = new JLabel("                                                                "); // default text, Match Text Spaces
		StatusLabel.setFont(new Font("Arial Narrow", Font.BOLD, 11));
		LowPanel.add(StatusLabel);
	}

	@Override
	public void actionPerformed(ActionEvent e) { // actionPerformed override
		// TODO Auto-generated method stub
		this.StatusLabel.setText("                                                                ");
		String input = this.textField.getText();
		try {
			Integer.parseInt(input); // Can make error
		}
		catch(NumberFormatException er){
			this.StatusLabel.setText(String.format("Enter an integer!%s", "                                   ")); // Match Text Spaces
			this.textArea.setText(""); this.progressBar.setValue(0); // erase textArea and progressBar
			return; // escape actionPerformed function
		}
		
		// initialize
		int NumRow = Integer.parseInt(input); // if input doesn't make error, store the integer value
		ArrayList<Integer> tmpList = new ArrayList<Integer>(); // present row list
		ArrayList<ArrayList<Integer>> allList = new ArrayList<ArrayList<Integer>>(); // go to txt file
		
		textArea.setText(""); // erase textArea
		
		for(int i = 0; i < NumRow; i++) { // from 0 to 'input value - 1'
			ArrayList<Integer> tmptmpList = new ArrayList<Integer>(); // store copy of (i-1)th row List
			tmptmpList.addAll(tmpList); // before change present row List, store to another List
			
			for(int j = 0; j < tmpList.size() - 1; j++) {
				tmpList.set(j+1, tmptmpList.get(j) + tmptmpList.get(j+1)); 
				// Nth List's j element = (N-1)th List's j element + (N-1)th List's j + 1 element 
			}
			tmpList.add(1); // add 1 to last of present List
			
			allList.add((ArrayList<Integer>) tmpList.clone()); // store present List's clone to allList 
		}
		
		SwingWorker<Integer, Integer> Worker = new SwingWorker<Integer, Integer>(){ // background process
			@Override
			protected Integer doInBackground() throws Exception {
				// TODO Auto-generated method stub		
				int totalsum = 0;
				for(int i = 0; i < NumRow; i++) { // from 0 to 'input value - 1'
					
					float status = ((float)i / NumRow) * 100; // percentage of now row
					for(int j = (int)status; j <= status + ((float)1 / NumRow) * 100; j++) {
						Thread.sleep(6); // sleep 6ms
						progressBar.setValue((int) j); // change progressBar value
					}
					
					int sum = 0;
					for(int j = 0; j < allList.get(i).size(); j++) {
						sum += allList.get(i).get(j); // calculate sum of present row
					}
					totalsum += sum;
					
					System.out.println(allList.get(i)); // present List print at console
					textArea.setText(String.format("%s%d\n", textArea.getText(), sum)); // sum of present List print at textArea(GUI)
				}
				StatusLabel.setText(String.format("Sum = %-47d", totalsum));
				return null;
			}
			
		};
		Worker.execute(); // background process run
		try {
			// false => rewrite from scratch, true => append
			PrintWriter writer = new PrintWriter(new FileOutputStream("data.txt", false)); // file open
			writer.println(allList); // store allList at file
			writer.close(); // file close
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
}
