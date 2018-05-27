package main;

import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;


import model.Crime;
import xml.XMLBuilder;
public class Program1 {

	public static void main(String[] args) {
		
		
		ObjectInputStream oStream=null;
		FileInputStream fStream=null;
		ArrayList<Crime> crimesInput = new ArrayList<Crime>();
		try {
			
		    fStream = new FileInputStream("InputData.dat");
			oStream = new ObjectInputStream(fStream);
			
			while(true){
				Crime readCrime = (Crime)oStream.readObject();
				crimesInput.add(readCrime);
			}
			
			
		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		}catch(EOFException e){
		    try {
				oStream.close();
			} catch (IOException e1) {
				
				e1.printStackTrace();
			}	
		}
		catch (IOException e) {
			
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			
			e.printStackTrace();
		} 
		
		XMLBuilder xmlBuilder = new XMLBuilder();
		
		xmlBuilder.generateXML(crimesInput, "XMLOutput.xml");

		
		System.out.println("Program1 successfully run. \n'XMLOutput.xml' was created and should be used as input for Program2.\n");

	}

}
