import java.util.*;

public class Multiplication extends Maths{
	protected double result;
	
	public void display(){
		super.display();
		System.out.println(" result => "+ result);
	}

	public void operation(){
		this.result = number1 * number2;
	}
}