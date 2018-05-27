package main;
import xml.XMLReader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;

import model.Crime;

public class Program2 {

	public static void main(String[] args) {
		
		try {
			
			XMLReader xmlReader = new XMLReader();
			
			ArrayList<Crime> crimes = xmlReader.readXML("XMLOutput.xml");
			PrintStream printStream = new PrintStream(new File("Report.txt"));
			
			for(Crime c : crimes){
				printStream.println(c.toString());
			}
			
			printStream.close();
			
			System.out.println("Program2 successfully run. \nCheck 'Report.txt' to see the data stored in the XML in plain English.\n");
		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		}
		
		
	}
}
