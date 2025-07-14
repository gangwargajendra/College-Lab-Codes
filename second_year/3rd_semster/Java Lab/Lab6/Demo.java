import java.util.*;

public class Demo {
    public static void main(String ... args){
		boolean n = true;

		while(n){
			System.out.println("1.Addition 2.Substraction 3.Multiplication 4.exit");
			System.out.print("Enter your choice : ");
			Scanner sc = new Scanner(System.in);
			int choice = sc.nextInt();
			switch(choice){
				case 1:
					Addition a1 = new Addition();
					a1.input();
					a1.operation();
					a1.display();
					break;
				case 2:
					Substraction s1 = new Substraction();
					s1.input();
					s1.operation();
					s1.display();
					break;
				case 3:
					Multiplication m1 = new Multiplication();
					m1.input();
					m1.operation();
					m1.display();
					break;
				case 4:
					n = false;
					 break;
			}
		}
	}
}