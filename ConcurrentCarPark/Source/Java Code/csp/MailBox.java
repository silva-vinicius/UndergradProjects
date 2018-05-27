package csp;

import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;

import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;
import org.jcsp.lang.Guard;



public class MailBox implements CSProcess {

	private Map mailBag;
	private AltingChannelInput inBookingChannel;
	private AltingChannelInput inIntChannel;
	private ChannelOutput outChannel;
	private PrintStream out;
	

	//==================================CONSTRUCTORS===================================
	public MailBox(AltingChannelInput inBookingChannel, AltingChannelInput inIntChannel, ChannelOutput outChannel, PrintStream out){
		this.mailBag = new HashMap<String, String>();
		this.inBookingChannel = inBookingChannel;
		this.inIntChannel = inIntChannel;
		this.outChannel = outChannel;
		this.out = out;
	}
	//==================================================================================

	private void addMail(String address, String content){
		this.mailBag.put(address, content);

	}
	
	//---------------------------------------------------------------------------------
	@Override
	public void run() {

		Alternative inputAlternative = new Alternative(new Guard[] {this.inBookingChannel, this.inIntChannel});
		final int RECEIVE=0, RETRIEVE=1;

		String address;
		String message;
		while(true){
			switch(inputAlternative.priSelect()){
			case RECEIVE:
				address = (String)this.inBookingChannel.read();
				message = (String)this.inBookingChannel.read();
				this.out.println("ETicket sent");
				this.addMail(address, message);
				message=null;
				break;
				
			case RETRIEVE:
				address=(String)this.inIntChannel.read();
				message=(String) this.mailBag.get(address);
				this.out.println("ETicket retrieval request");
				this.outChannel.write(message);
				this.out.println("Eticket retrieved");
				
				
				message=null;
				break;
			}

		}
	}
}
