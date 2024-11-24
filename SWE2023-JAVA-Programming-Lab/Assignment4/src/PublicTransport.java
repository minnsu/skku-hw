
public abstract class PublicTransport implements Payable {
	
	public String model;
	
	public PublicTransport(String model) { // constructor(String)
		// use set functions of instance variable
		this.setModel(model);
	}
	
	// get&set functions of model
	public String getModel() {
		return model;
	}
	public void setModel(String model) {
		this.model = model;
	}

	public void getDetail() {
		System.out.println("========================="); // '=' * 25
		System.out.println(this);
	}

	@Override
	public String toString() {
		return "Model: " + this.getModel(); // Model: model
	}
}
