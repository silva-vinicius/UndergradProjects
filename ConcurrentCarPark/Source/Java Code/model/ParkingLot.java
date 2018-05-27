package model;

import java.util.ArrayList;

public class ParkingLot {

	private ArrayList<ParkingSpace> parkingLot;
	private int availableSpaces;

	//==================================CONSTRUCTORS===================================
	public ParkingLot(int availableSpaces) {
		this.parkingLot = new ArrayList<ParkingSpace>();
		this.availableSpaces = availableSpaces;

		for(int i=0; i<availableSpaces; i++){
			this.parkingLot.add(new ParkingSpace());
		}
	}

	public ParkingLot(ArrayList<ParkingSpace> parkingLot, int availableSpaces) {
		this.parkingLot = parkingLot;
		this.availableSpaces = availableSpaces;
	}
	//=================================================================================

	//returns the number of the booked parking space
	public int bookSpace(Booking booking){

		for(int i=0; i<availableSpaces; i++){
			if(parkingLot.get(i).checkAvailability(booking.getArrival(), booking.getDeparture())){
				parkingLot.get(i).addBooking(booking);
				return i+1;
			}
		}
		return -1;
	}


	//---------------------------------------------------------------------------------
	public boolean checkIn(ETicketToken eToken){

		for(Booking book : this.parkingLot.get(eToken.getSpace()-1).getBookings()){
			if(book.getID() == eToken.getID() && book.getDriver().getLicence().equals(eToken.getLicence())){
				return true;
			}
		}

		return false;
	}

	//---------------------------------------------------------------------------------
	public boolean checkOut(ETicketToken eToken){
		try{
			for(Booking book : this.parkingLot.get(eToken.getSpace()-1).getBookings()){
				if(book.getID() == eToken.getID() && book.getDriver().getLicence().equals(eToken.getLicence())){
					parkingLot.get(eToken.getSpace()-1).removeBooking(eToken.getID());
					return true;
				}
			}
		}catch(IndexOutOfBoundsException e){
			return false;
		}
		return false;
	}


	//===============================GETTERS AND SETTERS===============================
	public ArrayList<ParkingSpace> getParkingLot() {
		return parkingLot;
	}

	//---------------------------------------------------------------------------------
	public void setParkingLot(ArrayList<ParkingSpace> parkingLot) {
		this.parkingLot = parkingLot;
	}

}
