package csp;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

import model.ETicketToken;

public class Arrival implements CSProcess {
	
	private ChannelInput inChannel;
	private ChannelOutput outChannel;
	private PrintStream out;
	
	
	//==================================CONSTRUCTORS===================================
	public Arrival(ChannelInput inChannel, ChannelOutput outChannel, PrintStream out){
		this.inChannel = inChannel;
		this.outChannel = outChannel;
		this.out = out;
	}
	
	//==================================================================================
	
	private static String formatDataString(String data){

		data = data.replace("data=", "");
		data = data.replace("%20", " ");
		data = data.replace(" HTTP/1.1", "");
		return data;
	}
	
	
	
	//---------------------------------------------------------------------------------
	private void handleRequestOne(Socket connection){

		try {
			PrintWriter out = new PrintWriter(connection.getOutputStream(),true);
			FileReader fr = new FileReader("arrival.html");
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
	private void handleRequestTwo(Socket connection, String inputData){
		
		try {
			inputData = formatDataString(inputData);
			PrintWriter out = new PrintWriter(connection.getOutputStream(),true);
			
			String [] fields = inputData.split(";");
			ETicketToken token = new ETicketToken(Long.parseLong(fields[0]), fields[1], Integer.parseInt(fields[2]));
			outChannel.write(token);
			this.out.println("Arrival request");
			boolean acceptedArrival = (boolean)inChannel.read();
			this.out.println("Processed arrival");
			
			String response;
			
			
			FileReader fr;
			BufferedReader br;
			String readLine = "";
			if(acceptedArrival){
				
				fr = new FileReader("checkInAccepted.html");
				br = new BufferedReader(fr);
				
				response="";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();

			}else{
				fr = new FileReader("checkInRefused.html");
				br = new BufferedReader(fr);
				
				response="";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();
			}
			
			
			out.println(response);

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}
	
	//---------------------------------------------------------------------------------
	@Override
	public void run() {

		// TODO Auto-generated method stub



		ServerSocket server = null;
		try {
			//creates a server socket to communicate with the port 8082. It's the welcome socket 
			server = new ServerSocket(8082);
		} catch (IOException e) {
			System.err.println("Cannot create socket on port 8082.");
			System.exit(-1);
		}

		//loop that allows the server to listen to requests on port 8082 for an indefinite time
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
	
	
	//===============================GETTERS AND SETTERS===============================
	public ChannelInput getInChannel() {
		return inChannel;
	}
	
	//---------------------------------------------------------------------------------
	public void setInChannel(ChannelInput inChannel) {
		this.inChannel = inChannel;
	}
	
	//---------------------------------------------------------------------------------
	public ChannelOutput getOutChannel() {
		return outChannel;
	}
	
	//---------------------------------------------------------------------------------
	public void setOutChannel(ChannelOutput outChannel) {
		this.outChannel = outChannel;
	}

}
