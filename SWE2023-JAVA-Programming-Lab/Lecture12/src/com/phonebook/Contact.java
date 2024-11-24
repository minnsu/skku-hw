package com.phonebook;

public class Contact {
	private String name;
	private String phone;
	
	public final static String[] rawData = new String[] { 
			"Mitsue Tani: 501-645-0791",
			"Amelia McGuiness: 502-519-4634", 
			"Austin Irwin: 317-716-6323",
			"David Ponte: 817-941-8660", 
			"Maria Casillas: 703-224-8177",
			"Klaus Zimmer: 734-876-8318", 
			"Arvind Poortvliet: 845-225-2412",
			"Kimberly Bryant: 478-967-9476", 
			"Robert Foss: 706-283-9218",
			"Veronica Hartnoll: 520-838-0633", 
			"Barry Peters: 760-951-2970",
			"Melanie Morris: 419-980-0128", 
			"Dorian: 919-477-2904",
			"Melisande Paiement: 478-553-3218", 
			"Elias Stuinen: 410-418-9516",
			"Luke Gilbert: 916-771-3266", 
			"Orpheo Meijerhof: 413-526-1632",
			"Marijke Thorsen: 845-756-2888", 
			"Christopher Hogan: 757-935-8572",
			"Veijo Hurme: 469-362-6326", 
			"Donna Scott: 541-563-2254",
			"Brenda Thomas: 484-544-4646", 
			"Martin Biermann: 661-302-6845",
			"Alvedin Bauk: 301-905-3083", 
			"Christy Reynolds: 513-629-1553",
			"Dale Escobar: 330-948-2674", 
			"Julia Ebersbacher: 913-727-1550",
			"Baresi: 704-201-9570", 
			"Cui Teng: 715-348-8673",
			"Pal Majer: 615-823-2105", 
			"Arika Fujii: 631-558-5171",
			"Janek Maciejewski: 830-778-9357", 
			"Horace Provost: 954-877-1843",
			"Mary Rainey: 304-702-4314" };
	
	public Contact(String n, String p){
		name = n;
		phone = p;
	}
	
	public String getName(){
		return name;
	}
	
	public String getPhone(){
		return phone;
	}
	
	public void setInfo(String n, String p){
		name = n;
		phone = p;
	}
	
}
