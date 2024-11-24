import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public abstract class User{
	private String tag;
	private String name;
	private String id;
	private String password;
	private String email;
	// tag's getter/setter
	public String getTag() {
		return tag;
	}
	public void setTag(String tag) {
		this.tag = tag;
	}
	// name's getter/setter
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	// id's getter/setter
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	// password's getter/setter
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	// email's getter/setter
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	// constructor with 5 parameter : tag, name, id, password, email
	User(String tag, String name, String id, String password, String email){
		this.tag = tag;
		this.name = name;
		this.id = id;
		this.password = password;
		this.email = email;
	}
	// constructor with 3 parameter : tag, id, password
	User(String tag, String id, String password){
		this.tag = tag;
		this.name = null;
		this.id = id;
		this.password = password;
		this.email = null;
	}
	
	// abstract method, these are implemented in UserFunction class
	public abstract boolean register(String retypePassword);
	public abstract String login();
}
