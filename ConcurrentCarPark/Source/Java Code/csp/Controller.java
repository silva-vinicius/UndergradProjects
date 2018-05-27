//reference: http://www.ibm.com/developerworks/java/library/j-csp2/
package csp;



import java.io.PrintStream;

import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutput;
import org.jcsp.lang.Guard;
import model.Booking;
import model.ETicketToken;
import model.ParkingLot;


public class Controller  implements CSProcess {

	private AltingChannelInput arrivalInChannel;
	private ChannelOutput arrivalOutChannel;
	private AltingChannelInput departureInChannel;
	private ChannelOutput departureOutChannel;
	private AltingChannelInput bookingInChannel;
	private ChannelOutput bookingOutChannel;
	private ChannelOutput mailOutChannel;
	private ParkingLot carPark;
	private PrintStream out;


	//==================================CONSTRUCTORS===================================

	public Controller(AltingChannelInput arrivalInChannel, ChannelOutput arrivalOutChannel,
			AltingChannelInput departureInChannel, ChannelOutput departureOutChannel,
			AltingChannelInput bookingInChannel, ChannelOutput bookingOutChannel, ChannelOutput mailOutChannel,
			ParkingLot carPark, PrintStream out) {
		this.arrivalInChannel = arrivalInChannel;
		this.arrivalOutChannel = arrivalOutChannel;
		this.departureInChannel = departureInChannel;
		this.departureOutChannel = departureOutChannel;
		this.bookingInChannel = bookingInChannel;
		this.bookingOutChannel = bookingOutChannel;
		this.mailOutChannel = mailOutChannel;
		this.carPark = carPark;
		this.out = out;

	}
	//==================================================================================


	@Override
	public void run() {

		// TODO Auto-generated method stub
		Alternative inputAlternative = new Alternative(new Guard[] {this.departureInChannel, this.arrivalInChannel, this.bookingInChannel});
		final int READ_DEPARTURE=0, READ_ARRIVAL=1, READ_BOOKING=2;

		ETicketToken token;

		boolean acceptedArrival=false;
		boolean acceptedDeparture=false;
		int bookedPlace=-1;

		while(true){

			switch(inputAlternative.priSelect()){

			case READ_ARRIVAL:
				token = (ETicketToken) arrivalInChannel.read();
				this.out.println("Arrival request");


				acceptedArrival = this.carPark.checkIn(token);
				arrivalOutChannel.write(acceptedArrival);
				this.out.println("Processed arrival");
				break;

			case READ_DEPARTURE:

				token = (ETicketToken) departureInChannel.read();
				this.out.println("Departure request");


				acceptedDeparture = this.carPark.checkOut(token);
				departureOutChannel.write(acceptedDeparture);
				this.out.println("Processed departure");

				break;

			case READ_BOOKING:

				
				Booking requestedBooking = (Booking) bookingInChannel.read();
				this.out.println("Booking request");
				bookedPlace = this.carPark.bookSpace(requestedBooking);
				bookingOutChannel.write(bookedPlace);
				this.out.println("Processed booking");

				//If booking was accepted, 
				if(bookedPlace>0){
					requestedBooking.setPlace(bookedPlace-1);
					mailOutChannel.write(requestedBooking);
					this.out.println("Eticket request");
				}

				break;
			}	
		}
	}


	//===============================GETTERS AND SETTERS===============================
	public ParkingLot getCarPark() {
		return carPark;
	}

	//---------------------------------------------------------------------------------
	public void setCarPark(ParkingLot carPark) {
		this.carPark = carPark;
	}

}
