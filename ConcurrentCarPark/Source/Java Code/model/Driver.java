package model;

public class Driver {
	private String name;
	private String phone;
	private String mail;
	private String licence;
	
	
	//==================================CONSTRUCTORS===================================
	public Driver(){
		this.name = null;
		this.phone = null;
		this.mail = null;
		this.licence = null;
	}
	
	public Driver(String name, String phone, String mail, String licence){
		this.name = name;
		this.phone = phone;
		this.mail = mail;
		this.licence = licence;
	}
    //=================================================================================
	
	public String toString(){
		
		return "Name: " + this.name + "<br/>Phone: " + this.phone + 
				"<br/>E-mail: " + this.mail + "<br/>Licence: " + 
				this.licence + "<br/>";
		
	}
	
	public String toSimpleString(){
		return "Name: " + this.name + "\nPhone: " + this.phone + 
				"\nE-mail: " + this.mail + "\nLicence: " + 
				this.licence + "\n";
	}
	//===============================GETTERS AND SETTERS===============================
	public String getName() {
		return name;
	}
	//---------------------------------------------------------------------------------
	public void setName(String name) {
		this.name = name;
	}
	//---------------------------------------------------------------------------------
	public String getPhone() {
		return phone;
	}
	//---------------------------------------------------------------------------------
	public void setPhone(String phone) {
		this.phone = phone;
	}
	//---------------------------------------------------------------------------------
	public String getMail() {
		return mail;
	}
	//---------------------------------------------------------------------------------
	public void setMail(String mail) {
		this.mail = mail;
	}
	//---------------------------------------------------------------------------------
	public String getLicence() {
		return licence;
	}
	//---------------------------------------------------------------------------------
	public void setLicence(String licence) {
		this.licence = licence;
	}
	//=================================================================================
}
