package model;

import java.io.Serializable;
import java.util.ArrayList;

//The class is serializable because Program3 writes objects from it in a Serialized way on "InputData.dat".
public class Theft extends Crime implements Serializable {


	private static final long serialVersionUID = 2381117433708693424L;
	private String objectStolen;
	private String objectOwner;
	private String location;
	private ArrayList<String> suspects;

	//==================================CONSTRUCTORS===================================
	public Theft(String objectStolen, String objectOwner, String location,
			ArrayList<String> suspects) {

		this.objectStolen = objectStolen;
		this.objectOwner = objectOwner;
		this.location = location;
		this.suspects = suspects;
	}

	public Theft() {
		this.objectStolen=null;
		this.objectOwner=null;
		this.location=null;
		this.suspects=null;
	}

	//=================================================================================

	public void addSuspect(String suspect){
		if(this.suspects==null){
			this.suspects = new ArrayList<String>();
		}
		this.suspects.add(suspect);
	}
	
	//---------------------------------------------------------------------------------
	public String toString(){
		
		String nonNullObjectStolen;
		if(this.objectStolen==null){
			nonNullObjectStolen = "Unknown";
		}else{
			nonNullObjectStolen = this.objectStolen;
		}
		
		String nonNullObjectOwner;
		if(this.objectOwner==null){
			nonNullObjectOwner = "Unknown";
		}else{
			nonNullObjectOwner = this.objectOwner;
		}
		
		String nonNullLocation;
		if(this.location==null){
			nonNullLocation = "Unknown";
		}else{
			nonNullLocation = this.location;
		}
		

		String description = "----------------------------------------------------------------------------\n";
		description+= "Crime: Theft\n\tObject Stolen: " + nonNullObjectStolen + "\n\tObject Owner: " + 
				nonNullObjectOwner +  "\n\tLocation: " + nonNullLocation + "\n\tSuspects:\n";

		if(this.suspects!=null && this.suspects.size()>0){

			for(String s : this.suspects){
				description += "\t\t"+s+"\n";
			}
		}else{
			description += "\t\t No suspects are known for this case.\n";
		}
		description+="\n----------------------------------------------------------------------------\n";
		return description;
	}


	//===============================GETTERS AND SETTERS===============================
	public String getObjectStolen() {
		return objectStolen;
	}
	
	//---------------------------------------------------------------------------------
	public void setObjectStolen(String objectStolen) {
		this.objectStolen = objectStolen;
	}
	
	//---------------------------------------------------------------------------------
	public String getObjectOwner() {
		return objectOwner;
	}
	
	//---------------------------------------------------------------------------------
	public void setObjectOwner(String objectOwner) {
		this.objectOwner = objectOwner;
	}
	
	//---------------------------------------------------------------------------------
	public String getLocation() {
		return location;
	}
	
	//---------------------------------------------------------------------------------
	public void setLocation(String location) {
		this.location = location;
	}
	
	//---------------------------------------------------------------------------------
	public ArrayList<String> getSuspects() {
		return suspects;
	}
	
	//---------------------------------------------------------------------------------
	public void setSuspects(ArrayList<String> suspects) {
		this.suspects = suspects;
	}

}
