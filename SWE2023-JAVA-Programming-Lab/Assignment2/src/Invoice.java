
public class Invoice {
	/*
	 * Instance : ProductName, Quantity, Price
	 * Method : get, set functions, getInvoiceAmount
	 * */
	String ProductName;
	int Quantity;
	double Price;
	
	public Invoice(String ProductName, int Quantity, double Price) { // constructor(String, int, double)
		this.setProductName(ProductName);
		this.setQuantity(Quantity);
		this.setPrice(Price);
	}

	// get, set function of ProductName
	public String getProductName() {
		return ProductName;
	}
	public void setProductName(String ProductName) {
		this.ProductName = ProductName;
	}

	// get, set function of Quantity
	public int getQuantity() {
		return Quantity;
	}
	public void setQuantity(int Quantity) {
		this.Quantity = Quantity;
	}

	// get, set function of Price
	public double getPrice() {
		return Price;
	}
	public void setPrice(double Price) {
		this.Price = Price;
	}
	
	// get Invoice Amount: return Quantity * Price
	public double getInvoiceAmount() {
		return getQuantity() * getPrice();
	}
	
}
