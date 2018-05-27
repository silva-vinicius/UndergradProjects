package csp;

import java.util.Date;

/*This class is used to limit the time the application will run.
  It is important to do so because we don't want the application listening to the computer ports indefinitely.
  I've set the limit for 10 minutes. 
*/

public class Timer extends Thread {
	
	public void run(){
		System.out.println("Timer started\n");
		long startTime = System.currentTimeMillis();
		long elapsedTime = 0L;

		while (elapsedTime < 10*60*1000) {
		    elapsedTime = (new Date()).getTime() - startTime;
		}
		System.out.println("Execution aborted by Timer");
		System.exit(0);
	}

}
