package Example2Interfaces;
public class Invoice implements Payable {
	private String partNumber;
	private String partDescription;
	private int quantity;
	private double pricePerItem;

	// four-argument constructor
	public Invoice(String part, String description, int count, double price) {
		partNumber = part;
		partDescription = description;
		setQuantity(count); // validate and store quantity
		setPricePerItem(price);
	} // end constructor

	public void setPartNumber(String part) {
		partNumber = part; // should validate
	} // end method setPartNumber

	public String getPartNumber() {
		return partNumber;
	} // end method getPartNumber

	public void setPartDescription(String description) {
		partDescription = description; // should validate
	} // end method setPartDescription

	public String getPartDescription() {
		return partDescription;
	} // end method getPartDescription

	public void setQuantity(int count) {
		quantity = count;
	} // end method setQuantity

	public int getQuantity() {
		return quantity;
	} // end method getQuantity

	public void setPricePerItem(double price) {
		if (price >= 0.0)
			pricePerItem = price;
		else
			throw new IllegalArgumentException("Price per item must be >= 0");
	} // end method setPricePerItem

	public double getPricePerItem() {
		return pricePerItem;
	} // end method getPricePerItem

	@Override
	public String toString() {
		return String.format("%s: \n%s: %s (%s) \n%s: %d \n%s: $%,.2f",
				"invoice", "part number", getPartNumber(),
				getPartDescription(), "quantity", getQuantity(),
				"price per item", getPricePerItem());
	} // end method toString

	@Override
	public double getPaymentAmount() {
		return getQuantity() * getPricePerItem(); // calculate total cost
	} // end method getPaymentAmount
} // end class Invoice

