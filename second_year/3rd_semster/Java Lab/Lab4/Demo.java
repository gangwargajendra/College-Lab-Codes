import java.util.*;

public class Demo{
	public static void main(String []args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter car Id : ");
		int Id = sc.nextInt();
		System.out.println("Enter car type('Small Car','Van','SUV') : ");
		sc.nextLine();
		String type = sc.nextLine();
		CarRental c1 = new CarRental(Id , type);
		
		c1.computeRent();
		
		c1.showCar();
	}
}