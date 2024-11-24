import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JButton;

public class GradeCalculatorApplication extends JFrame implements ActionListener{ // implements ActionListener

	private JPanel contentPane;
	private JLabel title;
	private JPanel InputPanel;
	private JLabel course1Label;
	private JLabel course2Label;
	private JLabel course3Label;
	private JTextField course1Grade;
	private JTextField course2Grade;
	private JTextField course3Grade;
	private JTextField course1Credit;
	private JTextField course2Credit;
	private JTextField course3Credit;
	private JButton calculateButton;
	private JTextField Result;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try { // make new class variable and setVisible
					GradeCalculatorApplication frame = new GradeCalculatorApplication();
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
	public GradeCalculatorApplication() {
		setTitle("Grade Calculator");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 600, 400);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5)); // Outermost Interval
		setContentPane(contentPane);
		contentPane.setLayout(null); // absolute layout
		
		// set title label's Font, color, Bound(size and location) and add title label
		title = new JLabel("SKKU Grade Calculator");
		title.setFont(new Font("Arial", Font.BOLD, 30));
		title.setForeground(new Color(0, 0, 128));
		title.setBounds(130, 70, 340, 40);
		contentPane.add(title);
		// InputPanel -> course1~3 and text fields are in this Panel
		InputPanel = new JPanel();
		InputPanel.setBounds(12, 100, 562, 130); // location and size
		contentPane.add(InputPanel);
		InputPanel.setLayout(null); // absolute layout
		
		// course label 1 ~ 3, set font, Right Alignment, Bound(size and location) and add each label
		course1Label = new JLabel("Course 1 ");
		course1Label.setFont(new Font("Arial", Font.BOLD, 16));
		course1Label.setHorizontalAlignment(SwingConstants.RIGHT);
		course1Label.setBounds(10, 10, 140, 35);
		InputPanel.add(course1Label);
		
		course2Label = new JLabel("Course 2 ");
		course2Label.setFont(new Font("Arial", Font.BOLD, 16));
		course2Label.setHorizontalAlignment(SwingConstants.RIGHT);
		course2Label.setBounds(10, 50, 140, 35);
		InputPanel.add(course2Label);
		
		course3Label = new JLabel("Course 3 ");
		course3Label.setHorizontalAlignment(SwingConstants.RIGHT);
		course3Label.setFont(new Font("Arial", Font.BOLD, 16));
		course3Label.setBounds(10, 90, 140, 35);
		InputPanel.add(course3Label);
		
		// course grade text field 1 ~ 3, set Center Alignment, Bound(size and location) and add each text field
		course1Grade = new JTextField();
		course1Grade.setHorizontalAlignment(SwingConstants.CENTER);
		course1Grade.setBounds(150, 15, 170, 27);
		InputPanel.add(course1Grade);
		course1Grade.setColumns(10);
		
		course2Grade = new JTextField();
		course2Grade.setHorizontalAlignment(SwingConstants.CENTER);
		course2Grade.setBounds(150, 55, 170, 27);
		InputPanel.add(course2Grade);
		course2Grade.setColumns(10);
		
		course3Grade = new JTextField();
		course3Grade.setHorizontalAlignment(SwingConstants.CENTER);
		course3Grade.setBounds(150, 95, 170, 27);
		InputPanel.add(course3Grade);
		course3Grade.setColumns(10);
		
		// course credit text field 1 ~ 3, set Center Alignment, Bound(size and location) and add each text field
		course1Credit = new JTextField();
		course1Credit.setHorizontalAlignment(SwingConstants.CENTER);
		course1Credit.setBounds(330, 15, 170, 27);
		InputPanel.add(course1Credit);
		course1Credit.setColumns(10);
		
		course2Credit = new JTextField();
		course2Credit.setHorizontalAlignment(SwingConstants.CENTER);
		course2Credit.setBounds(330, 55, 170, 27);
		InputPanel.add(course2Credit);
		course2Credit.setColumns(10);
		
		course3Credit = new JTextField();
		course3Credit.setHorizontalAlignment(SwingConstants.CENTER);
		course3Credit.setBounds(330, 95, 170, 27);
		InputPanel.add(course3Credit);
		course3Credit.setColumns(10);
		
		// set calculate button's background color, font setting, Bound(size and location), ActionListener and add calculate button
		calculateButton = new JButton("Calculate GPA");
		calculateButton.setBackground(new Color(0, 0, 128));
		calculateButton.setForeground(Color.WHITE);
		calculateButton.setFont(new Font("Arial", Font.BOLD, 16));
		calculateButton.setBounds(210, 230, 180, 30);
		calculateButton.addActionListener(this);
		contentPane.add(calculateButton);
		
		// set Result text field's Center Alignment, font setting, Bound(size and location) and do not add in here.
		Result = new JTextField();
		Result.setHorizontalAlignment(SwingConstants.CENTER);
		Result.setFont(new Font("Arial", Font.BOLD, 35));
		Result.setBounds(180, 260, 240, 40);
//		contentPane.add(Result); // Click the button and add
		Result.setColumns(10);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		String[] courseGrade = new String[] { // String array has each course grade textfield's content
				this.course1Grade.getText(),
				this.course2Grade.getText(),
				this.course3Grade.getText()
		};
		int[] courseCredit = new int[] { // integer array has each course credit textfield's content, parse as Int: String -> Integer
				Integer.parseInt(this.course1Credit.getText()),
				Integer.parseInt(this.course2Credit.getText()),
				Integer.parseInt(this.course3Credit.getText())
		};
		float tmp_sum = 0;
		for(int i = 0; i < 3; i++) { 
			// Repeat 3 times, check grade of each course and add Calculation result to tmp_sum 
			if(courseGrade[i].equals("A+")) {
				tmp_sum = (float) (tmp_sum + 4.5 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("A") || courseGrade[i].equals("A0")) {
				tmp_sum = (float) (tmp_sum + 4.0 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("B+")) {
				tmp_sum = (float) (tmp_sum + 3.5 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("B") || courseGrade[i].equals("B0")) {
				tmp_sum = (float) (tmp_sum + 3.0 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("C+")) {
				tmp_sum = (float) (tmp_sum + 2.5 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("C") || courseGrade[i].equals("C0")) {
				tmp_sum = (float) (tmp_sum + 2.0 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("D+")) {
				tmp_sum = (float) (tmp_sum + 1.5 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("D") || courseGrade[i].equals("D0")) {
				tmp_sum = (float) (tmp_sum + 1.0 * courseCredit[i]);
			}
			else if(courseGrade[i].equals("F")) {
				tmp_sum = (float) (tmp_sum + 0);
			}
		}
		// tmp_sum in this line is sum of every course's grade, therefore we should divide with sum of Credits
		tmp_sum = tmp_sum / (courseCredit[0] + courseCredit[1] + courseCredit[2]);
		// Store the calculated tmp_sum value to Result text field, using String format
		this.Result.setText( String.format("Your GPA: %.1f", tmp_sum) );
		// Add the Result text field
		contentPane.add(Result);
	}

}
