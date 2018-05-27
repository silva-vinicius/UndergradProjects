package csp;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

import org.jcsp.lang.*;



public class Main {
	public static void main (String[] args){
		
		
		
		try {
			One2OneChannel bookingControllerChannel = Channel.one2one();
			One2OneChannel controllerBookingChannel = Channel.one2one();
			One2OneChannel controllerMailChannel = Channel.one2one();
			
			PrintStream out = new PrintStream("log.txt");
		
			
			OnlineBooking booking = new OnlineBooking(controllerBookingChannel.in(), bookingControllerChannel.out(),out);
			CarParkComposition carPark = new CarParkComposition(bookingControllerChannel, controllerBookingChannel, controllerMailChannel, 50, out);
			ETicketComposition eTicket = new ETicketComposition(controllerMailChannel, out);

			new Parallel (
					new CSProcess[] {
							booking,
							carPark,
							eTicket,
					}
					).run ();
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		
		

	}

}
