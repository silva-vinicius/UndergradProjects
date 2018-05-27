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

public class MailInt implements CSProcess{

	private ChannelInput inChannel;
	private ChannelOutput outChannel;
	private PrintStream out;
	
	public MailInt(ChannelInput inChannel, ChannelOutput outChannel, PrintStream out){
		this.inChannel = inChannel;
		this.outChannel = outChannel;
		this.out = out;
		
	}

	private void handleTicketRetrieval(Socket connection, String mailAddress){
		try {
			PrintWriter out = new PrintWriter(connection.getOutputStream(),true);
			mailAddress = mailAddress.replace("data=", "");
			mailAddress = mailAddress.replace(" HTTP/1.1", "");
			
			//makes a request to the MailBox component;
			outChannel.write(mailAddress);
			this.out.println("ETicket retrieval request");
			String response = (String)inChannel.read();
			this.out.println("Eticket retrieved");
			if(response!=null && !response.equals("null")){

				out.println(response);	
			}else{
				FileReader fr = new FileReader("ticketNotFound.html");
				BufferedReader br = new BufferedReader(fr);
				String readLine = "";
				response="";

				while(readLine!=null){
					readLine = br.readLine();
					if(readLine!=null){
						response += readLine + "\n";
					}

				}
				br.close();

				out.println(response);
				
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	private void handleLogin(Socket connection){

		try {
			PrintWriter out = new PrintWriter(connection.getOutputStream(),true);
			FileReader fr = new FileReader("mailLogin.html");
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

			e.printStackTrace();
		}

	}

	@Override
	public void run() {




		ServerSocket server = null;
		try {
			//creates a server socket to communicate with the port 8081. It's the welcome socket 
			server = new ServerSocket(8081);
		} catch (IOException e) {
			System.err.println("Cannot create socket on port 8081.");
			System.exit(-1);
		}

		//loop that allows the server to listen to requests on port 8081 for an indefinite time
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
							
							handleTicketRetrieval(connection, inputData);
						}else{
							handleLogin(connection);
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


		// TODO Auto-generated method stub

	}

}
