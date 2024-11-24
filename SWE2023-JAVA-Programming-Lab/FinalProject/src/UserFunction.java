import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class UserFunction extends User{
	UserFunction(String tag, String name, String id, String password, String email){
		super(tag, name, id, password, email);
	}
	UserFunction(String tag, String id, String password) {
		super(tag, id, password);
		// TODO Auto-generated constructor stub
	}

	public String login() { // login method : parameter : id, password text, return error number or userTag
		String str;
		BufferedReader in;
		boolean idSuccess = false;
		try {
			in = new BufferedReader(new FileReader("DATA/users.txt"));
			while ((str = in.readLine()) != null) { // read line by line
				String[] splits = str.split(" ");
				if (super.getId().equals(splits[2])) { // match to 3rd element : ID
					idSuccess = true;
					if (super.getPassword().equals(splits[3])) { // match to 4th element : password
						return splits[0]; // return user tag
					} else {
						return "-1"; // -1 means password error
					}
				}
			}
			if (!idSuccess) { // print when ID does not exist
				return "-2"; // -2 means ID exist error
			}
		} catch (FileNotFoundException e2) {
			BufferedWriter fw;
			try { // if file does not exist, make file
				fw = new BufferedWriter(new FileWriter("DATA/users.txt", true));
				fw.write("");
	            fw.flush();
	            fw.close();
	            return "-2";
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		return null;
	}
	
	public boolean register(String retypePasswordText) {
		// register method : parameter : name, id, password, retype password, email return : success or fail boolean
		File f1 = new File("DATA/users.txt");
		String str = null;
		String tag = null;
		if (super.getPassword().equals(retypePasswordText)) { // check password part and retype password part
			BufferedWriter writer = null;
			try {
				writer = new BufferedWriter(new FileWriter("DATA/users.txt", true)); // open writer
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			BufferedReader in;
			try {
				in = new BufferedReader(new FileReader("DATA/users.txt")); // open reader
				while ((str = in.readLine()) != null) { // read line by line
					String[] splits = str.split(" "); // split to get last user's tag
					tag = splits[0]; // find the new tag number
				}
			} catch (FileNotFoundException e2) {
				e2.printStackTrace();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			str = " " + super.getName() + " "
					+ super.getId() + " " + super.getPassword() + " "
					+ super.getEmail() + "\n";;
			if (tag == null) { // if file does not exist, then first tag is set to 0
				str = "0" + str;
			} else { // else, tag is last user's tag + 1
				str = String.format("%d", Integer.parseInt(tag) + 1) + str;
			}
			try {
				writer.write(str); // write to users.txt file
				writer.close(); // and close
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		} 
		else { // password != retype password
			return false; // return false : fail
		}
		return true;
	}
}
