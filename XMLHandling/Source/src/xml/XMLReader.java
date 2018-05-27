package xml;

import java.io.IOException;
import java.util.ArrayList;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.input.SAXBuilder;

import model.Crime;
import model.Murder;
import model.Theft;
import model.TrafficViolation;

public class XMLReader {

	//---------------------------------------------------------------------------------
	private ArrayList<String> getSuspects(Element suspectsElement){

		if(suspectsElement==null || suspectsElement.getChildren().isEmpty()){
			return null;
		}
		ArrayList<String> suspects = new ArrayList<String>();

		for(Element e : suspectsElement.getChildren()){
			suspects.add(e.getText());
		}
		return suspects;
	}

	//---------------------------------------------------------------------------------
	private Murder getMurderObject(Element murderElement){

		Murder murderObject = new Murder();
		String victim = murderElement.getChildText("victim");
		String weapon = murderElement.getChildText("weapon");
		String location = murderElement.getChildText("location");
		Element suspects = murderElement.getChild("suspects");
		if(victim!=null){
			murderObject.setVictim(victim);
		}
		if(weapon!=null){
			murderObject.setWeapon(weapon);
		}
		if(location!=null){
			murderObject.setLocation(location);
		}
		murderObject.setSuspects(getSuspects(suspects));

		return murderObject;
	}

	//---------------------------------------------------------------------------------
	private Theft gettheftObject(Element theftElement){

		Theft theftObject = new Theft();
		String objectStolen = theftElement.getChildText("objectStolen");
		String objectOwner = theftElement.getChildText("objectOwner");
		String location = theftElement.getChildText("location");
		Element suspects = theftElement.getChild("suspects");
		if(objectStolen!=null){
			theftObject.setObjectStolen(objectStolen);
		}
		if(objectOwner!=null){
			theftObject.setObjectOwner(objectOwner);
		}
		if(location!=null){
			theftObject.setLocation(location);
		}
		theftObject.setSuspects(getSuspects(suspects));

		return theftObject;
	}

	//---------------------------------------------------------------------------------
	private TrafficViolation getTrafficViolationObject(Element tvElement){

		TrafficViolation tvObject = new TrafficViolation();
		String driver = tvElement.getChildText("driver");
		String vehiclePlate = tvElement.getChildText("vehiclePlate");
		String offense = tvElement.getChildText("offense");
		String location = tvElement.getChildText("location");
		
		if(driver!=null){
			tvObject.setDriver(driver);
		}
		if(vehiclePlate!=null){
			tvObject.setVehiclePlate(vehiclePlate);
		}
		if(offense!=null){
			tvObject.setOffense(offense);
		}
		if(location!=null){
			tvObject.setLocation(location);
		}
		return tvObject;
	}
	
	//---------------------------------------------------------------------------------
	public ArrayList<Crime> readXML(String path){
		SAXBuilder xmlBuilder = new SAXBuilder();
		ArrayList<Crime> storedCrimes = new ArrayList<Crime>();
		
		try {
			Document xmlDocument = xmlBuilder.build(path);
			Element rootNode = xmlDocument.getRootElement();
			
			for(Element e:rootNode.getChildren()){
				if(e.getChildText("type").equals("murder")){
					storedCrimes.add(this.getMurderObject(e));
				}
				
				if(e.getChildText("type").equals("theft")){
					storedCrimes.add(this.gettheftObject(e));
				}
				
				if(e.getChildText("type").equals("traffic violation")){
					storedCrimes.add(this.getTrafficViolationObject(e));
				}
			}
			
			return storedCrimes;
			
		} catch (JDOMException e) {
			
			e.printStackTrace();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
		
		return null;
		
	}
	
	

}
