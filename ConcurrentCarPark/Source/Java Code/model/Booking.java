package model;

import java.util.Date;

public class Booking {
	public static long instanceCounter= 0L;
	private long ID;
	private Car car;
	private Driver driver;
	private Date arrival;
	private Date departure;
	int place;
	
	//==================================CONSTRUCTORS===================================
	public Booking() {
		instanceCounter++;
		this.setID(instanceCounter);
		this.car = null;
		this.driver = null;
		this.arrival = null;
		this.departure = null;
		place=-1;
	}
	
	public Booking(Car car, Driver driver, Date arrival, Date departure, int place) {
		instanceCounter++;
		this.setID(instanceCounter);
		this.car = car;
		this.driver = driver;
		this.arrival = arrival;
		this.departure = departure;
		this.place = place;
		
		
	}
	//=================================================================================
	
	//===============================GETTERS AND SETTERS===============================
	public Car getCar() {
		return car;
	}
	public void setCar(Car car) {
		this.car = car;
	}
	public Driver getDriver() {
		return driver;
	}
	public void setDriver(Driver driver) {
		this.driver = driver;
	}
	public Date getArrival() {
		return arrival;
	}
	public void setArrival(Date arrival) {
		this.arrival = arrival;
	}
	public Date getDeparture() {
		return departure;
	}
	public void setDeparture(Date departure) {
		this.departure = departure;
	}
	public long getID() {
		return ID;
	}

	public void setID(long iD) {
		ID = iD;
	}
	
	public int getPlace() {
		return place;
	}

	public void setPlace(int place) {
		this.place = place;
	}
	
	//=================================================================================
	
	


	
	

}
