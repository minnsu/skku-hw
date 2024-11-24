package com.examples.lecture4;

public class Car {

	private String Maker;
	private int Year;
	private Engine carEngine;
	
	public Car(String maker, int year, int capacity, int SerialNumber) {
		this.Maker = maker;
		this.Year = year;
		this.carEngine = new Engine(capacity, SerialNumber);
	}

	public String getMaker() {
		return Maker;
	}
	public void setMaker(String maker) {
		Maker = maker;
	}

	public int getYear() {
		return Year;
	}
	public void setYear(int year) {
		Year = year;
	}

	public Engine getCarEngine() {
		return carEngine;
	}
	public void setCarEngine(Engine carEngine) {
		this.carEngine = carEngine;
	}
}