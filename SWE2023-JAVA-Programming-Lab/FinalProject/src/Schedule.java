import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.JScrollPane;
import javax.swing.JList;
import javax.swing.JRadioButton;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.SwingWorker;
import javax.swing.JTextField;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JDialog;

import java.util.Date;
import java.text.SimpleDateFormat;

public class Schedule extends JFrame {

	private JPanel contentPane;
	private JMenuBar menuBar;
	private JMenu utilityMenu;
	private JMenuItem calculatorMenuItem;
	private JMenuItem notepadMenuItem;
	private JPanel schedulePanel;
	private JTable table;
	private JPanel panel;
	private JScrollPane scrollPane;
	private JList list;
	private JRadioButton monRB;
	private JRadioButton tueRB;
	private JRadioButton wedRB;
	private JRadioButton thuRB;
	private JRadioButton friRB;
	private JRadioButton satRB;
	private JRadioButton sunRB;
	private JLabel scheduleNameLabel;
	private JTextField scheduleTextField;
	private JTextField startTimeTextField;
	private JTextField endTimeTextField;
	private JLabel timeLabel;
	private JLabel betweenTimeLabel;
	private JButton addToScheduleButton;
	private JButton deleteButton;
	private JButton moveToTodoDone;

	private JFrame frame = Schedule.this;
	List<String> listData = new ArrayList<String>();
	DefaultListModel<String> listModel = new DefaultListModel<String>();
	private String header[] = { "Time", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	private String contents[][] = new String[24][8];

	public String[] userSchedule;
	private String userTag;
	private JMenu loginRegisterMenu;
	private JMenuItem loginMenuItem;
	private JMenuItem registerMenuItem;
	private JButton refreshButton;
	private JScrollPane scrollPane_2;
	SwingWorker<Integer, Integer> folderMaker = new SwingWorker<Integer, Integer>() {
		@Override
		protected Integer doInBackground() throws Exception {
			// TODO Auto-generated method stub
			// folder make
			File Folder1 = new File("DATA/");
			if (!Folder1.exists()) {
				Folder1.mkdir();
			}
			File Folder2 = new File("DATA/usertext");
			if (!Folder2.exists()) {
				Folder2.mkdir();
			}
			return null;
		}
	};
	SwingWorker<Integer, Integer> fileMaker = new SwingWorker<Integer, Integer>() {
		@Override
		protected Integer doInBackground() throws Exception {
			// TODO Auto-generated method stub
			// folder make
			File usersInfoFile = new File("DATA/users.txt");
			if (!usersInfoFile.exists()) {
				usersInfoFile.createNewFile();
			}
			File scheduleFile = new File("DATA/userSchedule.txt");
			if (!scheduleFile.exists()) {
				scheduleFile.createNewFile();
			}
			return null;
		}
	};

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Schedule frame = new Schedule();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 * 
	 * @throws IOException
	 */
	public Schedule() throws IOException {
		setTitle("Weekly Scheduler");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 700, 660);
		// make menu bar, menu bar has register, login, calculator and notepad
		menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		// make folder "DATA/" and "DATA/usertext/"
		folderMaker.execute();
		while (!folderMaker.isDone()) { // wait until make folder is done
		}
		fileMaker.execute(); // make file "DATA/users.txt" and "DATA/userSchedule.txt"
		
		// add loginRegister menu in menu bar
		loginRegisterMenu = new JMenu("Login & Register");
		menuBar.add(loginRegisterMenu);
		// add login menu item in loginRegister menu
		loginMenuItem = new JMenuItem("Login");
		loginMenuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if login menu item is clicked
				// TODO Auto-generated method stub
				LoginDialog login = new LoginDialog(frame); // open login dialog
				userTag = login.userTag; // store schedule's instance userTag as logined user's tag number
				System.out.println("Logined user tag : " + userTag); // and print log in console.
				try {
					refresh(true); // first refresh : table refresh, this function refresh(read) file and table
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		loginRegisterMenu.add(loginMenuItem);
		// add register menu item in loginRegister menu
		registerMenuItem = new JMenuItem("Register");
		registerMenuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if register menu item is clicked
				// TODO Auto-generated method stub
				JDialog register = new RegisterDialog(frame); // open register dialog with polymorphism. 
				// because register don't need call another functionalities by Schedule page.
				// Login after Register
				LoginDialog login = new LoginDialog(frame);
				userTag = login.userTag; // and also set userTag
				System.out.println("Logined user tag : " + userTag); // with log to console.
				try {
					refresh(true); // first refresh : table refresh, this function refresh(read) file and table
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		loginRegisterMenu.add(registerMenuItem);

		// add utility menu in menu bar
		utilityMenu = new JMenu("utility");
		menuBar.add(utilityMenu);
		
		// add calculator menu item in utility menu
		calculatorMenuItem = new JMenuItem("Calculator");
		calculatorMenuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if calculator menu item is clicked
				// TODO Auto-generated method stub
				JDialog calc = new Calculator(frame); // call Calculator class with polymorphism.
			}
		});
		utilityMenu.add(calculatorMenuItem);

		// add notepad menu item in utility menu
		notepadMenuItem = new JMenuItem("Notepad");
		notepadMenuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if notepad menu item is clicked
				// TODO Auto-generated method stub
				if (userTag == null) { // if user Tag is not set. then ask to login
					JOptionPane.showMessageDialog(null, "If you want use notepad, then you should login first!");
				} else { // if userTag has valid value. then open notepad class with polymorphism.
					JDialog note = new Notepad(frame, userTag);
				}
			}
		});
		utilityMenu.add(notepadMenuItem);
		// contentPane has schedulePanel
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		// schedulePanel has table
		schedulePanel = new JPanel();
		schedulePanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		schedulePanel.setBounds(0, 0, 686, 325);
		contentPane.add(schedulePanel);
		schedulePanel.setLayout(new BorderLayout(0, 0));

		/*
		 * {"08:00", }, {"09:00", }, {"10:00", }, {"11:00", }, {"12:00", }, {"13:00", },
		 * {"14:00", }, {"15:00", }, {"16:00", }, {"17:00", }, {"18:00", }, {"19:00", },
		 * {"20:00", }, {"21:00", }, {"22:00", }, {"23:00", }, {"00:00", }, {"01:00", },
		 * {"02:00", }, {"03:00", }, {"04:00", }, {"05:00", }, {"06:00", }, {"07:00", }
		 * ;
		 */
		// set time columns
		contents[0][0] = "08:00";
		contents[1][0] = "09:00";
		contents[2][0] = "10:00";
		contents[3][0] = "11:00";
		contents[4][0] = "12:00";
		contents[5][0] = "13:00";
		contents[6][0] = "14:00";
		contents[7][0] = "15:00";
		contents[8][0] = "16:00";
		contents[9][0] = "17:00";
		contents[10][0] = "18:00";
		contents[11][0] = "19:00";
		contents[12][0] = "20:00";
		contents[13][0] = "21:00";
		contents[14][0] = "22:00";
		contents[15][0] = "23:00";
		contents[16][0] = "00:00";
		contents[17][0] = "01:00";
		contents[18][0] = "02:00";
		contents[19][0] = "03:00";
		contents[20][0] = "04:00";
		contents[21][0] = "05:00";
		contents[22][0] = "06:00";
		contents[23][0] = "07:00";
		// scrollPane_2 has table
		scrollPane_2 = new JScrollPane();
		schedulePanel.add(scrollPane_2, BorderLayout.CENTER);

		table = new JTable(contents, header);
		scrollPane_2.setViewportView(table);

		panel = new JPanel();
		panel.setBorder(new EmptyBorder(5, 5, 5, 5));
		panel.setBounds(0, 321, 686, 116);
		contentPane.add(panel);
		panel.setLayout(new BorderLayout(0, 0));

		scrollPane = new JScrollPane();
		panel.add(scrollPane);
		
		// make JList with listModel
		list = new JList(listModel);
		list.setFont(new Font("Arial", Font.PLAIN, 14));
		scrollPane.setViewportView(list);
		// Monday Radio Button
		monRB = new JRadioButton("Mon");
		monRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		monRB.setBounds(8, 435, 58, 23);
		contentPane.add(monRB);
		// Tuesday Radio Button
		tueRB = new JRadioButton("Tue");
		tueRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		tueRB.setBounds(8, 458, 58, 23);
		contentPane.add(tueRB);
		// Wednesday Radio Button
		wedRB = new JRadioButton("Wed");
		wedRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		wedRB.setBounds(8, 483, 58, 23);
		contentPane.add(wedRB);
		// Thursday Radio Button
		thuRB = new JRadioButton("Thu");
		thuRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		thuRB.setBounds(8, 504, 58, 23);
		contentPane.add(thuRB);
		// Friday Radio Button
		friRB = new JRadioButton("Fri");
		friRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		friRB.setBounds(8, 527, 58, 23);
		contentPane.add(friRB);
		// Saturday Radio Button
		satRB = new JRadioButton("Sat");
		satRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		satRB.setBounds(8, 550, 58, 23);
		contentPane.add(satRB);
		// Sunday Radio Button
		sunRB = new JRadioButton("Sun");
		sunRB.setFont(new Font("DejaVu Sans Mono", Font.PLAIN, 14));
		sunRB.setBounds(8, 573, 58, 23);
		contentPane.add(sunRB);

		// add schedule name label
		scheduleNameLabel = new JLabel("Enter a schedule :  ");
		scheduleNameLabel.setFont(new Font("Arial", Font.BOLD, 12));
		scheduleNameLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		scheduleNameLabel.setBounds(74, 440, 140, 30);
		contentPane.add(scheduleNameLabel);
		// add schedule name text field
		scheduleTextField = new JTextField();
		scheduleTextField.setHorizontalAlignment(SwingConstants.CENTER);
		scheduleTextField.setBounds(216, 440, 465, 30);
		contentPane.add(scheduleTextField);
		scheduleTextField.setColumns(10);
		// add start time text field
		startTimeTextField = new JTextField();
		startTimeTextField.setHorizontalAlignment(SwingConstants.CENTER);
		startTimeTextField.setBounds(216, 480, 210, 30);
		contentPane.add(startTimeTextField);
		startTimeTextField.setColumns(10);
		// add end time text field
		endTimeTextField = new JTextField();
		endTimeTextField.setHorizontalAlignment(SwingConstants.CENTER);
		endTimeTextField.setBounds(470, 480, 210, 30);
		contentPane.add(endTimeTextField);
		endTimeTextField.setColumns(10);
		// add time label
		timeLabel = new JLabel("Time (Hour, from ~ to) :  ");
		timeLabel.setFont(new Font("Arial", Font.BOLD, 12));
		timeLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		timeLabel.setBounds(74, 480, 140, 30);
		contentPane.add(timeLabel);
		// add "~" label
		betweenTimeLabel = new JLabel("~");
		betweenTimeLabel.setHorizontalAlignment(SwingConstants.CENTER);
		betweenTimeLabel.setBounds(425, 480, 45, 30);
		contentPane.add(betweenTimeLabel);
		// add add Schedule Button
		addToScheduleButton = new JButton("Add to schedule");
		addToScheduleButton.setBounds(405, 545, 136, 45);
		addToScheduleButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if add button is clicked
				if (scheduleTextField.getText().length() == 0 || startTimeTextField.getText().length() == 0
						|| endTimeTextField.getText().length() == 0) { // if any of textfield has invalid input then ask to check the input
					JOptionPane.showMessageDialog(null, "There is unvalid input. Please check your input.");
					return;
				}
				// else
				String addInput = "";
				String days = "";
				// check and add to string about days							all radio buttons set to unselected
				days = days + (monRB.isSelected() ? "Mon " : "");				monRB.setSelected(false);
				days = days + (tueRB.isSelected() ? "Tue " : "");				tueRB.setSelected(false);
				days = days + (wedRB.isSelected() ? "Wed " : "");				wedRB.setSelected(false);
				days = days + (thuRB.isSelected() ? "Thu " : "");				thuRB.setSelected(false);
				days = days + (friRB.isSelected() ? "Fri " : "");				friRB.setSelected(false);
				days = days + (satRB.isSelected() ? "Sat " : "");				satRB.setSelected(false);
				days = days + (sunRB.isSelected() ? "Sun " : "");				sunRB.setSelected(false);	
				// make input string format : tag scheduleName          startTime          endTime           daysString
				addInput = userTag + " " + scheduleTextField.getText() + "          " + startTimeTextField.getText()
						+ "          " + endTimeTextField.getText() + "          " + days;
				scheduleTextField.setText("");
				startTimeTextField.setText("");
				endTimeTextField.setText("");
				// erase all text field

				listModel.addElement(addInput); // add the string to listModel
				try {
					refresh(false); // not first refresh : table refresh, this function refresh(read) file and table
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		contentPane.add(addToScheduleButton);
		// add delete scheduel button
		deleteButton = new JButton("Delete");
		deleteButton.setBounds(545, 545, 136, 45);
		deleteButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if delete button is clicked
				if (list.isSelectionEmpty()) { // if there is no selected element
					JOptionPane.showMessageDialog(null, "Please select on list's element."); // show error message
					return;
				}
				// else
				int index = list.getSelectedIndex();
				listModel.removeElementAt(index);
				// find the selected index and remove from listModel
				try {
					refresh(false); // not first refresh : table refresh, this function refresh(read) file and table
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		contentPane.add(deleteButton);
		// add open Todo/Done List button
		moveToTodoDone = new JButton("Open Todo/Done List");
		moveToTodoDone.setBounds(125, 568, 276, 22);
		moveToTodoDone.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) { // if move Todo/Done button is clicked
				// TODO Auto-generated method stub
				TodoDoneList tdl = new TodoDoneList(frame); // open TodoDoneList class
			}
		});
		contentPane.add(moveToTodoDone);
		// add refresh button
		refreshButton = new JButton("Refresh Schedule");
		refreshButton.setBounds(125, 545, 276, 22);
		refreshButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) { // if refresh button is clicked
				try {
					refresh(false); // not first refresh : table refresh, this function refresh(read) file and table
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		contentPane.add(refreshButton);

	}

	private void refresh(boolean isFirst) throws IOException {
		// make first refresher swing worker
		SwingWorker<Integer, Integer> firstRefresher = new SwingWorker<Integer, Integer>() {
			@Override
			protected Integer doInBackground() throws Exception {
				// TODO Auto-generated method stub
				list.removeAll();
				listData.removeAll(listData);
				listModel.removeAllElements();
				// remove all data
				BufferedReader in = new BufferedReader(new FileReader("DATA/userSchedule.txt")); // select file
				String str;
				while ((str = in.readLine()) != null) { // read line by line until end
					String[] splits = str.split(" "); // split the line string with only one space " " -> split[0] : tag, split[1] : rest string
					if (splits[0].equals(userTag)) { // if line string's tag part is equal to logined user's tag
						listData.add(str); // then add the line string to listData
					}
				}
				listModel.addAll(listData); // add all data to listModel
				in.close();
				refresh(false); // not first refresh
				return null;
			}
		};
		// make not first refresher swing worker
		SwingWorker<Integer, Integer> notFirstRefresher = new SwingWorker<Integer, Integer>() {
			@Override
			protected Integer doInBackground() throws Exception {
				// TODO Auto-generated method stub
				BufferedReader fr = new BufferedReader(new FileReader("DATA/userSchedule.txt")); // select file
				String others = "";
				String other;
				while ((other = fr.readLine()) != null) { // read line by line until end
					String[] splits = other.split(" "); // split the line string with only one space " " -> split[0] : tag, split[1] : rest string
					if (splits[0].equals(userTag)) { // if line string's tag part is equal to logined user's tag
						continue; // then continue the loop
					}
					// else : other users line string
					others = others + other + "\n"; // add to others string variable
				}
				fr.close();
				String str = "";
				for (int i = 0; i < listModel.size(); i++) { // read listModel's data
					str = str + listModel.elementAt(i) + "\n"; // add to str line by line : logined user's data
				}
				BufferedWriter fw = new BufferedWriter(new FileWriter("DATA/userSchedule.txt", false)); // open file with false option : write from scratch
				fw.write(others + str); // write others data + logined user's valid data
				fw.close();
				tableRefresh(); // call table refresh function
				return null;
			}
		};
		if (isFirst) { // if first refresh situation
			firstRefresher.execute(); // call firstRefresher swing worker
		} else {
			notFirstRefresher.execute(); // else call notFirstRefresher swing worker
		}
	}

	private void tableRefresh() throws IOException {
		BufferedReader fr = new BufferedReader(new FileReader("DATA/userSchedule.txt")); // select file
		String other;
		for (int i = 0; i < 24; i++) {
			for (int j = 1; j < 8; j++) {
				contents[i][j] = ""; // erase all data in table except time column
			}
		}
		while ((other = fr.readLine()) != null) { // read line by line
			String[] splits_line = other.split("          "); // split with 10 space "          "  
			// splits[0] = <tag> <task_text>, splits[1] = <start_time> splits[2] = <end_time> splits[3] = <day_string>
			if (!splits_line[0].split(" ")[0].equals(userTag)) { // if tag part of split[0] is equal to logined user's tag
				continue; // continue this loop
			}
			String[] splits_day = splits_line[3].split(" "); // split day part string
			int day_idx = 0; // day idx
			for (int i = 0; i < splits_day.length; i++) { // iterate number of days
				// select day by string compare
				if (splits_day[i].equals("Mon")) {
					// contents[1][?]
					day_idx = 1;
				} else if (splits_day[i].equals("Tue")) {
					// contents[2][?]
					day_idx = 2;
				} else if (splits_day[i].equals("Wed")) {
					// contents[3][?]
					day_idx = 3;
				} else if (splits_day[i].equals("Thu")) {
					// contents[4][?]
					day_idx = 4;
				} else if (splits_day[i].equals("Fri")) {
					// contents[5][?]
					day_idx = 5;
				} else if (splits_day[i].equals("Sat")) {
					// contents[6][?]
					day_idx = 6;
				} else if (splits_day[i].equals("Sun")) {
					// contents[7][?]
					day_idx = 7;
				}
				int start = (Integer.parseInt(splits_line[1]) + 16) % 24; // find start idx
				int end = (Integer.parseInt(splits_line[2]) + 16) % 24; // find end idx
				if (start <= end) { // in general situation
					for (int j = start; j < end; j++) {
						contents[j][day_idx] = splits_line[0].substring(splits_line[0].split(" ")[0].length() + 1);
					}
				} else { // if index out of lange occur
					for (int j = end - 1; j >= 0; j--) { // 0 ~ end idx
						contents[j][day_idx] = splits_line[0].substring(splits_line[0].split(" ")[0].length() + 1);
					}
					for (int j = start; j < 24; j++) { // start ~ 23 idx
						contents[j][day_idx] = splits_line[0].substring(splits_line[0].split(" ")[0].length() + 1);
					}
				}
			}
		}
		
		// call date
		Date now = new Date(System.currentTimeMillis());
		SimpleDateFormat getDayAndHour = new SimpleDateFormat("u HH"); // u : number of day(Mon : 1 ~ Sun : 7), HH : hour
		String splitDayAndHour[] = getDayAndHour.format(now).split(" "); // split day and hour
		int dayIdx = Integer.parseInt(splitDayAndHour[0]); // parse day part as integer
		int hourIdx = (Integer.parseInt(splitDayAndHour[1]) + 16) % 24; // parse hour part as integer valid index
		if (contents[hourIdx][dayIdx].length() == 0) { // if there is no string(schedule) in now time
			contents[hourIdx][dayIdx] = "-- NOW --"; // set the table cell string as "-- NOW --"
		} else {
			contents[hourIdx][dayIdx] = "¡Ú : " + contents[hourIdx][dayIdx]; // else add star letter infront of present table cell string
		}
		fr.close();
	}
}
