package com.examples.lecture4;

public class Engine { // format your code ctrl +Shift + F
	private int engineCapacity;
	private int engineSerialNumber;
	
	public Engine(int engineCapacity, int engineSerialNumber) {
	
		this.engineCapacity = engineCapacity;
		this.engineSerialNumber = engineSerialNumber;
	}

	public int getEngineCapacity() {
		return engineCapacity;
	}
	public void setEngineCapacity(int engineCapacity) {
		this.engineCapacity = engineCapacity;
	}

	public int getEngineSerialNumber() {
		return engineSerialNumber;
	}
	public void setEngineSerialNumber(int engineSerialNumber) {
		this.engineSerialNumber = engineSerialNumber;
	}
	
	public String toString() {
		String info = "";
		//info = "Capacity = " + this.engineCapacity +"\n"+
		//		"SerialNumber =" + this.engineSerialNumber +"\n";
		
		info = "Capacity = " + this.getEngineCapacity() +"\n"+
						"SerialNumber =" + this.getEngineSerialNumber() +"\n";	
		return info;
	}	
}