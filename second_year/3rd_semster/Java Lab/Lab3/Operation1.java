import java.util.*;
public class Operation1 {
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter first operand : ");
		int a1 = sc.nextInt();
		System.out.print("Enter second operand : ");
		int a2 = sc.nextInt();
		System.out.print("Enter operator : ");
		String a3 = sc.next();
		Operation t1 = new Operation(a1 , a3 ,a2);
		t1.calculateValue();
		t1.displayResult();
	}
}