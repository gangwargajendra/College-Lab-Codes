import java.util.*;

public class Ques{
	public static void main (String s[]) {
		Scanner sc = new Scanner (System.in);
		System.out.println("Enter marks : ");
		int n = sc.nextInt();
		if(n > 100 || n < 0){
			System.out.println("invalid");
		}else if(n >= 91){
			System.out.println("grade = O");
		}else if(n >= 85){
			System.out.println("grade = A");
		}else if(n >=75){
			System.out.println("grade = B");
		}else if(n >= 50){
			System.out.println("grade = C");
		}else{
			System.out.println("grade = F");
		}
	}
}