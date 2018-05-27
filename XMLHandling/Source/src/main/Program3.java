//This code is used only to generate data to be used as input for Program1.java
package main;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;


import model.*;
public class Program3 {

	public static void main(String[] args) {
		
		
		
		//The weapon used in the murder is not known
		Murder murder1 = new Murder();
		murder1.setVictim("Robbie");
		murder1.setLocation("Sunflower Road, Greenvale, UK");
		murder1.addSuspect("Ruth");
		murder1.addSuspect("Daniel");
		
		Murder murder2 = new Murder();
		murder2.setVictim("Thomas Wayne");
		murder2.setWeapon("Pistol");
		murder2.setLocation("Crime Alley, Greenvale, UK");
		murder2.addSuspect("Slade");
		murder2.addSuspect("Oswald Cobblepot");
		murder2.addSuspect("Floyd Lawton");
		
		Theft theft1 = new Theft();
		theft1.setObjectStolen("Diamond Ring");
		theft1.setObjectOwner("Kate Nikolaevna");
		theft1.setLocation("Forbury Street, Greenvale, UK");
		theft1.addSuspect("Selina Kyle");
		theft1.addSuspect("Harvey Dent");
		
		TrafficViolation tv1 = new TrafficViolation();
		tv1.setDriver("Bruce Wayne");
		tv1.setLocation("Oxford Road, Greenvale, UK");
		tv1.setOffense("Speeding");
		tv1.setVehiclePlate("BAT 37542");
		
		//The vehicle's plate is not known
		TrafficViolation tv2 = new TrafficViolation();
		tv2.setDriver("Edward Nigma");
		tv2.setLocation("Vauxhall Road, Greenvale, UK");
		tv2.setOffense("Parking Violation");
		
		try {
			FileOutputStream fos = new FileOutputStream("InputData.dat");
			ObjectOutputStream os = new ObjectOutputStream(fos);
			
			os.writeObject(theft1);
			os.writeObject(murder1);
			os.writeObject(murder2);
			os.writeObject(tv1);
			os.writeObject(tv2);
			
			os.close();
			System.out.println("Program3 successfuly run. \n'InputData.dat' was created and should be used as input for Program1.\n");
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		
	}

}
