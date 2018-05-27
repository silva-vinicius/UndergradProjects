package model;

public class Car {
	private String plate;
	private String model;
	

	//==================================CONSTRUCTORS===================================
	
	public Car() {
		this.plate = null;
		this.model = null;
	}
	
	//---------------------------------------------------------------------------------
	public Car(String plate, String model) {
		this.plate = plate;
		this.model = model;
	}
	//=================================================================================
	
	public String toString(){
		return "Plate: " + plate + "<br/>Model: " + model;
	}
	
	//---------------------------------------------------------------------------------
	public String toSimmpleString(){
		return "Plate: " + plate + "\nModel: " + model;
		
	}
	//===============================GETTERS AND SETTERS===============================
	
	public String getPlate() {
		return plate;
	}
	
	//---------------------------------------------------------------------------------
	public void setPlate(String plate) {
		this.plate = plate;
	}
	//---------------------------------------------------------------------------------
	public String getModel() {
		return model;
	}
	//---------------------------------------------------------------------------------
	public void setModel(String model) {
		this.model = model;
	}
}
