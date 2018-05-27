package csp;

import java.io.PrintStream;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.Parallel;

import model.ParkingLot;

public class CarParkComposition implements CSProcess{
	private Controller controller;
	private Arrival arrival;
	private Departure departure;

	public CarParkComposition(One2OneChannel bookingController, One2OneChannel controllerBookingChannel, One2OneChannel controllerMailChannel, int availableSpaces, PrintStream out) {

		
		One2OneChannel arrivalControllerChannel = Channel.one2one();
		One2OneChannel controllerArrivalChannel = Channel.one2one();
		One2OneChannel departureControllerChannel = Channel.one2one();
		One2OneChannel controllerDepartureChannel = Channel.one2one();
		
		this.controller = new Controller(arrivalControllerChannel.in(), controllerArrivalChannel.out(), 
				                         departureControllerChannel.in(), controllerDepartureChannel.out(), 
				                         bookingController.in(), controllerBookingChannel.out(), 
				                         controllerMailChannel.out(), new ParkingLot(availableSpaces), out);
		
		this.arrival = new Arrival(controllerArrivalChannel.in(), arrivalControllerChannel.out(), out);
		
		this.departure = new Departure(controllerDepartureChannel.in(), departureControllerChannel.out(),out);

	}
	@Override
	public void run() {
		
		new Parallel (
				new CSProcess[] {
						this.controller,
						this.arrival,
						this.departure,
				}
				).run ();
	}

}
