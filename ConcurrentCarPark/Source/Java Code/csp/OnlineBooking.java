package csp;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import org.jcsp.lang.*;



import exceptions.InvalidDateRangeException;
import model.Booking;
import model.Car;
import model.Driver;



public class OnlineBooking implements CSProcess {

	private ChannelOutput outChannel;
	private ChannelInput inChannel;
	private PrintStream out;

	//===================================CONSTRUCTOR===================================
	public OnlineBooking(ChannelInput inChannel, ChannelOutput outChannel, PrintStream out){
		this.inChannel = inChannel;
		this.outChannel = outChannel;
		this.out = out;
	}

	//===================================================================================

	private static String formatDataString(String data){

		data = data.replace("data=", "");
		data = data.replace("%20", " ");
		return data;
	}

	//---------------------------------------------------------------------------------
	private static Date parseDate(String data) throws ParseException {
		if (data == null || data.equals("")) {
			return null;
		}
		Date date = null;

		SimpleDateFormat f = new SimpleDateFormat("dd/MM/yyyy - HH:mm");
		date = (Date) f.parse(data);

		return date;
	}

	//---------------------------------------------------------------------------------
	private static Booking generateBooking(String data) throws Exception{

		String[] fields = data.split(";");
		Driver driver = new Driver(fields[0], fields[1], fields[2], fields[3]);
		Car car = new Car(fields[4], fields[5]);
		
		Date arrival;
		arrival = parseDate(fields[6]);

		Date departure = parseDate(fields[7]);

		if(departure.before(arrival)){
			throw new InvalidDateRangeException("Error: Departure cannot be before arrival");
		}

		return new Booking(car, driver, arrival, departure, -1);

	}

	//---------------------------------------------------------------------------------
	private void handleRequestOne(Socket connection){

		try {
			PrintWriter out = new PrintWriter(connection.getOutputStream(),true);
			FileReader fr = new FileReader("index.html");
			BufferedReader br = new BufferedReader(fr);
			String readLine = "";
			String response="";

			while(readLine!=null){
				readLine = br.readLine();
				if(readLine!=null){
					response += readLine + "\n";
				}

			}
			br.close();

			out.println(response);

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	//---------------------------------------------------------------------------------
	private void handleRequestTwo(Socket connection, String data){

		//creates a stream used to send data to the client
		String response="";
		PrintWriter out = null;
		FileReader fr;
		BufferedReader br;

		try {
			data = formatDataString(data);
			out = new PrintWriter(connection.getOutputStream(),true);
			Booking booking = generateBooking(data);


			int bookedPlace=-1;
			//Send the booking to the controller in order to check if it is ok.
			if(outChannel!=null && inChannel!=null){
				this.outChannel.write(booking);
				this.out.println("Booking request");
				bookedPlace = (int)this.inChannel.read();
				this.out.println("Processed booking");
			}

			//If booking was successful, tell the user!
			if(bookedPlace > 0){
				
				fr = new FileReader("successfulBooking.html");
				br = new BufferedReader(fr);
				String readLine = "";
				response="";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();

			}else{

				fr = new FileReader("failedBooking.html");
				br = new BufferedReader(fr);
				String readLine = "";
				response="";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();

			}



		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvalidDateRangeException e) {


			try {

				fr = new FileReader("inconsistentDates.html");
				br = new BufferedReader(fr);
				String readLine = "";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();

				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (FileNotFoundException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

		} catch (ParseException e) {
			try {
				fr = new FileReader("invalidDateFormat.html");
				br = new BufferedReader(fr);
				String readLine = "";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();

				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (FileNotFoundException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		out.println(response);

	}


	//---------------------------------------------------------------------------------
	@Override
	public void run() {
		// TODO Auto-generated method stub



		ServerSocket server = null;
		try {
			//creates a server socket to communicate with the port 8080. It's the welcome socket 
			server = new ServerSocket(8080);
		} catch (IOException e) {
			System.err.println("Cannot create socket on port 8080.");
			System.exit(-1);
		}


		Timer t = new Timer();
		t.start();

		//loop that allows the server to listen to requests on port 8080 for an indefinite time
		while (true) {
			Socket connection = null;

			try {
				//creates a new socket that will actually do the communication with the client.
				connection = (server.accept());


				//creates a stream used to receive data from the client.
				BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));

				String inputLine;
				String inputData = null;

				//reads the client request line by line
				while ((inputLine = in.readLine()) != null) {
					if (inputLine.indexOf("GET") != -1){


						int index = inputLine.indexOf("data=");
						if(index!=-1){
							inputData = inputLine.substring(index);
							handleRequestTwo(connection, inputData);
						}else{
							handleRequestOne(connection);
						}

					}

					if (inputLine.length() == 0)
						break;



				}


			} catch (IOException e) {
				System.err.println("Client accept failed: " + e);
				continue;
			}
		}

	}

}
