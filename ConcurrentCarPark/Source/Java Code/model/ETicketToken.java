package model;

public class ETicketToken {
	private long ID;
	private String licence;
	private int space;

	//==================================CONSTRUCTORS===================================
	public ETicketToken(long iD, String licence, int space) {
		ID = iD;
		this.licence = licence;
		this.space = space;
	}

	//=================================================================================

	
	//===============================GETTERS AND SETTERS===============================
	public long getID() {
		return ID;
	}

	//---------------------------------------------------------------------------------
	public void setID(long iD) {
		ID = iD;
	}

	//---------------------------------------------------------------------------------
	public String getLicence() {
		return licence;
	}

	//---------------------------------------------------------------------------------
	public void setLicence(String licence) {
		this.licence = licence;
	}

	//---------------------------------------------------------------------------------
	
	public int getSpace() {
		return space;
	}

	//---------------------------------------------------------------------------------
	
	public void setSpace(int space) {
		this.space = space;
	}


}
