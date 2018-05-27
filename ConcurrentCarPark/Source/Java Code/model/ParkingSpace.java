package model;

import java.util.ArrayList;
import java.util.Date;

public class ParkingSpace {

	private ArrayList<Booking> bookings;


	//==================================CONSTRUCTORS===================================
	public ParkingSpace() {
		this.bookings = new ArrayList<Booking>();
	}

	public ParkingSpace(ArrayList<Booking> bookings) {
		this.bookings = bookings;
	}
	//=================================================================================

	

	public void addBooking(Booking booking){
		this.bookings.add(booking);

	}

	//---------------------------------------------------------------------------------
	public boolean removeBooking (long bookingID){
		for (Booking bkg: this.bookings) {

			if(bkg.getID() == bookingID){
				this.bookings.remove(bkg);
				return true;
			}

		}
		return false;
	}
	
	//---------------------------------------------------------------------------------
	public boolean checkAvailability(Date arrival, Date departure){


		for (Booking bkg: this.bookings) {

			if(arrival.before(bkg.getArrival()) && departure.after(bkg.getArrival())){
				return false;
			}
			if(arrival.after(bkg.getArrival()) && departure.before(bkg.getDeparture())){
				return false;
			}
			if(arrival.before(bkg.getDeparture()) && departure.after(bkg.getDeparture())){
				return false;
			}

		}
		return true;
	}
	
	//---------------------------------------------------------------------------------
	public Booking getBookingByID(long ID){
		
		for(Booking bkg : this.bookings){
			if(bkg.getID() == ID){
				return bkg;
			}
		}
		
		return null;
	}

	//===============================GETTERS AND SETTERS===============================
	public ArrayList<Booking> getBookings() {
		return bookings;
	}

	//---------------------------------------------------------------------------------
	public void setBookings(ArrayList<Booking> bookings) {
		this.bookings = bookings;
	}



}
