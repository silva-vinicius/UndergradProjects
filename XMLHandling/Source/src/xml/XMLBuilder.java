package xml;

import java.util.ArrayList;
import model.Crime;
import model.Murder;
import model.Theft;
import model.TrafficViolation;

import java.io.FileWriter;
import java.io.IOException;
import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.output.Format;
import org.jdom2.output.XMLOutputter;


public class XMLBuilder {
	
	
	private Element getSuspectsElement(ArrayList<String> suspects){
		Element suspectsElement = new Element("suspects");
		for(String suspect : suspects){
			suspectsElement.addContent(new Element("suspect").setText(suspect));
		}
		
		return suspectsElement;
	}
	
	//---------------------------------------------------------------------------------
	private Element getMurderElement(Murder murder){
		Element murderElement=new Element("crime");
		murderElement.addContent(new Element("type").setText("murder"));
		if(murder.getVictim()!=null){
			murderElement.addContent(new Element("victim").setText(murder.getVictim()));
		}
		
		if(murder.getWeapon()!=null){
			murderElement.addContent(new Element("weapon").setText(murder.getWeapon()));	
		}
		
		if(murder.getLocation()!=null){
			murderElement.addContent(new Element("location").setText(murder.getLocation()));	
		}
		
		if(murder.getSuspects()!=null){
			if(murder.getSuspects().size()>0){
				murderElement.addContent(getSuspectsElement(murder.getSuspects()));
			}	
		}
		
		return murderElement;
	}
	
	//---------------------------------------------------------------------------------
	private Element getTheftElement(Theft theft){
		
		Element theftElement=new Element("crime");
		theftElement.addContent(new Element("type").setText("theft"));
		
		if(theft.getObjectStolen()!=null){
			theftElement.addContent(new Element("objectStolen").setText(theft.getObjectStolen()));	
		}
		
		if(theft.getObjectOwner()!=null){
			theftElement.addContent(new Element("objectOwner").setText(theft.getObjectOwner()));
		}
		
		if(theft.getLocation()!=null){
			theftElement.addContent(new Element("location").setText(theft.getLocation()));
		}
		
		if(theft.getSuspects()!=null){
			if(theft.getSuspects().size()>0){
				theftElement.addContent(getSuspectsElement(theft.getSuspects()));
			}
		}
		
		return theftElement;
	}
	
	//---------------------------------------------------------------------------------
	private Element getTrafficElement(TrafficViolation tv){
		Element tvElement=new Element("crime");
		tvElement.addContent(new Element("type").setText("traffic violation"));
		
		if(tv.getDriver()!=null){
			tvElement.addContent(new Element("driver").setText(tv.getDriver()));	
		}
		
		if(tv.getVehiclePlate()!=null){
			tvElement.addContent(new Element("vehiclePlate").setText(tv.getVehiclePlate()));	
		}
		
		if(tv.getOffense()!=null){
			tvElement.addContent(new Element("offense").setText(tv.getOffense()));	
		}
		
		if(tv.getLocation()!=null){
			tvElement.addContent(new Element("location").setText(tv.getLocation()));	
		}
		
		return tvElement;
	}
	
	//---------------------------------------------------------------------------------
	public void generateXML(ArrayList<Crime> crimes, String path){
		
		Element root = new Element("CrimesInfo");
		Document doc = new Document(root);
		
		Murder auxMurder;
		Theft auxtheft;
		TrafficViolation auxTrafficViolation;
		for(Crime crime : crimes){
			
			if(crime instanceof Murder){
				auxMurder = (Murder)crime;
				doc.getRootElement().addContent(getMurderElement(auxMurder));
			}
			
			if(crime instanceof Theft){
				auxtheft = (Theft)crime;
				doc.getRootElement().addContent(getTheftElement(auxtheft));
			}
			
			if(crime instanceof TrafficViolation){
				auxTrafficViolation = (TrafficViolation)crime;
				doc.getRootElement().addContent(getTrafficElement(auxTrafficViolation));
			}
		}
		
		XMLOutputter xmlOutput = new XMLOutputter();
		
		xmlOutput.setFormat(Format.getPrettyFormat());
		try {
			xmlOutput.output(doc, new FileWriter(path));
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
}
