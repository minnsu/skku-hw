package com.phonebook;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.ListModel;
import javax.swing.JList;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Phonebook extends JFrame {

	private JPanel contentPane;
	private JMenuBar menuBar;
	private JMenu mnActionMenu;
	private JMenu mnNewMenu_1;
	private JMenuItem mnAddMenuItem;
	private JMenuItem mnRemoveDMenuItem;
	private JMenuItem mnDeleteMenuItem;
	private JMenuItem mnExitMenuItem;
	private JMenuItem mnSortMenuItem;
	private JMenuItem mnShuffleMenuItem;
	private JMenuItem mnDuplicateMenuItem;
	private JScrollPane scrollPane;
	private JList list;
	private JFrame frame = Phonebook.this;
	List<String> listData = new ArrayList<String>();
	DefaultListModel<String> listModel = new DefaultListModel<String>();
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Phonebook frame = new Phonebook();
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
	public Phonebook() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 330, 371);
		
		menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		mnActionMenu = new JMenu("Action");
		menuBar.add(mnActionMenu);
		
		mnAddMenuItem = new JMenuItem("Add");
		mnActionMenu.add(mnAddMenuItem);
		
		mnDeleteMenuItem = new JMenuItem("Delete");
		mnActionMenu.add(mnDeleteMenuItem);
		
		mnExitMenuItem = new JMenuItem("Exit");
		mnActionMenu.add(mnExitMenuItem);
		
		mnNewMenu_1 = new JMenu("Collections");
		menuBar.add(mnNewMenu_1);
		
		mnSortMenuItem = new JMenuItem("Sort");
		mnSortMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			Collections.sort(listData);
			listModel.clear();
			listModel.addAll(listData);
			
			}
		});
		mnNewMenu_1.add(mnSortMenuItem);
		
		mnShuffleMenuItem = new JMenuItem("Shuffle");
		mnNewMenu_1.add(mnShuffleMenuItem);
		mnShuffleMenuItem.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				Collections.shuffle(listData);
				listModel.clear();
				listModel.addAll(listData);
				
			}
		});
		mnDuplicateMenuItem = new JMenuItem("Duplicate");
		mnNewMenu_1.add(mnDuplicateMenuItem);
		
		mnRemoveDMenuItem = new JMenuItem("Remove Duplicate");
		mnNewMenu_1.add(mnRemoveDMenuItem);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		// fill the ArrayList with phone contacts
				for(String conact : Contact.rawData) {
					
					listData.add(conact);
				}
				listModel.addAll(listData);
		
		list = new JList(listModel);
		list.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
			
			int index = list.getSelectedIndex();
			String value = listModel.get(index);
			String [] splits = value.split(":");
			EditDialog editConact = new EditDialog(frame, splits[0], splits[1]);
			String ModifiedContact= editConact.getName()+":"+editConact.getPhone();
			//change the data inside ArrayList
			listData.set(index, ModifiedContact);
			// replace all data of the model with the new ArrayList
			listModel.clear();
			listModel.addAll(listData);
			
			System.out.println(value);
			}
		});
		scrollPane = new JScrollPane(list);
		contentPane.add(scrollPane, BorderLayout.CENTER);
		
		
		
		//contentPane.add(list, BorderLayout.NORTH);
	}

}
