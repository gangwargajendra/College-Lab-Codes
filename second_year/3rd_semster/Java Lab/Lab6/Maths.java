import java.util.*;

public class Maths{
	protected int number1;
	protected int number2;
	
	public void display(){
		System.out.print("number1 => "+number1 + " number2 => " + number2);
	}

	public void input(){
		Scanner sc = new Scanner(System.in);
		System.out.print("Ener first number : ");
		int number1 = sc.nextInt();
		this.number1 = number1;
		System.out.print("Ener second number : ");
		int number2 = sc.nextInt();
		this.number2 = number2;
	}
}