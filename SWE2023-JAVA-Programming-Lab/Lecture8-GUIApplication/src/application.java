import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import java.awt.GridLayout;
import javax.swing.JLabel;
import java.awt.Color;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

public class application extends JFrame implements ActionListener {

	private JPanel contentPane;
	private JButton ResetScoreButton;
	private JPanel panel;
	private JLabel lblNewLabel;
	private JLabel lblNewLabel_1;
	private JLabel RedScoreLabel;
	private JLabel BlueScoreLabel;
	private JButton RedScoreButton;
	private JButton BlueScoreButton;
	private int redcounter = 0;
	private int bluecounter = 0;
	
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					application frame = new application();
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
	public application() {
		setTitle("Scoring Application");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 350, 220);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		ResetScoreButton = new JButton("Reset Score");
		contentPane.add(ResetScoreButton, BorderLayout.SOUTH);
		
		panel = new JPanel();
		panel.setBackground(UIManager.getColor("Panel.background"));
		contentPane.add(panel, BorderLayout.CENTER);
		panel.setLayout(new GridLayout(3, 2, 0, 0));
		
		lblNewLabel = new JLabel("Red Team");
		lblNewLabel.setFont(new Font("±¼¸²", Font.PLAIN, 16));
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setForeground(Color.RED);
		panel.add(lblNewLabel);
		
		lblNewLabel_1 = new JLabel("Blue Tem");
		lblNewLabel_1.setFont(new Font("±¼¸²", Font.PLAIN, 16));
		lblNewLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_1.setForeground(Color.BLUE);
		panel.add(lblNewLabel_1);
		
		RedScoreLabel = new JLabel("0");
		RedScoreLabel.setFont(new Font("±¼¸²", Font.PLAIN, 20));
		RedScoreLabel.setHorizontalAlignment(SwingConstants.CENTER);
		panel.add(RedScoreLabel);
		
		BlueScoreLabel = new JLabel("0");
		BlueScoreLabel.setFont(new Font("±¼¸²", Font.PLAIN, 20));
		BlueScoreLabel.setHorizontalAlignment(SwingConstants.CENTER);
		panel.add(BlueScoreLabel);
		
		RedScoreButton = new JButton("Red Score");
		RedScoreButton.setToolTipText("");
		RedScoreButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		panel.add(RedScoreButton);
		
		BlueScoreButton = new JButton("Blue Score");
		panel.add(BlueScoreButton);
		
		RedScoreButton.addActionListener(this);
		BlueScoreButton.addActionListener(this);
		ResetScoreButton.addActionListener(this);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource() == RedScoreButton) {
			redcounter++; 
			RedScoreLabel.setText(String.format("%d", redcounter));
		}
		else if(e.getSource() == BlueScoreButton) {
			bluecounter++;
			BlueScoreLabel.setText(String.format("%d", bluecounter));
		}
		else if(e.getSource() == ResetScoreButton) {
			redcounter = 0; bluecounter = 0;
			RedScoreLabel.setText(String.format("%d", redcounter));
			BlueScoreLabel.setText(String.format("%d", bluecounter));
		}
	}

}
