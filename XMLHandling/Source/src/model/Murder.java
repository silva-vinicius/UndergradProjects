package model;

import java.io.Serializable;
import java.util.ArrayList;

//The class is serializable because Program3 writes objects from it in a Serialized way on "InputData.dat".
public class Murder extends Crime implements Serializable {

	private static final long serialVersionUID = -1939111068539829265L;
	private String victim;
	private String location;
	private String weapon;
	private ArrayList<String> suspects;
	
	//==================================CONSTRUCTORS===================================

	public Murder(String victim, String location, String weapon, ArrayList<String> suspects) {
		this.victim = victim;
		this.location = location;
		this.weapon = weapon;
		this.suspects = suspects;
	}
	
	public Murder() {
		victim=null;
		location=null;
		weapon=null;
		suspects=null;
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
		
		String nonNullVictim;
		if(this.victim==null){
			nonNullVictim="Unknown";
		}else{
			nonNullVictim= this.victim;
		}
		
		String nonNullLocation;
		if(this.location==null){
			nonNullLocation = "Unknown";
		}else{
			nonNullLocation = this.location;
		}
		
		String nonNullWeapon;
		if(this.weapon==null){
			nonNullWeapon="Unknown";
		}else{
			nonNullWeapon = this.weapon;
		}
		
		String description = "----------------------------------------------------------------------------\n";
		description+= "Crime: Murder\n\tVictim: " + nonNullVictim + "\n\tLocation: " + 
		             nonNullLocation +  "\n\tWeapon: " + nonNullWeapon + "\n\tSuspects:\n";
		
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
	public String getVictim() {
		return victim;
	}
	
	//---------------------------------------------------------------------------------
	public void setVictim(String victim) {
		this.victim = victim;
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
	public String getWeapon() {
		return weapon;
	}
	
	//---------------------------------------------------------------------------------
	public void setWeapon(String weapon) {
		this.weapon = weapon;
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
