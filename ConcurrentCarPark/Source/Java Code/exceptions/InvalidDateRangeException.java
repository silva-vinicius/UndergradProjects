package exceptions;

public class InvalidDateRangeException extends Exception {

	private static final long serialVersionUID = 1L;
	
	public InvalidDateRangeException(String message){
		super(message);
	}

}
