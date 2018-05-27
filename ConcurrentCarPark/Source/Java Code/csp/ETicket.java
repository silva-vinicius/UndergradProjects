package csp;



import java.io.PrintStream;
import java.util.Properties;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.NoSuchProviderException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

import com.sun.mail.util.MailConnectException;

import model.Booking;

public class ETicket implements CSProcess{

	private String serverAdress;
	private String myMail;
	private String myPassword;
	private ChannelInput inChannel;
	private ChannelOutput outChannel;
	private PrintStream out;


	//==================================CONSTRUCTORS===================================

	public ETicket(String serverAdress, String myMail, String myPassword, ChannelInput inChannel, ChannelOutput outChannel, PrintStream out){
		this.serverAdress = serverAdress;
		this.myMail = myMail;
		this.myPassword = myPassword;
		this.inChannel = inChannel;
		this.outChannel = outChannel;
		this.out = out;

	}

	public ETicket (ChannelInput inChannel, ChannelOutput outChannel, PrintStream out){
		this.serverAdress = "smtp.gmail.com";
		this.myMail = "carparkcoursework@gmail.com";
		this.myPassword = "coursework123";
		this.inChannel = inChannel;
		this.outChannel = outChannel;
		this.out = out;
	}
	//==================================================================================

	public void sendETicket(Booking book){
		String eTicketContent =
				"<html> <head> <title> ETicket </title> </head>"
				+ " <body>  <table border = \"0\" align = \"center\" bgcolor = \"#4682B4\"> " +
				"<caption><h2>Your CarPark ETicket</h2></caption> <tbody>	"+	
				" <tr bgcolor = \"#4682B4\" color = \"white\">"+
				"<td colspan = \"4\"> &nbsp; </td> </tr>"+
				"<tr  align = \"center\" bgcolor = \"#CAE1FF\" color = \"white\"> <td colspan = \"4\"><h4>" +
				
				"===================BOOKING DETAILS===================<br/>" + 
				"E-Ticket number: " + book.getID() + "<br/>Arrival Time: " + book.getArrival().toString()+
				"<br/>Departure Time: " + book.getDeparture().toString() +
				"<br/>Parking space: " + (book.getPlace()+1) +
				"<br/>=======================================================<br/><br/>" + 
				"===================DRIVER'S DETAILS===================<br/>" +
				book.getDriver().toString()+
				"<br/>=======================================================<br/><br/>" +
				"=====================CAR'S DETAILS:====================<br/>" + 
				book.getCar().toString() +
				"<br/>=======================================================<br/><br/>" + 
				"Obs.: When arriving at the CarPark, visit http://localhost:8082 in order to check-in. <br/>" +
				"When leaving CarPark visit http://localhost:8083 in order to check-out." +
				"</h4></td></tr>" +
				"<tr> <td colspan = \"4\"> &nbsp;</td> </tr> </tbody> </table></form></body></html>";
		
		
		String key = book.getDriver().getMail();
		
		this.outChannel.write(key);
		this.outChannel.write(eTicketContent);
		this.out.println("Eticket sent");
		
		//Extra feature: Send email to user:
		try {
			Properties props = new Properties();
			props.setProperty("mail.smtps.host", serverAdress);

			Session session = Session.getInstance(props, null);
			Transport transport;
			transport = session.getTransport("smtps");
			transport.connect(myMail, myPassword);

			Message message = new MimeMessage(session);
			message.setSubject("CarPark e-ticket");
			
			String messageContent = 
					"		ETicket		" +
					
					"\n===================BOOKING DETAILS===================\n" + 
					"E-Ticket number: " + book.getID() + "\nArrival Time: " + book.getArrival().toString()+
					"\nDeparture Time: " + book.getDeparture().toString() +
					"\nParking space: " + (book.getPlace()+1) +
					"\n=======================================================\n\n" + 
					"===================DRIVER'S DETAILS===================\n" +
					book.getDriver().toSimpleString() +
					"\n=======================================================\n\n" +
					"=====================CAR'S DETAILS:====================\n" + 
					book.getCar().toSimmpleString() +
					"\n=======================================================\n\n" + 
					"Obs.: When arriving at the CarPark, visit http://localhost:8082 in order to check-in. \n" +
					"When leaving CarPark visit http://localhost:8083 in order to check-out.";
			
			message.setText(messageContent);
			message.setFrom(new InternetAddress(myMail));
			message.setRecipient(Message.RecipientType.TO, new InternetAddress(book.getDriver().getMail()));
			transport.sendMessage(message, message.getAllRecipients());
			
		} catch (NoSuchProviderException e) {
			
			e.printStackTrace();
		} catch(MailConnectException e){
			out.println("The computer is not connected to the internet. It is not possible to send the ETicket to the customer.");
		} catch (MessagingException e) {
			e.printStackTrace();
		} 
	}
	
	//---------------------------------------------------------------------------------
	@Override
	public void run() {

		while (true){
			Booking booking = (Booking)this.inChannel.read();
			this.out.println("ETicket request");
			sendETicket(booking);
		}
	}


	//===============================GETTERS AND SETTERS===============================
	public String getServerAdress() {
		return serverAdress;
	}

	//---------------------------------------------------------------------------------
	public void setServerAdress(String serverAdress) {
		this.serverAdress = serverAdress;
	}

	//---------------------------------------------------------------------------------
	public String getMyMail() {
		return myMail;
	}

	//---------------------------------------------------------------------------------
	public void setMyMail(String myMail) {
		this.myMail = myMail;
	}

	//---------------------------------------------------------------------------------
	public String getPassword() {
		return this.myPassword;
	}

	//---------------------------------------------------------------------------------
	public void setMyPassword(String newPassword) {
		this.myPassword= newPassword;
	}

}
