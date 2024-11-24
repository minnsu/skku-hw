import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.AbstractButton;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;

public class ButtonFrame extends JFrame implements ActionListener{
	private AbstractButton plainJButton ; // button with just text
		// Abstract Button - Toggle button : on/off, Check button : check box on/off, Radio button : circle button ○, ●
	private JButton fancyJButton ; // button with icons
	// ButtonFrame adds JButtons to JFrame
	
	public ButtonFrame() {
		super("Testing Buttons");
		setLayout(new FlowLayout());
		
		plainJButton = new JButton("Plain Button");
		add(plainJButton);
		
		Icon bug1 = new ImageIcon(getClass().getResource("bug1.gif"));
		Icon bug2 = new ImageIcon(getClass().getResource("bug2.gif"));
		fancyJButton = new JButton("Fancy Button", bug1); // 기본 이미지
		fancyJButton.setRolloverIcon(bug2); // 커서가 위에 있을 때 바꿀 이미지
		add(fancyJButton);
		
		ButtonHandler handler = new ButtonHandler();
		fancyJButton.addActionListener(this); //handler);
		plainJButton.addActionListener(this); //handler);
		
	}
	
	private class ButtonHandler implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			JOptionPane.showMessageDialog(ButtonFrame.this, String.format("You pressed: %s", e.getActionCommand()));
				//	, "Title of the message", JOptionPane.WARNING_MESSAGE );
				// parameter1 : parentComponent: 불러온 창을 표시하는 것?
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == fancyJButton) {
			JOptionPane.showMessageDialog(ButtonFrame.this, "fancyJutton"
					, "fancyJButton", JOptionPane.INFORMATION_MESSAGE );
			// parameter1 : parentComponent: 불러온 창을 표시하는 것?
		}
		else if(e.getSource() == plainJButton) {
			JOptionPane.showMessageDialog(ButtonFrame.this, "Plain button"
					, "Plain button action", JOptionPane.INFORMATION_MESSAGE );
		}
	}
	
}
