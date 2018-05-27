package model;

import java.io.Serializable;

//The class is serializable because Program3 writes objects from it in a Serialized way on "InputData.dat".
public class TrafficViolation extends Crime implements Serializable {
	

	private static final long serialVersionUID = -1149637472120569612L;
	private String driver;
	private String vehiclePlate;
	private String offense;
	private String location;
	
	//==================================CONSTRUCTORS===================================
	public TrafficViolation(String driver, String vehiclePlate, String offense, String location) {
		this.driver = driver;
		this.vehiclePlate = vehiclePlate;
		this.offense = offense;
		this.location = location;
	}
	
	public TrafficViolation(){
		this.driver=null;
		this.vehiclePlate=null;
		this.offense=null;
		this.location=null;
	}
	//=================================================================================
	
	public String toString(){
		
		String nonNullDriver;
		if(this.driver==null){
			nonNullDriver = "Unknown";
		}else{
			nonNullDriver = this.driver;
		}
		
		String nonNullPlate;
		if(this.vehiclePlate==null){
			nonNullPlate = "Unknown";
		}else{
			nonNullPlate = this.vehiclePlate;
		}
		
		String nonNullOffense;
		if(this.offense==null){
			nonNullOffense = "Unknown";
		}else{
			nonNullOffense = this.offense;
		}
		
		String nonNullLocation;
		if(this.location==null){
			nonNullLocation="Unknown";
		}else{
			nonNullLocation = this.location;
		}
		
		String description = "----------------------------------------------------------------------------\n";
		description+= "Crime: Traffic Violation\n\tDriver: " + nonNullDriver + "\n\tVehicle Plate: " + 
		             nonNullPlate +  "\n\tOffense: " + nonNullOffense + "\n\tLocation: " + nonNullLocation + "\n";
		description+="\n----------------------------------------------------------------------------\n";
		return description;
	}
	//===============================GETTERS AND SETTERS===============================
	public String getDriver() {
		return driver;
	}
	
	//---------------------------------------------------------------------------------
	public void setDriver(String driver) {
		this.driver = driver;
	}
	
	//---------------------------------------------------------------------------------
	public String getVehiclePlate() {
		return vehiclePlate;
	}
	
	//---------------------------------------------------------------------------------
	public void setVehiclePlate(String vehiclePlate) {
		this.vehiclePlate = vehiclePlate;
	}
	
	//---------------------------------------------------------------------------------
	public String getOffense() {
		return offense;
	}
	
	//---------------------------------------------------------------------------------
	public void setOffense(String offense) {
		this.offense = offense;
	}
	
	//---------------------------------------------------------------------------------
	public String getLocation() {
		return location;
	}
	
	//---------------------------------------------------------------------------------
	public void setLocation(String location) {
		this.location = location;
	}
}
