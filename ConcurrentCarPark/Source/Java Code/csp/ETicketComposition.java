package csp;

import java.io.PrintStream;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.Parallel;

public class ETicketComposition implements CSProcess{
	
	private MailBox mailBox;
	private ETicket eTicket;
	private MailInt mailInterface;
	
	
	public ETicketComposition(One2OneChannel controllerMailChannel, PrintStream out){
		
		One2OneChannel eTicketMailChannel = Channel.one2one();
		One2OneChannel interFaceMailChannel = Channel.one2one();
		One2OneChannel mailInterfaceChannel = Channel.one2one();

		this.mailBox = new MailBox(eTicketMailChannel.in(), interFaceMailChannel.in(), mailInterfaceChannel.out(), out);
		this.eTicket = new ETicket(controllerMailChannel.in(), eTicketMailChannel.out(),out);
	    this.mailInterface = new MailInt(mailInterfaceChannel.in(), interFaceMailChannel.out(),out);

	}


	@Override
	public void run() {
		
		 new Parallel (
					new CSProcess[] {
							this.mailBox,
							this.eTicket,
							this.mailInterface,
					}
					).run ();
	}

}
